# Copyright (c) 2012 - 2017, Lars Bilke
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# CHANGES:
#
# 2012-01-31, Lars Bilke
# - Enable Code Coverage
#
# 2013-09-17, Joakim Söderberg
# - Added support for Clang.
# - Some additional usage instructions.
#
# 2016-02-03, Lars Bilke
# - Refactored functions to use named parameters
#
# 2017-06-02, Lars Bilke
# - Merged with modified version from github.com/ufz/ogs
#
# 2019-05-06, Anatolii Kurotych
# - Remove unnecessary --coverage flag
#
# 2019-12-13, FeRD (Frank Dana)
# - Deprecate COVERAGE_LCOVR_EXCLUDES and COVERAGE_GCOVR_EXCLUDES lists in favor
#   of tool-agnostic COVERAGE_EXCLUDES variable, or EXCLUDE setup arguments.
# - CMake 3.4+: All excludes can be specified relative to BASE_DIRECTORY
# - All setup functions: accept BASE_DIRECTORY, EXCLUDE list
# - Set lcov basedir with -b argument
# - Add automatic --demangle-cpp in lcovr, if 'c++filt' is available (can be
#   overridden with NO_DEMANGLE option in setup_target_for_coverage_lcovr().)
# - Delete output dir, .info file on 'make clean'
# - Remove Python detection, since version mismatches will break gcovr
# - Minor cleanup (lowercase function names, update examples...)
#
# 2019-12-19, FeRD (Frank Dana)
# - Rename Lcov outputs, make filtered file canonical, fix cleanup for targets
#
# 2020-01-19, Bob Apthorpe
# - Added gfortran support
#
# 2020-02-17, FeRD (Frank Dana)
# - Make all add_custom_target()s VERBATIM to auto-escape wildcard characters
#   in EXCLUDEs, and remove manual escaping from gcovr targets
#
# USAGE:
#
# 1. Copy this file into your cmake modules path.
#
# 2. Add the following line to your CMakeLists.txt:
#      include(CodeCoverage)
#
# 3. Append necessary compiler flags and link necessary libraries:
#      setup_coverage_environ()
#
# 3.a (OPTIONAL) Set appropriate optimization flags, e.g. -O0, -O1 or -Og
#
# 4. If you need to exclude additional directories from the report, specify them
#    using full paths in the COVERAGE_EXCLUDES variable before calling
#    setup_target_for_coverage_*().
#    Example:
#      set(COVERAGE_EXCLUDES
#          '${PROJECT_SOURCE_DIR}/src/dir1/*'
#          '/path/to/my/src/dir2/*')
#    Or, use the EXCLUDE argument to setup_target_for_coverage_*().
#    Example:
#      setup_target_for_coverage_lcov(
#          NAME coverage
#          EXECUTABLE testrunner
#          EXCLUDE "${PROJECT_SOURCE_DIR}/src/dir1/*" "/path/to/my/src/dir2/*")
#
# 4.a NOTE: With CMake 3.4+, COVERAGE_EXCLUDES or EXCLUDE can also be set
#     relative to the BASE_DIRECTORY (default: PROJECT_SOURCE_DIR)
#     Example:
#       set(COVERAGE_EXCLUDES "dir1/*")
#       setup_target_for_coverage_gcovr_html(
#           NAME coverage
#           EXECUTABLE testrunner
#           BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
#           EXCLUDE "dir2/*")
#
# 5. Use the functions described below to create a custom make target which
#    runs your test executable and produces a code coverage report.
#
# 6. Build a Debug build:
#      cmake -DCMAKE_BUILD_TYPE=Debug ..
#      make
#      make my_coverage_target
#

include(CMakeParseArguments)
include(add_link_options)

