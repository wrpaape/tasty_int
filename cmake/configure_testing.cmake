# test directories
set(PROJECT_TEST_INCLUDE_DIR ${PROJECT_TEST_DIR}/include)
set(PROJECT_TEST_SRC_DIR     ${PROJECT_TEST_DIR}/src)
set(PROJECT_TEST_LIB_DIR     ${PROJECT_TEST_DIR}/lib)
set(PROJECT_TEST_BIN_DIR     ${PROJECT_TEST_DIR}/bin)

# add 'make test' to run unit tests
enable_testing()
# 'make check' runs tests with verbose output
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

# include testing frameworks
include(catch_test)  # Catch framework
include(google_test) # Google Test framework
