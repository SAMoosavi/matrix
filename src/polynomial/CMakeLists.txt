
add_library(polynomial INTERFACE)

target_include_directories(polynomial INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(polynomial INTERFACE matirx_interface matrix_common)
