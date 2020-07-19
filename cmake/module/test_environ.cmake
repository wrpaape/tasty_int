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


# Targets
# ------------------------------------------------------------------------------
# add 'make test' to run unit tests
enable_testing()

# 'make build_test' to build and run tests
add_custom_target(
    build-test
    COMMAND ${CMAKE_CTEST_COMMAND}
)

# 'make build-test-verbose' to build and run tests (with verbose output)
add_custom_target(
    build-test-verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure
)

# 'make test_verbose' to run tests (with verbose output)
add_custom_target(
    test-verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure
)

set(PROJECT_BUILD_TEST_COMMANDS build-test build-test-verbose)

if(BUILD_COVERAGE)
    include(CodeCoverage)

    setup_target_for_coverage_lcov(
        NAME       coverage
        EXECUTABLE ${CMAKE_CTEST_COMMAND}
        EXCLUDE    "/usr/*" "/*/usr/*"     # system headers
                   "*/third_party/*"       # third party code
                   "*/gtest/*" "*/gmock/*" # testing framework
                   "*/test/*"              # unit tests
                   "*/cmake/*"             # cmake executables
                   "*/benchmark/*"         # benchmark framework, benchmarks
                   "*/generate_*.cpp"      # code generators
    )
    
    setup_coverage_environ()
endif()
