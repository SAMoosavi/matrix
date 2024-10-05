cmake_minimum_required(VERSION 3.25)
project(Matrix VERSION 1.0.0 LANGUAGES CXX)

include(CTest)

enable_testing()

# Add interface library
add_library(matirx_interface INTERFACE)

# Set cpp standard
target_compile_features(matirx_interface INTERFACE cxx_std_20)

# Add compiler flags
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(matirx_interface INTERFACE
        -Wall
        -Wextra
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(matirx_interface INTERFACE
        /W4
    )
endif()

add_subdirectory(include)
add_subdirectory(src/common)
add_subdirectory(src/polynomial)

add_executable(matrix src/main.cpp)

target_link_libraries(matrix
    PUBLIC
        MatrixUtility)

        # if(NOT CMAKE_BUILD_TYPE)
        #     set(CMAKE_BUILD_TYPE Release)
        # endif()
