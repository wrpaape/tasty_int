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

# Utility rule file for Unity.

# Include the progress variables for this target.
include CMakeFiles/Unity.dir/progress.make

CMakeFiles/Unity: CMakeFiles/Unity-complete


CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-install
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-mkdir
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-download
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-update
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-patch
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-configure
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-build
CMakeFiles/Unity-complete: Unity-prefix/src/Unity-stamp/Unity-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'Unity'"
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles/Unity-complete
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-done

Unity-prefix/src/Unity-stamp/Unity-install: Unity-prefix/src/Unity-stamp/Unity-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && $(MAKE) install
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-install

Unity-prefix/src/Unity-stamp/Unity-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'Unity'"
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/tmp
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E make_directory /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src
	/usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-mkdir

Unity-prefix/src/Unity-stamp/Unity-download: Unity-prefix/src/Unity-stamp/Unity-gitinfo.txt
Unity-prefix/src/Unity-stamp/Unity-download: Unity-prefix/src/Unity-stamp/Unity-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/test/src && /usr/local/Cellar/cmake/3.4.3/bin/cmake -P /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/tmp/Unity-gitclone.cmake
	cd /Users/Reid/my_projects/cpp/tasty_int/test/src && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-download

Unity-prefix/src/Unity-stamp/Unity-update: Unity-prefix/src/Unity-stamp/Unity-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -P /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/tmp/Unity-gitupdate.cmake

Unity-prefix/src/Unity-stamp/Unity-patch: Unity-prefix/src/Unity-stamp/Unity-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Performing patch step for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E copy /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity/CMakeLists.txt /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity/CMakeLists.txt
	cd /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-patch

Unity-prefix/src/Unity-stamp/Unity-configure: Unity-prefix/tmp/Unity-cfgcmd.txt
Unity-prefix/src/Unity-stamp/Unity-configure: Unity-prefix/src/Unity-stamp/Unity-update
Unity-prefix/src/Unity-stamp/Unity-configure: Unity-prefix/src/Unity-stamp/Unity-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -DCMAKE_INSTALL_PREFIX=/Users/Reid/my_projects/cpp/tasty_int/test "-GUnix Makefiles" /Users/Reid/my_projects/cpp/tasty_int/test/src/Unity
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-configure

Unity-prefix/src/Unity-stamp/Unity-build: Unity-prefix/src/Unity-stamp/Unity-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'Unity'"
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && $(MAKE)
	cd /Users/Reid/my_projects/cpp/tasty_int/build/test/src/Unity && /usr/local/Cellar/cmake/3.4.3/bin/cmake -E touch /Users/Reid/my_projects/cpp/tasty_int/cmake/Unity-prefix/src/Unity-stamp/Unity-build

Unity: CMakeFiles/Unity
Unity: CMakeFiles/Unity-complete
Unity: Unity-prefix/src/Unity-stamp/Unity-install
Unity: Unity-prefix/src/Unity-stamp/Unity-mkdir
Unity: Unity-prefix/src/Unity-stamp/Unity-download
Unity: Unity-prefix/src/Unity-stamp/Unity-update
Unity: Unity-prefix/src/Unity-stamp/Unity-patch
Unity: Unity-prefix/src/Unity-stamp/Unity-configure
Unity: Unity-prefix/src/Unity-stamp/Unity-build
Unity: CMakeFiles/Unity.dir/build.make

.PHONY : Unity

# Rule to build all files generated by this target.
CMakeFiles/Unity.dir/build: Unity

.PHONY : CMakeFiles/Unity.dir/build

CMakeFiles/Unity.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Unity.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Unity.dir/clean

CMakeFiles/Unity.dir/depend:
	cd /Users/Reid/my_projects/cpp/tasty_int/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Reid/my_projects/cpp/tasty_int /Users/Reid/my_projects/cpp/tasty_int /Users/Reid/my_projects/cpp/tasty_int/cmake /Users/Reid/my_projects/cpp/tasty_int/cmake /Users/Reid/my_projects/cpp/tasty_int/cmake/CMakeFiles/Unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Unity.dir/depend

