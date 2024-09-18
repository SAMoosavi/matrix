cmake_minimum_required(VERSION 3.25)
project(Matrix VERSION 1.0)

include(CTest)

enable_testing()

# Add interface library
add_library(matirx_interface INTERFACE)

# Set cpp standard
target_compile_features(matirx_interface INTERFACE cxx_std_20)

# Add include directory to all subdirectories
include_directories(include)

# Add source directory
add_subdirectory(src)

# Add test directory
add_subdirectory(tests)

# Add libs directory
add_subdirectory(libs)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

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
