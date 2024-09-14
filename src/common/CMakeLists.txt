
add_library(MatrixCommon STATIC
    concept.h
)

target_link_libraries(MatrixCommon PRIVATE MatrixInterface)
