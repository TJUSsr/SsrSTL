# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/monster/SsrProject/SsrSTL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/monster/SsrProject/SsrSTL/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/SsrSTL_Release_Darwin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SsrSTL_Release_Darwin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SsrSTL_Release_Darwin.dir/flags.make

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o: CMakeFiles/SsrSTL_Release_Darwin.dir/flags.make
CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/monster/SsrProject/SsrSTL/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o -c /Users/monster/SsrProject/SsrSTL/main.cpp

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/monster/SsrProject/SsrSTL/main.cpp > CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.i

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/monster/SsrProject/SsrSTL/main.cpp -o CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.s

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.requires

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.provides: CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SsrSTL_Release_Darwin.dir/build.make CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.provides

CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.provides.build: CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o


CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o: CMakeFiles/SsrSTL_Release_Darwin.dir/flags.make
CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o: ../utils_logs/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/monster/SsrProject/SsrSTL/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o -c /Users/monster/SsrProject/SsrSTL/utils_logs/logger.cpp

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/monster/SsrProject/SsrSTL/utils_logs/logger.cpp > CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.i

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/monster/SsrProject/SsrSTL/utils_logs/logger.cpp -o CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.s

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.requires:

.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.requires

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.provides: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/SsrSTL_Release_Darwin.dir/build.make CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.provides.build
.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.provides

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.provides.build: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o


CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o: CMakeFiles/SsrSTL_Release_Darwin.dir/flags.make
CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o: ../utils_alloc/alloc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/monster/SsrProject/SsrSTL/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o -c /Users/monster/SsrProject/SsrSTL/utils_alloc/alloc.cpp

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/monster/SsrProject/SsrSTL/utils_alloc/alloc.cpp > CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.i

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/monster/SsrProject/SsrSTL/utils_alloc/alloc.cpp -o CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.s

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.requires:

.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.requires

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.provides: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.requires
	$(MAKE) -f CMakeFiles/SsrSTL_Release_Darwin.dir/build.make CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.provides.build
.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.provides

CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.provides.build: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o


# Object files for target SsrSTL_Release_Darwin
SsrSTL_Release_Darwin_OBJECTS = \
"CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o" \
"CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o" \
"CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o"

# External object files for target SsrSTL_Release_Darwin
SsrSTL_Release_Darwin_EXTERNAL_OBJECTS =

bin/SsrSTL_Release_Darwin: CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o
bin/SsrSTL_Release_Darwin: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o
bin/SsrSTL_Release_Darwin: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o
bin/SsrSTL_Release_Darwin: CMakeFiles/SsrSTL_Release_Darwin.dir/build.make
bin/SsrSTL_Release_Darwin: CMakeFiles/SsrSTL_Release_Darwin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/monster/SsrProject/SsrSTL/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bin/SsrSTL_Release_Darwin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SsrSTL_Release_Darwin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SsrSTL_Release_Darwin.dir/build: bin/SsrSTL_Release_Darwin

.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/build

CMakeFiles/SsrSTL_Release_Darwin.dir/requires: CMakeFiles/SsrSTL_Release_Darwin.dir/main.cpp.o.requires
CMakeFiles/SsrSTL_Release_Darwin.dir/requires: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_logs/logger.cpp.o.requires
CMakeFiles/SsrSTL_Release_Darwin.dir/requires: CMakeFiles/SsrSTL_Release_Darwin.dir/utils_alloc/alloc.cpp.o.requires

.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/requires

CMakeFiles/SsrSTL_Release_Darwin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SsrSTL_Release_Darwin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/clean

CMakeFiles/SsrSTL_Release_Darwin.dir/depend:
	cd /Users/monster/SsrProject/SsrSTL/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/monster/SsrProject/SsrSTL /Users/monster/SsrProject/SsrSTL /Users/monster/SsrProject/SsrSTL/cmake-build-release /Users/monster/SsrProject/SsrSTL/cmake-build-release /Users/monster/SsrProject/SsrSTL/cmake-build-release/CMakeFiles/SsrSTL_Release_Darwin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SsrSTL_Release_Darwin.dir/depend
