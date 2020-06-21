include(set_have_char8_t)

find_package(GTest REQUIRED)

add_library(tasty_int_test INTERFACE)
target_sources(
    tasty_int_test
    INTERFACE
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/logarithmic_range.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/logarithmic_range_values.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/nonnegative_arithmetic_values.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/base_10_integer_string_from_arithmetic.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/check_integer_result.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/comparison_tests.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/make_arithmetic_printable.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/approximately_equal.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/expect_approx.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/non_boolean_arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/signed_arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/unsigned_arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/integral_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/floating_point_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/detail/filter_types.hpp
)
set_have_char8_t(tasty_int_test)
target_link_libraries(
    tasty_int_test
    INTERFACE
    GTest::GTest
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
