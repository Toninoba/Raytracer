cmake_minimum_required(VERSION 3.31)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.5.3
)

FetchContent_MakeAvailable(doctest)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        # Nutze einen aktuellen Release-Tag von SDL3 (z.B. release-3.1.3 oder neuer)
        GIT_TAG release-3.4.16
)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

# ------------------------------------
# libraries
# ------------------------------------



add_library(tmath INTERFACE
        lib/Matrix.h
        lib/Color.h
        lib/Constants.h)

target_include_directories(tmath INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_compile_options(tmath INTERFACE
        $<$<CONFIG:Release>:-O3>
        -march=native
)

# ------------------------------------

add_library(primitives STATIC
        primitives/MatrixTransformations.cpp
        primitives/MatrixTransformations.h
        primitives/Ray.cpp
        primitives/Ray.h
        primitives/Intersection.cpp
        primitives/Intersection.h
        primitives/Intersections.cpp
        primitives/Intersections.h
        primitives/Material.cpp
        primitives/Material.h
        primitives/Computations.cpp
        primitives/Computations.h
)

target_include_directories(primitives PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/primitives
)

target_link_libraries(primitives PUBLIC tmath geometry)

# ------------------------------------

add_library(geometry STATIC
        geometry/Sphere.cpp
        geometry/Sphere.h
        lights/PointLight.cpp
        lights/PointLight.h
)

target_include_directories(geometry PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/geometry
)

target_link_libraries(geometry PUBLIC tmath primitives)

# ------------------------------------

add_library(lights STATIC
        lights/PointLight.cpp
        lights/PointLight.h
)

target_include_directories(lights PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lights
)

target_link_libraries(lights PUBLIC tmath primitives)

# ------------------------------------

add_library(canvas INTERFACE
        canvas/Canvas.h
)

target_include_directories(canvas INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/canvas
)


# ------------------------------------

add_library(scene STATIC
        scene/World.cpp
        scene/World.h
)

target_include_directories(scene PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/scene
)

target_link_libraries(scene PUBLIC
        geometry
        lights
)

# ------------------------------------
# Executables
# ------------------------------------

add_executable(Raytracer canvas/window_main.cpp
        )

target_link_libraries(Raytracer PRIVATE SDL3::SDL3-static)

# ------------------------------------
# Unit-tests
# ------------------------------------

# Vec tests
add_executable(test_vec
        tests/test_vec.cpp)

target_link_libraries(test_vec PRIVATE doctest::doctest tmath)

# Matrix tests
add_executable(test_matrix
        tests/test_matrix.cpp
)

target_link_libraries(test_matrix PRIVATE
        doctest::doctest
        tmath
)

# Color tests
add_executable(test_color
        tests/test_color.cpp)

target_link_libraries(test_color PRIVATE
        doctest::doctest
        tmath)

# Canvas tests
add_executable(test_canvas
        tests/test_canvas.cpp
        tests/test_world.cpp
)

target_link_libraries(test_canvas
        doctest::doctest
        canvas
        tmath
)

        # Transformation tests

        add_executable(test_transformation
        tests/test_transformation.cpp
)

        target_link_libraries(test_transformation PRIVATE
        doctest::doctest
        tmath
        primitives
)

        # Ray tests

        add_executable(test_ray
        tests/test_ray.cpp
)
target_link_libraries(test_ray PRIVATE
        doctest::doctest
        tmath
        primitives
        geometry
)

add_executable(test_lights
        tests/test_lights.cpp
)

target_link_libraries(test_lights PRIVATE
        doctest::doctest
        tmath
        geometry
        primitives
        lights
)

add_executable(test_world
        tests/test_world.cpp
)

target_link_libraries(test_world PRIVATE
        doctest::doctest
        scene
)

enable_testing()

add_test(NAME TestVec COMMAND test_vec)
add_test(NAME TestMatrix COMMAND test_matrix)
add_test(NAME TestColor COMMAND test_color)
add_test(NAME TestTransformation COMMAND test_transformation)
add_test(NAME TestRay COMMAND test_ray)
add_test(NAME TestLights COMMAND test_lights)