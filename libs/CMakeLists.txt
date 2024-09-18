include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
  FIND_PACKAGE_ARGS 
)

FetchContent_MakeAvailable(googletest)

add_library(goolgletest_interface INTERFACE)

target_link_libraries(goolgletest_interface INTERFACE gtest_main gmock_main)
