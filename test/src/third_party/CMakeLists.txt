cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
project(test_third_party)

include(ExternalProject)

# GTest, GMock
# ------------------------------------------------------------------------------
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
    SOURCE_DIR     ${CMAKE_CURRENT_LIST_DIR}/googletest
    INSTALL_DIR    ${CMAKE_INSTALL_PREFIX}
    CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
                   # FindGTest will choke if release version not available
                   -DCMAKE_BUILD_TYPE:STRING=Release
                   # Prevent GoogleTest from overriding our compiler/linker
                   # options when building with Visual Studio
                   -Dgtest_force_shared_crt:BOOL=ON
                   # Make sure toolchain is the same
                   -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
)
