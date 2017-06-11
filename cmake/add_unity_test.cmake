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
set(UNITY_TEST_SRC_DIR     ${PROJECT_TEST_SRC_DIR}/Unity)
set(UNITY_TEST_BUILD_DIR   ${PROJECT_BUILD_TEST_SRC_DIR}/Unity)
set(UNITY_TEST_SCRIPT_DIR  ${PROJECT_TEST_SCRIPT_DIR}/Unity)
set(UNITY_TEST_RUNNER_DIR  ${PROJECT_TEST_RUNNER_DIR}/Unity)
set(UNITY_TEST_PATCH_DIR   ${CMAKE_CURRENT_LIST_DIR}/Unity)
set(UNITY_TEST_INCLUDE_DIR ${PROJECT_TEST_INCLUDE_DIR}/unity)
set(
    UNITY_TEST_LIBRARIES
    unity
)
set(UNITY_TEST_GITIGNORE_PATCH          ${UNITY_TEST_PATCH_DIR}/gitignore_patch)
set(UNITY_TEST_CMAKE_LISTS_TXT          ${UNITY_TEST_PATCH_DIR}/CMakeLists.txt)
set(UNITY_TEST_CONFIG_HEADER_TEMPLATE   ${UNITY_TEST_PATCH_DIR}/unity_config.h)


# Set Up Framework
# ------------------------------------------------------------------------------
add_custom_target(
    unity_test_patch_files
    DEPENDS ${UNITY_TEST_GITIGNORE_PATCH}
            ${UNITY_TEST_CMAKE_LISTS_TXT}
            ${UNITY_TEST_CONFIG_HEADER_TEMPLATE}
)

ExternalProject_Add(
    Unity
    DEPENDS             unity_test_patch_files
    GIT_REPOSITORY      https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG             master
    PATCH_COMMAND       ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_GITIGNORE_PATCH}
                        ${UNITY_TEST_SRC_DIR}/.gitignore
                        COMMAND
                        ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_CMAKE_LISTS_TXT}
                        ${UNITY_TEST_SRC_DIR}/CMakeLists.txt
                        COMMAND
                        ${CMAKE_COMMAND} -E copy
                        ${UNITY_TEST_CONFIG_HEADER_TEMPLATE}
                        ${UNITY_TEST_SRC_DIR}/unity_config.h
    SOURCE_DIR          ${UNITY_TEST_SRC_DIR}
    BINARY_DIR          ${UNITY_TEST_BUILD_DIR}
    TEST_BEFORE_INSTALL ON
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${PROJECT_TEST_DIR}
)

# Locate 'unity' library created by 'Unity'
# ------------------------------------------------------------------------------
add_library(unity SHARED IMPORTED GLOBAL)
set(filename
    ${CMAKE_SHARED_LIBRARY_PREFIX}unity${CMAKE_SHARED_LIBRARY_SUFFIX})
set_target_properties(
    unity
    PROPERTIES
    IMPORTED_LOCATION             ${PROJECT_TEST_LIB_DIR}/${filename}
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_TEST_INCLUDE_DIR}
)
add_dependencies(unity Unity)

 
# External API
# ------------------------------------------------------------------------------
function(add_unity_test)
    # first source file is the unity test file
    list(FIND ARGV SOURCES i_sources)
    math(EXPR i_first_source "1+0${i_sources}") # bug: -1 + 1, 1 + -1
                                                # not supported
    if(i_first_source EQUAL 0) # -1 (not found) + 1 or last element
        message(
            FATAL_ERROR
            "add_unity_test -- required 'SOURCES' list not provided"
        )
    endif()
    list(GET ARGV ${i_first_source} unity_test_filename)

    # generate test runner source file
    set(unity_test_source
        ${CMAKE_CURRENT_SOURCE_DIR}/${unity_test_filename})

    set(unity_test_runner_source
        "${UNITY_TEST_RUNNER_DIR}/codegen/run_${unity_test_filename}")
    add_custom_command(
        OUTPUT            ${unity_test_runner_source}
        DEPENDS           ${unity_test_source}
        COMMAND           ${RUBY_EXECUTABLE}
                          ${UNITY_TEST_SCRIPT_DIR}/generate_test_runner.rb
                          ${unity_test_source}
                          ${unity_test_runner_source}
                          --framework="unity/unity"
        WORKING_DIRECTORY ${UNITY_TEST_SCRIPT_DIR}
        COMMENT           "generate unity test runner for '${unity_test_source}'"
    )

    add_custom_test(
        ${ARGV}
        FRAMEWORK_NAME         Unity
        FRAMEWORK_SOURCES      ${unity_test_runner_source}
        FRAMEWORK_LIBRARIES    ${UNITY_TEST_LIBRARIES}
    )
endfunction()
