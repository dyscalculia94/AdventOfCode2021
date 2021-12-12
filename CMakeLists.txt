cmake_minimum_required(VERSION 3.1.0)

project(aoc2021)

# ==================================================================================================================== #
# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ==================================================================================================================== #
# Set compiler flags
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall -Wunused-variable -Wno-unknown-pragmas -g -fPIC -ffast-math")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# ==================================================================================================================== #
# Set the location of the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# ==================================================================================================================== #
# Set the include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/inc
 
  /usr/local/include
  /usr/include
)

# ==================================================================================================================== #
# C++ sources
message(STATUS ">>> Adding src subdirectory")
add_subdirectory(src)

# ==================================================================================================================== #
# Make the executable
add_executable(aoc2021 main.cpp ${AOC2021_SRCS})