cmake_minimum_required(VERSION 3.10)
project(psal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all source files recursively from src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include header directory
target_include_directories(${PROJECT_NAME} PRIVATE include)
