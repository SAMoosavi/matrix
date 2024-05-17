cmake_minimum_required(VERSION 3.26)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
add_executable(Matrix main.cpp
        Matrix.cpp
        Matrix.h
        concept.h
        Matrix-tmp.h
        Polynomial.h
        Polynomial.cpp
        Polynomial-inl.h
        RationalExpression.cpp
        RationalExpression.h
        RationalExpression-inl.h
)
