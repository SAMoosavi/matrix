cmake_minimum_required(VERSION 3.26)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix main.cpp
        Matrix.cpp
        Matrix.h
        concept.h
        Matrix-tmp.h
        Expression.cpp
        Expression.h
        Expression-inl.h
        Polynomial.h
        Polynomial.cpp
        Polynomial-inl.h
)
