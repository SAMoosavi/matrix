
add_library(matrix_common INTERFACE)

target_include_directories(matrix_common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(matrix_common INTERFACE matirx_interface)
