cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(
    tasty_int
    VERSION 0.1.0
    LANGUAGES CXX
)

# cmake options
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

# config defines
set(TASTY_INT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(TASTY_INT_AUTHOR  "\"wrpaape\"")

# global directories
set(PROJECT_SRC_DIR     ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_TEST_DIR    ${PROJECT_SOURCE_DIR}/test)
set(PROJECT_BIN_DIR     ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_LIB_DIR     ${PROJECT_SOURCE_DIR}/lib)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})

# misc global variables


# update include path
include_directories(
    ${PROJECT_INCLUDE_DIR}
)

# subdirectories
add_subdirectory(src)
