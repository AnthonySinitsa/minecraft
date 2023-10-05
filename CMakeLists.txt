# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(minecraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add executable target with source files listed in SOURCE_FILES variable
file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(minecraft ${SOURCE_FILES})
