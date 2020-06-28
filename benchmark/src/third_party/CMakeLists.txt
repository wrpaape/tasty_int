cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
project(benchmark_third_party)

include(ExternalProject)

# benchmark
# ------------------------------------------------------------------------------
set(benchmark_configuration Release)
ExternalProject_Add(
    benchmark
    GIT_REPOSITORY  https://github.com/google/benchmark.git
    GIT_TAG         master
    SOURCE_DIR      ${CMAKE_CURRENT_LIST_DIR}/benchmark
    INSTALL_DIR     ${CMAKE_INSTALL_PREFIX}
    BUILD_COMMAND   ""
                    # This command is empty because all necessary targets will
                    # be built on install stage
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
                    -DCMAKE_BUILD_TYPE:STRING=${benchmark_configuration}
                    -DBENCHMARK_ENABLE_GTEST_TESTS:BOOL=OFF
                    -DBENCHMARK_ENABLE_LTO:BOOL=${CMAKE_INTERPROCEDURAL_OPTIMIZATION}
                    # Make sure toolchain is the same
                    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    INSTALL_COMMAND ${CMAKE_COMMAND} --build  .
                                     --target install
                                     --config ${benchmark_configuration}
)
