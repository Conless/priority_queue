cmake_minimum_required(VERSION 3.11)
project(priority_queue)

enable_testing()

set(CMAKE_CXX_FLAGS "-g -O2 -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Main sources
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/data)
add_subdirectory(src)

# Test
# add_subdirectory(test)
