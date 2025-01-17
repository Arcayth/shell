cmake_minimum_required(VERSION 3.13)

# Project name
project(shell-starter-cpp)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable the generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all source files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

# Add the executable
add_executable(shell ${SOURCE_FILES})

