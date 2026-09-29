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

add_library(primitives STATIC
        primitives/MatrixTransformations.cpp
        primitives/MatrixTransformations.h
        primitives/Ray.cpp
        primitives/Ray.h
)

target_include_directories(primitives PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/primitives
)

target_link_libraries(primitives PUBLIC tmath)

add_executable(Raytracer main.cpp
        )

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
        tests/test_color.cpp
)

target_link_libraries(test_color PRIVATE
        doctest::doctest
        tmath)

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
)





target_link_libraries(Raytracer PRIVATE tmath)