# Check prereqs
find_program( LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
find_program( GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat )
find_program( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts/test)
find_program( CPPFILT_PATH NAMES c++filt )

function(setup_coverage_environ_for_clang)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3)
        message(
            FATAL_ERROR
            "Clang version must be 3.0.0 or greater! Aborting..."
        )
    endif()
    find_program(LLVM_COV_PATH llvm-cov)
    if(NOT LLVM_COV_PATH)
        message(FATAL_ERROR "llvm-cov not found! Aborting...")
    endif()

    add_executable(
        llvm-cov-gcov
        ${PROJECT_CMAKE_SRC_DIR}/CodeCoverage/llvm_cov_gcov.cpp
    )
    if(MSVC)
        set(EXECV_HEADER "<process.h>")
    else()
        set(EXECV_HEADER "<unistd.h>")
    endif()
    # llvm-cov requires the 'gcov' command to produce compatible output for
    # lcov, and lcov requires a single executable for its '--gcov-tool'
    # argument => provide an executable that forwards arguments to the command
    # "llvm-cov gcov".
    target_compile_definitions(
        llvm-cov-gcov
        PRIVATE
        -DTASTY_INT_LLVM_COV_PATH=\"${LLVM_COV_PATH}\"
        -DTASTY_INT_EXECV_HEADER=${EXECV_HEADER}
    )

    set(coverage_flags -fprofile-instr-generate -fcoverage-mapping)
    set(
        COVERAGE_COMPILER_FLAGS
        ${coverage_flags}
        PARENT_SCOPE
    )
    set(
        COVERAGE_LINKER_FLAGS
        ${coverage_flags}
        PARENT_SCOPE
    )
    set(GCOV_TOOL_PATH $<TARGET_FILE:llvm-cov-gcov> PARENT_SCOPE)
endfunction()

function(setup_coverage_environ_for_gnu)
    find_program(GCOV_PATH gcov)
    if(NOT GCOV_PATH)
        message(FATAL_ERROR "gcov not found! Aborting...")
    endif()

    set(COVERAGE_LIBRARIES    gcov         PARENT_SCOPE)
    set(COVERAGE_LINKER_FLAGS --coverage   PARENT_SCOPE)
    set(GCOV_TOOL_PATH        ${GCOV_PATH} PARENT_SCOPE)
endfunction()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    setup_coverage_environ_for_clang()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    setup_coverage_environ_for_gnu()
else()
    message(FATAL_ERROR "Compiler is not GNU gcc or Clang! Aborting...")
endif()

list(APPEND COVERAGE_COMPILER_FLAGS -g -fprofile-arcs -ftest-coverage)
if(MSVC)
    list(APPEND COVERAGE_COMPILER_FLAGS /O0)
else()
    list(APPEND COVERAGE_COMPILER_FLAGS -O0)
endif()
string(REPLACE ";" " " _coverage_compiler_flags "${COVERAGE_COMPILER_FLAGS}")
string(REPLACE ";" " " _coverage_linker_flags   "${COVERAGE_LINKER_FLAGS}")

set(GCOV_TOOL
    "${GCOV_TOOL_PATH}"
    CACHE FILEPATH "Path to the tool used by the coverage report generator lcov."
    FORCE )
set(CMAKE_CXX_FLAGS_COVERAGE
    "${_coverage_compiler_flags}"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
set(CMAKE_C_FLAGS_COVERAGE
    "${_coverage_compiler_flags}"
    CACHE STRING "Flags used by the C compiler during coverage builds."
    FORCE )
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${_coverage_linker_flags}"
    CACHE STRING "Flags used for linking binaries during coverage builds."
    FORCE )
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${_coverage_linker_flags}"
    CACHE STRING "Flags used by the shared libraries linker during coverage builds."
    FORCE )
set(CMAKE_LIBRARIES_COVERAGE
    "${COVERAGE_LIBRARIES}"
    CACHE STRING "Required libraries for coverage builds."
    FORCE )
mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_C_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    CMAKE_LIBRARIES_COVERAGE )

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if(NOT CMAKE_BUILD_TYPE_LOWER STREQUAL "debug")
    message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
endif()

