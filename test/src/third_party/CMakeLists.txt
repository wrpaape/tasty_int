cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
project(test_third_party)

include(ExternalProject)

# GTest, GMock
# ------------------------------------------------------------------------------
# FindGTest will fail if non-debug version (no "d" suffix on libraries) is not
# available
set(googletest_configuration Release)
ExternalProject_Add(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         master
    SOURCE_DIR      ${CMAKE_CURRENT_LIST_DIR}/googletest
    INSTALL_DIR     ${CMAKE_INSTALL_PREFIX}
    BUILD_COMMAND   ""
                    # This command is empty because all necessary targets will
                    # be built on install stage
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
                    -DCMAKE_BUILD_TYPE:STRING=${googletest_configuration}
                    # Prevent GoogleTest from overriding our compiler/linker
                    # options when building with Visual Studio
                    -Dgtest_force_shared_crt:BOOL=ON
                    # Make sure toolchain is the same
                    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    INSTALL_COMMAND ${CMAKE_COMMAND} --build  .
                                     --target install
                                     --config ${googletest_configuration}
)
