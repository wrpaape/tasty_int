if(PROJECT_CMAKE_TESTING_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_TESTING_CMAKE_INCLUDED TRUE)
# ==============================================================================
# enable unit testing
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(CTest) # sets BUILD_TESTING


# Exported Variables
# ------------------------------------------------------------------------------
# test directories
set(PROJECT_TEST_INCLUDE_DIR      ${PROJECT_TEST_DIR}/include)
set(PROJECT_TEST_SRC_DIR          ${PROJECT_TEST_DIR}/src)
set(PROJECT_TEST_RUNNER_DIR       ${PROJECT_TEST_SRC_DIR}/runner)
set(PROJECT_TEST_LIB_DIR          ${PROJECT_TEST_DIR}/lib)
set(PROJECT_TEST_BIN_DIR          ${PROJECT_TEST_DIR}/bin)
set(PROJECT_TEST_SCRIPT_DIR       ${PROJECT_TEST_DIR}/script)
set(PROJECT_BUILD_TEST_SRC_DIR    ${PROJECT_BUILD_DIR}/test/src)

# build and run all custom tests with verbose output
set(PROJECT_RUN_TESTS_TARGET run_tests)


# Targets
# ------------------------------------------------------------------------------
# add 'make test' to run unit tests
enable_testing()

# add 'make run_tests' to build and run tests
add_custom_target(
    ${PROJECT_RUN_TESTS_TARGET}
    COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure
)
