cmake_minimum_required(VERSION 3.31)
project(Raytracer)

set(CMAKE_CXX_STANDARD 26)

add_executable(Raytracer main.cpp)

add_library(Vec STATIC
        lib/Vec.cpp
        lib/Vec.h)

target_link_libraries(Raytracer Vec)
