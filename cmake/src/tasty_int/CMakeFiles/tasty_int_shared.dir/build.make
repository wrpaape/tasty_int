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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Reid/my_projects/cpp/tasty_int

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Reid/my_projects/cpp/tasty_int/cmake

# Include any dependencies generated for this target.
include src/tasty_int/CMakeFiles/tasty_int_shared.dir/depend.make

# Include the progress variables for this target.
include src/tasty_int/CMakeFiles/tasty_int_shared.dir/progress.make

# Include the compile flags for this target's objects.
include src/tasty_int/CMakeFiles/tasty_int_shared.dir/flags.make

../src/tasty_int/codegen/tasty_int_token_values.cpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "generate TastyInt 'token_values' lookup tables"
	cd /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/configure/bin && /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/configure/bin/generate_tasty_int_token_values_file /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/codegen/tasty_int_token_values.cpp

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o: src/tasty_int/CMakeFiles/tasty_int_shared.dir/flags.make
src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o: ../src/tasty_int/tasty_int.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o -c /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/tasty_int.cpp

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.i"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/tasty_int.cpp > CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.i

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.s"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/tasty_int.cpp -o CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.s

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.requires:

.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.requires

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.provides: src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.requires
	$(MAKE) -f src/tasty_int/CMakeFiles/tasty_int_shared.dir/build.make src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.provides.build
.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.provides

src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.provides.build: src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o


src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o: src/tasty_int/CMakeFiles/tasty_int_shared.dir/flags.make
src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o: ../src/tasty_int/codegen/tasty_int_token_values.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o -c /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/codegen/tasty_int_token_values.cpp

src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.i"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/codegen/tasty_int_token_values.cpp > CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.i

src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.s"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int/codegen/tasty_int_token_values.cpp -o CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.s

src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.requires:

.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.requires

src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.provides: src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.requires
	$(MAKE) -f src/tasty_int/CMakeFiles/tasty_int_shared.dir/build.make src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.provides.build
.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.provides

src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.provides.build: src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o


# Object files for target tasty_int_shared
tasty_int_shared_OBJECTS = \
"CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o" \
"CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o"

# External object files for target tasty_int_shared
tasty_int_shared_EXTERNAL_OBJECTS =

../lib/libtasty_int_shared.dylib: src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o
../lib/libtasty_int_shared.dylib: src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o
../lib/libtasty_int_shared.dylib: src/tasty_int/CMakeFiles/tasty_int_shared.dir/build.make
../lib/libtasty_int_shared.dylib: src/tasty_int/CMakeFiles/tasty_int_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../../../lib/libtasty_int_shared.dylib"
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tasty_int_shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tasty_int/CMakeFiles/tasty_int_shared.dir/build: ../lib/libtasty_int_shared.dylib

.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/build

src/tasty_int/CMakeFiles/tasty_int_shared.dir/requires: src/tasty_int/CMakeFiles/tasty_int_shared.dir/tasty_int.cpp.o.requires
src/tasty_int/CMakeFiles/tasty_int_shared.dir/requires: src/tasty_int/CMakeFiles/tasty_int_shared.dir/codegen/tasty_int_token_values.cpp.o.requires

.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/requires

src/tasty_int/CMakeFiles/tasty_int_shared.dir/clean:
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int && $(CMAKE_COMMAND) -P CMakeFiles/tasty_int_shared.dir/cmake_clean.cmake
.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/clean

src/tasty_int/CMakeFiles/tasty_int_shared.dir/depend: ../src/tasty_int/codegen/tasty_int_token_values.cpp
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Reid/my_projects/cpp/tasty_int /Users/Reid/my_projects/cpp/tasty_int/src/tasty_int /Users/Reid/my_projects/cpp/tasty_int/cmake /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int /Users/Reid/my_projects/cpp/tasty_int/cmake/src/tasty_int/CMakeFiles/tasty_int_shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tasty_int/CMakeFiles/tasty_int_shared.dir/depend

