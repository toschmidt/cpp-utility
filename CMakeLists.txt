cmake_minimum_required(VERSION 3.14)
# Name of your project
# project(<project-name>)

# C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compilation Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -static-libasan -static-libubsan -fsanitize=address -fsanitize=leak -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# Standard Libraries
# include(${CMAKE_SOURCE_DIR}/cmake/threads.cmake)

# Test Framework
# include(${CMAKE_SOURCE_DIR}/cmake/catch2.cmake)

# Implementation
add_subdirectory(src)

# Tests
add_subdirectory(test)
