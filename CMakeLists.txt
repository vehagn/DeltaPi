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
link_directories(${MYSQLCPPCONN_SOURCE_DIR}/cppconn)
link_directories(${MYSQL_DIR}/lib/opt)

# Add librares
add_library(mysql mysql.cpp)
add_library(functions functions.cpp)
add_library(classes classes.cpp)

# Build
#add_executable(dpb dpb.cpp)
add_executable(DeltaPi DeltaPi.cpp)
SET_TARGET_PROPERTIES(DeltaPi PROPERTIES
			LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
			COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
target_link_libraries(DeltaPi classes functions 
			${RpiHw_LIBRARIES} ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
  			${MYSQLCPPCONN_STLPORT_LIB} ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
			${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY} ${Boost_LIBRARIES})



