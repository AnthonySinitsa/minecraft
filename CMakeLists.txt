# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(minecraft)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add executable target with source files listed in SOURCE_FILES variable
file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(minecraft ${SOURCE_FILES})

# Find required packages
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

# Include directories for SDL2 and GLEW
include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Link SDL2, GLEW, and OpenGL libraries
target_link_libraries(minecraft ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} GL)