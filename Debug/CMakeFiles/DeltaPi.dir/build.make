# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/delta/DeltaPi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/delta/DeltaPi/Debug

# Include any dependencies generated for this target.
include CMakeFiles/DeltaPi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DeltaPi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DeltaPi.dir/flags.make

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o: CMakeFiles/DeltaPi.dir/flags.make
CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o: ../DeltaPi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/delta/DeltaPi/Debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o -c /home/delta/DeltaPi/DeltaPi.cpp

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeltaPi.dir/DeltaPi.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/delta/DeltaPi/DeltaPi.cpp > CMakeFiles/DeltaPi.dir/DeltaPi.cpp.i

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeltaPi.dir/DeltaPi.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/delta/DeltaPi/DeltaPi.cpp -o CMakeFiles/DeltaPi.dir/DeltaPi.cpp.s

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.requires:
.PHONY : CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.requires

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.provides: CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.requires
	$(MAKE) -f CMakeFiles/DeltaPi.dir/build.make CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.provides.build
.PHONY : CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.provides

CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.provides.build: CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o

# Object files for target DeltaPi
DeltaPi_OBJECTS = \
"CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o"

# External object files for target DeltaPi
DeltaPi_EXTERNAL_OBJECTS =

DeltaPi: CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o
DeltaPi: CMakeFiles/DeltaPi.dir/build.make
DeltaPi: libclasses.a
DeltaPi: libfunctions.a
DeltaPi: libmysql.a
DeltaPi: /usr/lib/librpihw.so
DeltaPi: /usr/lib/libGraphicsMagick++.so
DeltaPi: CMakeFiles/DeltaPi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable DeltaPi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeltaPi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DeltaPi.dir/build: DeltaPi
.PHONY : CMakeFiles/DeltaPi.dir/build

CMakeFiles/DeltaPi.dir/requires: CMakeFiles/DeltaPi.dir/DeltaPi.cpp.o.requires
.PHONY : CMakeFiles/DeltaPi.dir/requires

CMakeFiles/DeltaPi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DeltaPi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DeltaPi.dir/clean

CMakeFiles/DeltaPi.dir/depend:
	cd /home/delta/DeltaPi/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/delta/DeltaPi /home/delta/DeltaPi /home/delta/DeltaPi/Debug /home/delta/DeltaPi/Debug /home/delta/DeltaPi/Debug/CMakeFiles/DeltaPi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DeltaPi.dir/depend

