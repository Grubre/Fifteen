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
add_executable(fifteen_test fifteen_test.cpp)

include_directories(../src/fifteen_lib)
target_link_libraries(heuristics_test PRIVATE GTest::GTest fifteen_lib)
target_link_libraries(fifteen_test PRIVATE GTest::GTest fifteen_lib)

add_test(heuristics_gtests heuristics_test)
add_test(fifteen_gtests fifteen_test)