# Defines a target for running and collection code coverage information
# Builds dependencies, runs the given executable and outputs reports.
# NOTE! The executable should always have a ZERO as exit code otherwise
# the coverage generation will not complete.
#
# setup_target_for_coverage_lcov(
#     NAME testrunner_coverage                    # New target name
#     EXECUTABLE testrunner -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
#     DEPENDENCIES testrunner                     # Dependencies to build first
#     BASE_DIRECTORY "../"                        # Base directory for report
#                                                 #  (defaults to PROJECT_SOURCE_DIR)
#     EXCLUDE "src/dir1/*" "src/dir2/*"           # Patterns to exclude (can be relative
#                                                 #  to BASE_DIRECTORY, with CMake 3.4+)
#     NO_DEMANGLE                                 # Don't demangle C++ symbols
#                                                 #  even if c++filt is found
# )
function(setup_target_for_coverage_lcov)
    set(options NO_DEMANGLE)
    set(oneValueArgs BASE_DIRECTORY NAME)
    set(multiValueArgs EXCLUDE EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES LCOV_ARGS GENHTML_ARGS)
    cmake_parse_arguments(Coverage "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT LCOV_PATH)
        message(FATAL_ERROR "lcov not found! Aborting...")
    endif() # NOT LCOV_PATH

    if(NOT GENHTML_PATH)
        message(FATAL_ERROR "genhtml not found! Aborting...")
    endif() # NOT GENHTML_PATH

    # Set base directory (as absolute path), or default to PROJECT_SOURCE_DIR
    if(${Coverage_BASE_DIRECTORY})
        get_filename_component(BASEDIR ${Coverage_BASE_DIRECTORY} ABSOLUTE)
    else()
        set(BASEDIR ${PROJECT_SOURCE_DIR})
    endif()

    # Collect excludes (CMake 3.4+: Also compute absolute paths)
    set(LCOV_EXCLUDES "")
    foreach(EXCLUDE ${Coverage_EXCLUDE} ${COVERAGE_EXCLUDES} ${COVERAGE_LCOV_EXCLUDES})
        if(CMAKE_VERSION VERSION_GREATER 3.4)
            get_filename_component(EXCLUDE ${EXCLUDE} ABSOLUTE BASE_DIR ${BASEDIR})
        endif()
        list(APPEND LCOV_EXCLUDES "${EXCLUDE}")
    endforeach()
    list(REMOVE_DUPLICATES LCOV_EXCLUDES)

    # Conditional arguments
    if(CPPFILT_PATH AND NOT ${Coverage_NO_DEMANGLE})
      set(GENHTML_EXTRA_ARGS "--demangle-cpp")
    endif()

    # Setup target
    add_custom_target(${Coverage_NAME}

        # Cleanup lcov
        COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_TOOL} -directory . -b ${BASEDIR} --zerocounters
        # Create baseline to make sure untouched files show up in the report
        COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_TOOL} -c -i -d . -b ${BASEDIR} -o ${Coverage_NAME}.base

        # Run tests
        COMMAND ${Coverage_EXECUTABLE} ${Coverage_EXECUTABLE_ARGS}

        # Capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_TOOL} --directory . -b ${BASEDIR} --capture --output-file ${Coverage_NAME}.capture
        # add baseline counters
        COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_TOOL} -a ${Coverage_NAME}.base -a ${Coverage_NAME}.capture --output-file ${Coverage_NAME}.total
        # filter collected data to final coverage report
        COMMAND ${LCOV_PATH} ${Coverage_LCOV_ARGS} --gcov-tool ${GCOV_TOOL} --remove ${Coverage_NAME}.total ${LCOV_EXCLUDES} --output-file ${Coverage_NAME}.info

        # Generate HTML output
        COMMAND ${GENHTML_PATH} ${GENHTML_EXTRA_ARGS} ${Coverage_GENHTML_ARGS} -o ${Coverage_NAME} ${Coverage_NAME}.info

        # Set output files as GENERATED (will be removed on 'make clean')
        BYPRODUCTS
            ${Coverage_NAME}.base
            ${Coverage_NAME}.capture
            ${Coverage_NAME}.total
            ${Coverage_NAME}.info
            ${Coverage_NAME}  # report directory

        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${Coverage_DEPENDENCIES}
        VERBATIM # Protect arguments to commands
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )

    # Show where to find the lcov info report
    add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
        COMMAND ;
        COMMENT "Lcov code coverage info report saved in ${Coverage_NAME}.info."
    )

    # Show info where to find the report
    add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
        COMMAND ;
        COMMENT "Open ./${Coverage_NAME}/index.html in your browser to view the coverage report."
    )

