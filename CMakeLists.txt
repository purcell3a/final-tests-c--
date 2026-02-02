cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(LibraryExecutable main.cpp Library.cpp)

# Add test executable
add_executable(LibraryTest tests/LibraryTest.cpp Library.cpp)

# Enable testing and add LibraryTest to CTest
enable_testing()
add_test(NAME LibraryTest COMMAND LibraryTest)
