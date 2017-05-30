if(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED TRUE)
# ==============================================================================
# add a 'test_${NAME}' executable and CTest from sources compiled with the
# Google Test/Mock framework
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
find_package(Threads REQUIRED)                    # We need thread support
include(ExternalProject)
include(add_custom_test)


# Exported Variables
# ------------------------------------------------------------------------------
set(GOOGLE_TEST_SRC_DIR   ${PROJECT_TEST_SRC_DIR}/googletest)
set(GOOGLE_TEST_BUILD_DIR ${PROJECT_BUILD_TEST_SRC_DIR}/googletest)


# Set Up Framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
    SOURCE_DIR     ${GOOGLE_TEST_SRC_DIR}
    BINARY_DIR     ${GOOGLE_TEST_BUILD_DIR}
    INSTALL_DIR    ${PROJECT_TEST_DIR}
    CMAKE_ARGS     "-DCMAKE_INSTALL_PREFIX=${PROJECT_TEST_DIR}"
)


# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(
    GOOGLE_TEST_LIBRARIES
    gtest
    gtest_main
    gmock
    gmock_main
    ${CMAKE_THREAD_LIBS_INIT}
)
 
# External API
# ------------------------------------------------------------------------------
function(add_google_test)
    add_custom_test(
        ${ARGN}
        FRAMEWORK_NAME      googletest
        FRAMEWORK_SOURCES   ${GOOGLE_TEST_SOURCES}
        FRAMEWORK_LIBRARIES ${GOOGLE_TEST_LIBRARIES}
    )
endfunction()
