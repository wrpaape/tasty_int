include(set_have_type)

find_package(GTest REQUIRED)

set(TASTY_INT_TEST_INCLUDE_DIR ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test)

add_library(tasty_int_test INTERFACE)
target_sources(
    tasty_int_test
    INTERFACE
    ${TASTY_INT_TEST_INCLUDE_DIR}/logarithmic_range.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/logarithmic_range_values.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/arithmetic_types.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/signed_arithmetic_types.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/unsigned_arithmetic_types.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/detail/filter_types.hpp
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
