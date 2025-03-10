cmake_minimum_required(VERSION 3.25)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(test_olog test_olog.cpp)
target_link_libraries(test_olog ${GTEST_LIBRARIES} GTest::Main OLog)

# Register the test
add_test(NAME AddTests COMMAND test_olog)