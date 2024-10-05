
# add_library(Matrix STATIC)

# target_include_directories(Matrix INTERFACE
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(Matrix
#     PRIVATE
#     matirx_interface
#     matrix_common)


add_library(MatrixUtility INTERFACE)

set_target_properties(MatrixUtility PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(MatrixUtility
    INTERFACE
        # $<INSTALL_INTERFACE:include>
        # $<BUILD_INTERFACE:include>
        ${CMAKE_CURRENT_SOURCE_DIR}
        # matrix.h
    # # PRIVATE
        # matrix-tmp.h
)

target_link_libraries(MatrixUtility
    INTERFACE
        matirx_interface
        matrix_common)
