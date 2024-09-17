# List all test source files
set(TEST_FILES
        matrixFunctionality.cpp
        polynomialFunctionality.cpp
)

# Create an executable target for each test file
foreach (TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} gtest_main gmock_main polynomial)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    # add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_CTEST_COMMAND}
    #     --build-and-test "${CMAKE_SOURCE_DIR}/tests/${TEST_FILE}"
    #                         "${CMAKE_BINARY_DIR}/tests/${TEST_NAME}"
    #     --build-target "${CMAKE_SOURCE_DIR}/test"
    #     --build-generator ${CMAKE_GENERATOR}
    #     --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    #     --build-project ${TEST_NAME}
    #     --test-command ${TEST_NAME}
    # )
endforeach ()