endfunction() # setup_target_for_coverage_lcov

# Defines a target for running and collection code coverage information
# Builds dependencies, runs the given executable and outputs reports.
# NOTE! The executable should always have a ZERO as exit code otherwise
# the coverage generation will not complete.
#
# setup_target_for_coverage_gcovr_xml(
#     NAME ctest_coverage                    # New target name
#     EXECUTABLE ctest -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
#     DEPENDENCIES executable_target         # Dependencies to build first
#     BASE_DIRECTORY "../"                   # Base directory for report
#                                            #  (defaults to PROJECT_SOURCE_DIR)
#     EXCLUDE "src/dir1/*" "src/dir2/*"      # Patterns to exclude (can be relative
#                                            #  to BASE_DIRECTORY, with CMake 3.4+)
# )
function(setup_target_for_coverage_gcovr_xml)

    set(options NONE)
    set(oneValueArgs BASE_DIRECTORY NAME)
    set(multiValueArgs EXCLUDE EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES)
    cmake_parse_arguments(Coverage "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GCOVR_PATH)
        message(FATAL_ERROR "gcovr not found! Aborting...")
    endif() # NOT GCOVR_PATH

    # Set base directory (as absolute path), or default to PROJECT_SOURCE_DIR
    if(${Coverage_BASE_DIRECTORY})
        get_filename_component(BASEDIR ${Coverage_BASE_DIRECTORY} ABSOLUTE)
    else()
        set(BASEDIR ${PROJECT_SOURCE_DIR})
    endif()

    # Collect excludes (CMake 3.4+: Also compute absolute paths)
    set(GCOVR_EXCLUDES "")
    foreach(EXCLUDE ${Coverage_EXCLUDE} ${COVERAGE_EXCLUDES} ${COVERAGE_GCOVR_EXCLUDES})
        if(CMAKE_VERSION VERSION_GREATER 3.4)
            get_filename_component(EXCLUDE ${EXCLUDE} ABSOLUTE BASE_DIR ${BASEDIR})
        endif()
        list(APPEND GCOVR_EXCLUDES "${EXCLUDE}")
    endforeach()
    list(REMOVE_DUPLICATES GCOVR_EXCLUDES)

    # Combine excludes to several -e arguments
    set(GCOVR_EXCLUDE_ARGS "")
    foreach(EXCLUDE ${GCOVR_EXCLUDES})
        list(APPEND GCOVR_EXCLUDE_ARGS "-e")
        list(APPEND GCOVR_EXCLUDE_ARGS "${EXCLUDE}")
    endforeach()

    add_custom_target(${Coverage_NAME}
        # Run tests
        ${Coverage_EXECUTABLE} ${Coverage_EXECUTABLE_ARGS}

        # Running gcovr
        COMMAND ${GCOVR_PATH} --xml
            -r ${BASEDIR} ${GCOVR_EXCLUDE_ARGS}
            --object-directory=${PROJECT_BINARY_DIR}
            -o ${Coverage_NAME}.xml
        BYPRODUCTS ${Coverage_NAME}.xml
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${Coverage_DEPENDENCIES}
        VERBATIM # Protect arguments to commands
        COMMENT "Running gcovr to produce Cobertura code coverage report."
    )

    # Show info where to find the report
    add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
        COMMAND ;
        COMMENT "Cobertura code coverage report saved in ${Coverage_NAME}.xml."
    )
endfunction() # setup_target_for_coverage_gcovr_xml

