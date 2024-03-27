cmake_minimum_required(VERSION 3.26)
project(Matrix VERSION 1.0)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Matrix main.cpp
        Matrix.cpp
        Matrix.h
        concept.h
        Matrix-tmp.h
)
# Add source directory
add_subdirectory(src)
