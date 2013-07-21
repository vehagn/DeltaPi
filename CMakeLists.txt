# CMake's configuration

# Set the minimum required version of CMake for this project
cmake_minimum_required(VERSION 2.6)

# Set the compiler flags
add_definitions(-Wall -ansi -pedantic -pedantic-errors -std=c++11)

# Find dependencies
find_package(RpiHw REQUIRED)
find_package(Freetype REQUIRED)
find_package(GraphicsMagick++ REQUIRED)

# Set the path to the header files
include_directories(${RpiHw_INCLUDE_DIRS})
  
# Build
add_executable(dpb ${CMAKE_SOURCE_DIR}/dpb.cpp)
target_link_libraries(dpb ${RpiHw_LIBRARIES})


