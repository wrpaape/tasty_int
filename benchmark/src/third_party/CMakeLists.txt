cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
project(benchmark_third_party)

include(ExternalProject)

# benchmark
# ------------------------------------------------------------------------------
ExternalProject_Add(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        master
    SOURCE_DIR     ${CMAKE_CURRENT_LIST_DIR}/benchmark
    INSTALL_DIR    ${CMAKE_INSTALL_PREFIX}
    CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_INSTALL_PREFIX}
                   -DCMAKE_BUILD_TYPE:STRING=Release
                   -DBENCHMARK_ENABLE_GTEST_TESTS:BOOL=OFF
)
