include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(heuristics_test heuristics_test.cpp)

include_directories(../src/fifteen)
target_link_libraries(heuristics_test PRIVATE GTest::GTest)

add_test(heuristics_gtests heuristics_test)
