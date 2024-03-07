cmake_minimum_required(VERSION 3.26)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix main.cpp
        Matrix.cpp
        Matrix.h
        Consept.h
        Matrix-tmp.h
)
