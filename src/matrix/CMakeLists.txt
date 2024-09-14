
add_library(MatrixLib SHARED
    matrix-tmp.h
)

target_link_libraries(MatrixLib PRIVATE MatrixInterface)

target_include_directories(MatrixLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
