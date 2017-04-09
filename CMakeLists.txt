cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(tasty_int VERSION 0.1 LANGUAGES CXX)

# version numbers
set(tasty_int_VERSION_MAJOR 1)
set(tasty_int_VERSION_MINOR 0)



# configurable headers
configure_file(
    "${PROJECT_SOURCE_DIR}/tasty_int_config.hpp.in"
    "${PROJECT_INCLUDE_DIR}/tasty_int_config.hpp"
)

include_directories(
    "${PROJECT_INCLUDE_DIR}"
)

add_executable(tasty_int_demo tasty_int_demo.cpp)
