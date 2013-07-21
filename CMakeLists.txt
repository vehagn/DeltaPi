# CMake's configuration

# Set the minimum required version of CMake for this project
cmake_minimum_required( VERSION 2.6 )

# Find Rpi-hw library on the operating system
find_package( RpiHw )

# Check if the library was found
if (RpiHw_FOUND)
    # Set the path to the header files
    include_directories( ${RpiHw_INCLUDE_DIRS} )

    # Compile the project
    add_executable( dpb ${CMAKE_SOURCE_DIR} dpb.cpp )

    # Link the library to the project
    target_link_libraries( dpb ${RpiHw_LIBRARIES} )
endif()