# Defines a target for running and collection code coverage information
# Builds dependencies, runs the given executable and outputs reports.
# NOTE! The executable should always have a ZERO as exit code otherwise
# the coverage generation will not complete.
#
# setup_target_for_coverage_gcovr_html(
#     NAME ctest_coverage                    # New target name
#     EXECUTABLE ctest -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
#     DEPENDENCIES executable_target         # Dependencies to build first
#     BASE_DIRECTORY "../"                   # Base directory for report
#                                            #  (defaults to PROJECT_SOURCE_DIR)
#     EXCLUDE "src/dir1/*" "src/dir2/*"      # Patterns to exclude (can be relative
#                                            #  to BASE_DIRECTORY, with CMake 3.4+)
# )
function(setup_target_for_coverage_gcovr_html)

    set(options NONE)
    set(oneValueArgs BASE_DIRECTORY NAME)
    set(multiValueArgs EXCLUDE EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES)
    cmake_parse_arguments(Coverage "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GCOVR_PATH)
        message(FATAL_ERROR "gcovr not found! Aborting...")
    endif() # NOT GCOVR_PATH

    # Set base directory (as absolute path), or default to PROJECT_SOURCE_DIR
    if(${Coverage_BASE_DIRECTORY})
        get_filename_component(BASEDIR ${Coverage_BASE_DIRECTORY} ABSOLUTE)
    else()
        set(BASEDIR ${PROJECT_SOURCE_DIR})
    endif()

    # Collect excludes (CMake 3.4+: Also compute absolute paths)
    set(GCOVR_EXCLUDES "")
    foreach(EXCLUDE ${Coverage_EXCLUDE} ${COVERAGE_EXCLUDES} ${COVERAGE_GCOVR_EXCLUDES})
        if(CMAKE_VERSION VERSION_GREATER 3.4)
            get_filename_component(EXCLUDE ${EXCLUDE} ABSOLUTE BASE_DIR ${BASEDIR})
        endif()
        list(APPEND GCOVR_EXCLUDES "${EXCLUDE}")
    endforeach()
    list(REMOVE_DUPLICATES GCOVR_EXCLUDES)

    # Combine excludes to several -e arguments
    set(GCOVR_EXCLUDE_ARGS "")
    foreach(EXCLUDE ${GCOVR_EXCLUDES})
        list(APPEND GCOVR_EXCLUDE_ARGS "-e")
        list(APPEND GCOVR_EXCLUDE_ARGS "${EXCLUDE}")
    endforeach()

    add_custom_target(${Coverage_NAME}
        # Run tests
        ${Coverage_EXECUTABLE} ${Coverage_EXECUTABLE_ARGS}

        # Create folder
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${Coverage_NAME}

        # Running gcovr
        COMMAND ${GCOVR_PATH} --html --html-details
            -r ${BASEDIR} ${GCOVR_EXCLUDE_ARGS}
            --object-directory=${PROJECT_BINARY_DIR}
            -o ${Coverage_NAME}/index.html

        BYPRODUCTS ${PROJECT_BINARY_DIR}/${Coverage_NAME}  # report directory
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${Coverage_DEPENDENCIES}
        VERBATIM # Protect arguments to commands
        COMMENT "Running gcovr to produce HTML code coverage report."
    )

    # Show info where to find the report
    add_custom_command(TARGET ${Coverage_NAME} POST_BUILD
        COMMAND ;
        COMMENT "Open ./${Coverage_NAME}/index.html in your browser to view the coverage report."
    )

endfunction() # setup_target_for_coverage_gcovr_html

function(setup_coverage_environ)
    if(COVERAGE_COMPILER_FLAGS)
        message(STATUS "Appending code coverage compile options: "
                       "'${COVERAGE_COMPILER_FLAGS}'.")
        add_compile_options(${COVERAGE_COMPILER_FLAGS})
    endif()
    if(COVERAGE_LINKER_FLAGS)
        message(STATUS "Appending code coverage link options: "
                       "'${COVERAGE_LINKER_FLAGS}'.")
        add_link_options(${COVERAGE_LINKER_FLAGS})
    endif()
    if(COVERAGE_LIBRARIES)
        message(STATUS "Linking code coverage libraries: "
                       "'${COVERAGE_LIBRARIES}'.")
        link_libraries(${COVERAGE_LIBRARIES})
    endif()
    if(NOT COVERAGE_COMPILER_FLAGS AND
       NOT COVERAGE_LINKER_FLAGS AND
       NOT COVERAGE_LIBRARIES)
        message(STATUS "No code coverage environment setup required.")
    endif()
endfunction()
