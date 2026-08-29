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
        lib/Matrix.h)

target_include_directories(tmath INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_compile_options(tmath INTERFACE
        $<$<CONFIG:Release>:-O3>
        -march=native
)

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






target_link_libraries(Raytracer PRIVATE tmath)

