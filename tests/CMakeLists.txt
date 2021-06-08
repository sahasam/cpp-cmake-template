cmake_minimum_required(VERSION 3.19.1)

enable_testing()

set(TEST_SOURCES
    test.cpp
    adder/adder.cpp
)

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tests gtest_main Adder)

include(GoogleTest)
gtest_discover_tests(tests)