# List all the source files
set(SOURCES
        main.cpp
)

include_directories(Matrix PRIVATE common)
include_directories(Matrix PRIVATE matrix)
include_directories(Matrix PRIVATE polynomial)

# Add the executable
add_executable(Matrix ${SOURCES})

target_link_libraries(Matrix PRIVATE MatrixInterface)

enable_testing()
