if(PROJECT_CMAKE_TEST_ENVIRON_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_TEST_ENVIRON_CMAKE_INCLUDED TRUE)
# ==============================================================================
# enable unit testing
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(CTest) # sets BUILD_TEST_ENVIRON


# Exported Variables
# ------------------------------------------------------------------------------
# test directories
set(PROJECT_TEST_INCLUDE_DIR ${PROJECT_TEST_DIR}/include)
set(PROJECT_TEST_SRC_DIR     ${PROJECT_TEST_DIR}/src)
set(PROJECT_TEST_RUNNER_DIR  ${PROJECT_TEST_SRC_DIR}/runner)
set(PROJECT_TEST_LIB_DIR     ${PROJECT_TEST_DIR}/lib)
set(PROJECT_TEST_BIN_DIR     ${PROJECT_TEST_DIR}/bin)
set(PROJECT_TEST_SCRIPT_DIR  ${PROJECT_TEST_DIR}/script)
set(PROJECT_TEST_BUILD_DIR   ${PROJECT_BUILD_DIR}/test/src)


# Targets
# ------------------------------------------------------------------------------
# add 'make test' to run unit tests
enable_testing()

# 'make build_test' to build and run tests
add_custom_target(
    build_test
    COMMAND ${CMAKE_CTEST_COMMAND}
)

# 'make build_test_verbose' to build and run tests (with verbose output)
add_custom_target(
    build_test_verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure
)

# 'make test_verbose' to run tests (with verbose output)
add_custom_target(
    test_verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure
)

set(PROJECT_BUILD_TEST_COMMANDS build_test build_test_verbose)
