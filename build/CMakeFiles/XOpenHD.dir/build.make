# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/consti10/Desktop/XOpenHD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/consti10/Desktop/XOpenHD/build

# Include any dependencies generated for this target.
include CMakeFiles/XOpenHD.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/XOpenHD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XOpenHD.dir/flags.make

CMakeFiles/XOpenHD.dir/main.cpp.o: CMakeFiles/XOpenHD.dir/flags.make
CMakeFiles/XOpenHD.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/consti10/Desktop/XOpenHD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XOpenHD.dir/main.cpp.o"
	/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XOpenHD.dir/main.cpp.o -c /home/consti10/Desktop/XOpenHD/main.cpp

CMakeFiles/XOpenHD.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XOpenHD.dir/main.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/consti10/Desktop/XOpenHD/main.cpp > CMakeFiles/XOpenHD.dir/main.cpp.i

CMakeFiles/XOpenHD.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XOpenHD.dir/main.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/consti10/Desktop/XOpenHD/main.cpp -o CMakeFiles/XOpenHD.dir/main.cpp.s

# Object files for target XOpenHD
XOpenHD_OBJECTS = \
"CMakeFiles/XOpenHD.dir/main.cpp.o"

# External object files for target XOpenHD
XOpenHD_EXTERNAL_OBJECTS =

XOpenHD: CMakeFiles/XOpenHD.dir/main.cpp.o
XOpenHD: CMakeFiles/XOpenHD.dir/build.make
XOpenHD: CMakeFiles/XOpenHD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/consti10/Desktop/XOpenHD/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable XOpenHD"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XOpenHD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XOpenHD.dir/build: XOpenHD

.PHONY : CMakeFiles/XOpenHD.dir/build

CMakeFiles/XOpenHD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XOpenHD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XOpenHD.dir/clean

CMakeFiles/XOpenHD.dir/depend:
	cd /home/consti10/Desktop/XOpenHD/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/consti10/Desktop/XOpenHD /home/consti10/Desktop/XOpenHD /home/consti10/Desktop/XOpenHD/build /home/consti10/Desktop/XOpenHD/build /home/consti10/Desktop/XOpenHD/build/CMakeFiles/XOpenHD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XOpenHD.dir/depend

