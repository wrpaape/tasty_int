cmake_minimum_required(VERSION 3.12 FATAL_ERROR) # CMAKE_CXX_STANDARD 20

project(
    tasty_int
    VERSION 0.1.0
    LANGUAGES CXX
)

# cmake options
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD     20)
option(BUILD_TESTING "Enable unit testing." ON)
if(NOT CMAKE_BUILD_TYPE)
  set(
      CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Build Type, options are: Debug (default) Release RelWithDebInfo MinSizeRel."
      FORCE
  )
endif()

# config defines
set(TASTY_INT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(TASTY_INT_AUTHOR  "\"wrpaape\"")

# global directories
set(PROJECT_SRC_DIR          ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR      ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BUILD_DIR        ${PROJECT_SOURCE_DIR}/build)
set(PROJECT_BIN_DIR          ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_LIB_DIR          ${PROJECT_SOURCE_DIR}/lib)
set(PROJECT_TEST_DIR         ${PROJECT_SOURCE_DIR}/test)
set(PROJECT_CMAKE_DIR        ${PROJECT_SOURCE_DIR}/cmake)
set(PROJECT_CMAKE_MODULE_DIR ${PROJECT_CMAKE_DIR}/module)

# make cmake modules available to include(), find_package()
list(APPEND CMAKE_MODULE_PATH ${PROJECT_CMAKE_MODULE_DIR})

# set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# set up common cmake module environment
include(cmake_environ)

# set up project testing environment
# to disable unit testing, invoke cmake with '-DBUILD_TESTING=OFF' from the
# command line or set BUILD_TESTING to OFF in the interactive GUI (if supported)
if(BUILD_TESTING)
    include(test_environ)
    add_subdirectory(test)
endif()

# set include directory
include_directories(${PROJECT_INCLUDE_DIR})

# enter
add_subdirectory(src)
add_subdirectory(docs)
