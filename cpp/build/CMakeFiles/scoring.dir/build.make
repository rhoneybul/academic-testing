# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/scoring.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/scoring.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/scoring.dir/flags.make

CMakeFiles/scoring.dir/src/main.cpp.o: CMakeFiles/scoring.dir/flags.make
CMakeFiles/scoring.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/scoring.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scoring.dir/src/main.cpp.o -c /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/src/main.cpp

CMakeFiles/scoring.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scoring.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/src/main.cpp > CMakeFiles/scoring.dir/src/main.cpp.i

CMakeFiles/scoring.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scoring.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/src/main.cpp -o CMakeFiles/scoring.dir/src/main.cpp.s

CMakeFiles/scoring.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/scoring.dir/src/main.cpp.o.requires

CMakeFiles/scoring.dir/src/main.cpp.o.provides: CMakeFiles/scoring.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/scoring.dir/build.make CMakeFiles/scoring.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/scoring.dir/src/main.cpp.o.provides

CMakeFiles/scoring.dir/src/main.cpp.o.provides.build: CMakeFiles/scoring.dir/src/main.cpp.o


# Object files for target scoring
scoring_OBJECTS = \
"CMakeFiles/scoring.dir/src/main.cpp.o"

# External object files for target scoring
scoring_EXTERNAL_OBJECTS =

scoring: CMakeFiles/scoring.dir/src/main.cpp.o
scoring: CMakeFiles/scoring.dir/build.make
scoring: CMakeFiles/scoring.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable scoring"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scoring.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/scoring.dir/build: scoring

.PHONY : CMakeFiles/scoring.dir/build

CMakeFiles/scoring.dir/requires: CMakeFiles/scoring.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/scoring.dir/requires

CMakeFiles/scoring.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/scoring.dir/cmake_clean.cmake
.PHONY : CMakeFiles/scoring.dir/clean

CMakeFiles/scoring.dir/depend:
	cd /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build /Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/build/CMakeFiles/scoring.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/scoring.dir/depend

