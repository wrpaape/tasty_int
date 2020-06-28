cmake_minimum_required(VERSION 3.12 FATAL_ERROR) # CMAKE_CXX_STANDARD 20

project(
    TastyInt
    VERSION 1.0.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

# cmake options
include(CMakeDependentOption)
if(NOT CMAKE_BUILD_TYPE)
  set(
      CMAKE_BUILD_TYPE "Debug"
      CACHE STRING
      "Build Type, options are: Debug (default) Release RelWithDebInfo MinSizeRel."
      FORCE
  )
endif()
set(BUILD_DEBUG OFF)
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)
if(CMAKE_BUILD_TYPE_LOWER STREQUAL "debug")
    set(BUILD_DEBUG ON)
endif()
option(BUILD_TESTING "Enable unit testing." ${BUILD_DEBUG})
set(have_coverage_supported_compiler FALSE)
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
   set(have_coverage_supported_compiler TRUE)
endif()
cmake_dependent_option(
    BUILD_COVERAGE "Generate code coverage report." ${BUILD_TESTING}
    "BUILD_DEBUG;BUILD_TESTING;have_coverage_supported_compiler"
    OFF
)
option(BUILD_BENCHMARKING "Enable micro benchmarks." ON)
# @todo TODO: https://svn.boost.org/trac10/wiki/BestPracticeHandbook
# @todo TODO: offer coverage as a build type and remove BUILD_COVERAGE
# @todo TODO: remove in-source 'bin' and 'lib' directories

# config defines
set(TASTY_INT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(TASTY_INT_AUTHOR  "\"wrpaape\"")

# global directories
set(PROJECT_SRC_DIR          ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR      ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BIN_DIR          ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_LIB_DIR          ${PROJECT_SOURCE_DIR}/lib)
set(PROJECT_TEST_DIR         ${PROJECT_SOURCE_DIR}/test)
set(PROJECT_BENCHMARK_DIR    ${PROJECT_SOURCE_DIR}/benchmark)
set(PROJECT_CMAKE_DIR        ${PROJECT_SOURCE_DIR}/cmake)
set(PROJECT_CMAKE_MODULE_DIR ${PROJECT_CMAKE_DIR}/module)

# make cmake modules available to include(), find_package()
list(APPEND CMAKE_MODULE_PATH ${PROJECT_CMAKE_MODULE_DIR})

# set up common cmake environment
include(cmake_environ)

# set up project testing environment
# to disable unit testing, invoke cmake with '-DBUILD_TESTING=OFF' from the
# command line or set BUILD_TESTING to OFF in the interactive GUI (if supported)
if(BUILD_TESTING)
    include(test_environ)
    add_subdirectory(test)
endif()

# set up project micro benchmarking environment
# to disable benchmarks, invoke cmake with '-DBUILD_BENCHMARKING=OFF' from the
# command line or set BUILD_BENCHMARKING to OFF in the interactive GUI (if
# supported)
if(BUILD_BENCHMARKING)
    include(benchmark_environ)
    add_subdirectory(benchmark)
endif()

# enter
add_subdirectory(src)
add_subdirectory(docs)
