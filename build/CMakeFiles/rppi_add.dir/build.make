# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/abishek/myFiles/github/AMD-RPP-CPUONLY

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build

# Include any dependencies generated for this target.
include CMakeFiles/rppi_add.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rppi_add.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rppi_add.dir/flags.make

CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o: CMakeFiles/rppi_add.dir/flags.make
CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o: ../src/arithmetic/rppi_add.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o -c /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/src/arithmetic/rppi_add.cpp

CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/src/arithmetic/rppi_add.cpp > CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.i

CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/src/arithmetic/rppi_add.cpp -o CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.s

# Object files for target rppi_add
rppi_add_OBJECTS = \
"CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o"

# External object files for target rppi_add
rppi_add_EXTERNAL_OBJECTS =

rppi_add: CMakeFiles/rppi_add.dir/src/arithmetic/rppi_add.cpp.o
rppi_add: CMakeFiles/rppi_add.dir/build.make
rppi_add: CMakeFiles/rppi_add.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rppi_add"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rppi_add.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rppi_add.dir/build: rppi_add

.PHONY : CMakeFiles/rppi_add.dir/build

CMakeFiles/rppi_add.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rppi_add.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rppi_add.dir/clean

CMakeFiles/rppi_add.dir/depend:
	cd /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/abishek/myFiles/github/AMD-RPP-CPUONLY /Users/abishek/myFiles/github/AMD-RPP-CPUONLY /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build /Users/abishek/myFiles/github/AMD-RPP-CPUONLY/build/CMakeFiles/rppi_add.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rppi_add.dir/depend

