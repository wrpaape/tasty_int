cmake_minimum_required(VERSION 3.12 FATAL_ERROR) # CMAKE_CXX_STANDARD 20

project(
    tasty_int
    VERSION 0.1.0
    LANGUAGES CXX
)

# cmake options
include(CMakeDependentOption)
set(CMAKE_CXX_STANDARD 20)
if(NOT CMAKE_BUILD_TYPE)
  set(
      CMAKE_BUILD_TYPE "Debug"
      CACHE STRING
      "Build Type, options are: Debug (default) Release RelWithDebInfo MinSizeRel."
      FORCE
  )
endif()
set(BUILD_DEBUG OFF)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_DEBUG ON)
endif()
option(BUILD_TESTING "Enable unit testing." ${BUILD_DEBUG})
cmake_dependent_option(
    BUILD_COVERAGE "Generate code coverage report." ${BUILD_DEBUG}
    BUILD_TESTING OFF
)

# config defines
set(TASTY_INT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(TASTY_INT_AUTHOR  "\"wrpaape\"")

# global directories
set(PROJECT_SRC_DIR          ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR      ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BIN_DIR          ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_LIB_DIR          ${PROJECT_SOURCE_DIR}/lib)
set(PROJECT_TEST_DIR         ${PROJECT_SOURCE_DIR}/test)
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

# enter
add_subdirectory(src)
add_subdirectory(docs)
