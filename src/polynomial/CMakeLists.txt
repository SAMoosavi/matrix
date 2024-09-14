
add_library(Polynomial STATIC
    polynomial.h
    polynomial-tmp.h
    polynomial-helper.h
    polynomial-helper-tmp.h
)

target_link_libraries(Polynomial PRIVATE MatrixInterface)

