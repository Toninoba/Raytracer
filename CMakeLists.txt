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
        src/lib/Matrix.h
        src/lib/Color.h
        src/lib/Constants.h
        src/lib/Vec.h
)

target_include_directories(tmath INTERFACE
        src/lib
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tmath INTERFACE
        $<$<CONFIG:Release>:-O3>
        -mavx2
        -mfma
    )
elseif (MSVC)
    target_compile_options(tmath INTERFACE
        $<$<CONFIG:Release>:/O2>
        /arch:AVX2
    )
endif()

# ------------------------------------

add_library(primitives STATIC
        src/primitives/MatrixTransformations.cpp
        src/primitives/MatrixTransformations.h
        src/primitives/Ray.cpp
        src/primitives/Ray.h
        src/primitives/Intersection.cpp
        src/primitives/Intersection.h
        src/primitives/Intersections.cpp
        src/primitives/Intersections.h
        src/primitives/Computations.cpp
        src/primitives/Computations.h
        src/primitives/Material.cpp
        src/primitives/Material.h
)

target_include_directories(primitives PUBLIC
        src/primitives
)

target_link_libraries(primitives PUBLIC
        tmath
        geometry
        patterns
)

# ------------------------------------

add_library(geometry STATIC
        src/geometry/Sphere.cpp
        src/geometry/Sphere.h
        src/geometry/Shape.cpp
        src/geometry/Shape.h
        src/geometry/TestShape.cpp
        src/geometry/TestShape.h
        src/geometry/Plane.cpp
        src/geometry/Plane.h
        src/geometry/Cube.cpp
        src/geometry/Cube.h
        src/geometry/Cylinder.cpp
        src/geometry/Cylinder.h
        src/geometry/Cone.cpp
        src/geometry/Cone.h
)

target_include_directories(geometry PUBLIC
        src/geometry
)

target_link_libraries(geometry PUBLIC
        tmath
        primitives
)

# ------------------------------------

add_library(lights STATIC
        src/lights/PointLight.cpp
        src/lights/PointLight.h
)

target_include_directories(lights PUBLIC
        src/lights
)

target_link_libraries(lights PUBLIC
        primitives
)

# ------------------------------------

add_library(canvas INTERFACE
        src/canvas/Canvas.h
)

target_include_directories(canvas INTERFACE
        src/canvas
)


# ------------------------------------

add_library(scene STATIC
        src/scene/World.cpp
        src/scene/World.h
        src/scene/Camera.cpp
        src/scene/Camera.h
)

target_include_directories(scene PUBLIC
        src/scene
)

target_link_libraries(scene PUBLIC
        geometry
        lights
        patterns
)

# ------------------------------------

add_library(patterns STATIC
        src/patterns/StripedPattern.cpp
        src/patterns/StripedPattern.h
        src/patterns/Pattern.cpp
        src/patterns/Pattern.h
        src/patterns/GradientPattern.cpp
        src/patterns/GradientPattern.h
        src/patterns/RingPattern.cpp
        src/patterns/RingPattern.h
        src/patterns/CheckerPattern.cpp
        src/patterns/CheckerPattern.h
        src/patterns/TestPattern.cpp
        src/patterns/TestPattern.h
)

target_include_directories(patterns PUBLIC
        src/patterns
)

target_link_libraries(patterns PUBLIC
        tmath
        geometry
)

# ------------------------------------
# Executables
# ------------------------------------

add_executable(Raytracer src/canvas/window_main.cpp
        src/canvas/windowRenderer.cpp
        src/canvas/ThreadPool.cpp
)

target_link_libraries(Raytracer PRIVATE SDL3::SDL3-static
    tmath canvas primitives geometry lights scene
)


# ------------------------------------
# Unit-tests
# ------------------------------------

# Vec tests
add_executable(test_vec
        src/tests/test_vec.cpp)

target_link_libraries(test_vec PRIVATE doctest::doctest tmath)

# Matrix tests
add_executable(test_matrix
        src/tests/test_matrix.cpp
)

target_link_libraries(test_matrix PRIVATE
        doctest::doctest
        tmath
)

# Color tests
add_executable(test_color
        src/tests/test_color.cpp)

target_link_libraries(test_color PRIVATE
        doctest::doctest
        tmath)

# Canvas tests
add_executable(test_canvas
        src/tests/test_canvas.cpp
)

target_link_libraries(test_canvas
        doctest::doctest
        canvas
        tmath
)

# Transformation tests

add_executable(test_transformation
        src/tests/test_transformation.cpp
)

target_link_libraries(test_transformation PRIVATE
        doctest::doctest
        tmath
        primitives
)

# Ray tests

add_executable(test_ray
        src/tests/test_ray.cpp
)
target_link_libraries(test_ray PRIVATE
        doctest::doctest
        tmath
        primitives
        geometry
)

# Light tests

add_executable(test_lights
        src/tests/test_lights.cpp
)

target_link_libraries(test_lights PRIVATE
        doctest::doctest
        tmath
        geometry
        primitives
        lights
)

# World test
add_executable(test_world
        src/tests/test_world.cpp
)

target_link_libraries(test_world PRIVATE
        doctest::doctest
        scene
)

# Camera tests
add_executable(test_camera
        src/tests/test_camera.cpp
)

target_link_libraries(test_camera PRIVATE
        doctest::doctest
        scene
)

# Geometry tests
add_executable(test_geometry
    src/tests/test_geometry.cpp
)

target_link_libraries(test_geometry PRIVATE
        doctest::doctest
        geometry
)

# Pattern tests

add_executable(test_pattern
    src/tests/test_patterns.cpp
)

target_link_libraries(test_pattern
        doctest::doctest
        geometry
        patterns
        lights
        primitives
)

# Reflection tests

add_executable(test_reflection
    src/tests/test_reflection.cpp
)

target_link_libraries(test_reflection PRIVATE
        doctest::doctest
        primitives
        lights
        scene
)

# Refraction tests

add_executable(test_refraction
    src/tests/test_refraction.cpp
)

target_link_libraries(test_refraction PRIVATE
        doctest::doctest
        primitives
        lights
        scene
)

enable_testing()

add_test(NAME TestVec COMMAND test_vec)
add_test(NAME TestMatrix COMMAND test_matrix)
add_test(NAME TestColor COMMAND test_color)
add_test(NAME TestTransformation COMMAND test_transformation)
add_test(NAME TestRay COMMAND test_ray)
add_test(NAME TestLights COMMAND test_lights)
add_test(NAME TestWorld COMMAND test_world)
add_test(NAME TestCamera COMMAND test_camera)
add_test(NAME TestGeometry COMMAND test_geometry)
add_test(NAME TestCanvas COMMAND test_canvas)
add_test(NAME TestPattern COMMAND test_pattern)
add_test(NAME TestRefraction COMMAND test_refraction)
add_test(NAME TestReflection COMMAND test_reflection)