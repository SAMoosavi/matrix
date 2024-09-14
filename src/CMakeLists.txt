# List all the source files
set(SOURCES
        main.cpp
)

add_subdirectory(common)
add_subdirectory(matrix)
add_subdirectory(polynomial)

# Add the executable
add_executable(Matrix ${SOURCES})

target_link_libraries(Matrix
    PRIVATE
        MatrixCommon
    PUBLIC
        MatrixLib
    PRIVATE
        Polynomial
)

enable_testing()
