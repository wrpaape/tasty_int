if(PROJECT_CMAKE_ADD_UNITY_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_UNITY_TEST_CMAKE_INCLUDED TRUE)
# ==============================================================================
# add a 'test_${NAME}' executable and CTest from sources compiled with
# ThrowTheSwitch's Unity Test framework
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR) # ExternalProject
find_package(Ruby 1.9 REQUIRED)                   # test runner generators
include(ExternalProject)
include(add_custom_test)


# Exported Variables
# ------------------------------------------------------------------------------
set(UNITY_TEST_SRC_DIR    ${PROJECT_TEST_SRC_DIR}/Unity)
set(UNITY_TEST_BUILD_DIR  ${PROJECT_BUILD_TEST_SRC_DIR}/Unity)
set(UNITY_TEST_SCRIPT_DIR ${PROJECT_TEST_SCRIPT_DIR}/unity_test)
set(UNITY_TEST_RUNNER_DIR ${PROJECT_TEST_RUNNER_DIR}/unity_test)
set(UNITY_TEST_PATCH_DIR  ${CMAKE_CURRENT_LIST_DIR}/unity_test)
set(
    UNITY_TEST_LIBRARIES
    unity_test
)


#Set Up Framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    Unity
    GIT_REPOSITORY      https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG             master
    PATCH_COMMAND       ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_PATCH_DIR}/gitignore_patches
                        ${UNITY_TEST_SRC_DIR}/.gitignore
                        COMMAND
                        ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_PATCH_DIR}/CMakeLists.txt
                        ${UNITY_TEST_SRC_DIR}/CMakeLists.txt
                        COMMAND
                        ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_PATCH_DIR}/unity_config.h
                        ${UNITY_TEST_SRC_DIR}/src/unity_config.h
    SOURCE_DIR          ${UNITY_TEST_SRC_DIR}
    BINARY_DIR          ${UNITY_TEST_BUILD_DIR}
    TEST_BEFORE_INSTALL ON
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${PROJECT_TEST_DIR}
)

 
# External API
# ------------------------------------------------------------------------------
function(add_unity_test unity_test_source)
    set(unity_test_runner_source
        "${UNITY_TEST_RUNNER_DIR}/codegen/runner__${unity_test_source}")

    # TODO: test_runners
    add_custom_test(
        ${ARGN}
        FRAMEWORK_NAME      Unity
        FRAMEWORK_LIBRARIES ${UNITY_TEST_LIBRARIES}
    )

    add_custom_command(
        OUTPUT            ${unity_test_runner_source}
        COMMAND           ${RUBY_EXECUTABLE}
                          ${UNITY_TEST_SCRIPT_DIR}/generate_test_runner.rb
                          ${unity_test_source}
                          ${unity_test_runner_source}
        WORKING_DIRECTORY ${UNITY_TEST_SCRIPT_DIR}
        COMMENT           "generate unity test runner for '${unity_test_source}'"
    )
endfunction()
