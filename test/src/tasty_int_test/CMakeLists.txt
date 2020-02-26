include(set_have_type)

find_package(GTest REQUIRED)

add_library(tasty_int_test INTERFACE)
target_sources(
    tasty_int_test
    INTERFACE
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/logarithmic_range.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/logarithmic_range_values.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/base_10_integer_string_from_arithmetic.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/signed_arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/unsigned_arithmetic_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/integral_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/floating_point_types.hpp
    ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test/detail/filter_types.hpp
)
target_include_directories(
    tasty_int_test
    INTERFACE
    ${GTEST_INCLUDE_DIRS}
)
set_have_type(char8_t)
target_compile_definitions(
    tasty_int_test
    INTERFACE
    COMPILE_DEFINITIONS -DHAVE_CHAR8_T=${HAVE_CHAR8_T}
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
