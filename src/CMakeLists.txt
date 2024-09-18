# List all the source files
set(SOURCES
        main.cpp
)

add_subdirectory(common)
add_subdirectory(polynomial)

# Add the executable
add_executable(Matrix ${SOURCES})

target_link_libraries(Matrix PRIVATE matirx_interface)
target_link_libraries(Matrix PRIVATE matrix_common)
target_link_libraries(Matrix PRIVATE polynomial)

# Add matrix library
add_library(matrix INTERFACE IMPORTED)

target_include_directories(matrix INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(matrix INTERFACE
        matirx_interface
        matrix_common
        polynomial
)
