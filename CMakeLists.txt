# CMake's configuration

# Set the minimum required version of CMake for this project
cmake_minimum_required(VERSION 2.6)

# Set the compiler flags
add_definitions(-Wall -ansi -pedantic -pedantic-errors -std=c++11)

# Find dependencies
find_package(RpiHw REQUIRED)
find_package(Freetype REQUIRED)
find_package(GraphicsMagick++ REQUIRED)
find_package(Boost REQUIRED)

# Set the path to the header files
include_directories(${RpiHw_INCLUDE_DIRS})
include_directories(${MYSQLCPPCONN_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

#set(MY_TARGET_LINK_LIBRARIES mysqlcppconn)

# Add librares
add_library(mysql mysql.cpp)
add_library(functions functions.cpp)
add_library(classes classes.cpp)

# Build
add_executable(DeltaPi DeltaPi.cpp)
add_executable(EpsilonPi EpsilonPi.cpp)
target_link_libraries(DeltaPi classes functions mysql mysqlcppconn ${RpiHw_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(EpsilonPi classes functions mysql mysqlcppconn ${RpiHw_LIBRARIES} ${Boost_LIBRARIES})



