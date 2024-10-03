cmake_minimum_required(VERSION 3.14)
project(Magic VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add Homebrew lib and include directories
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/lib" "/opt/homebrew/include")

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Collect all test files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Create library target
add_library(magic_lib ${SOURCES})
target_link_libraries(magic_lib PRIVATE spdlog::spdlog)

# Create executable target
add_executable(magic src/main.cpp)
target_link_libraries(magic PRIVATE magic_lib spdlog::spdlog)

# Create test executable
add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PRIVATE 
    magic_lib
    GTest::GTest
    GTest::Main
    spdlog::spdlog
)

# Enable testing
enable_testing()

# Add tests to CTest
add_test(NAME MagicTests COMMAND run_tests)
set_tests_properties(MagicTests PROPERTIES FAIL_REGULAR_EXPRESSION ".*[Ff]ail.*")
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# Custom target for running the main program
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/magic
    DEPENDS magic
)