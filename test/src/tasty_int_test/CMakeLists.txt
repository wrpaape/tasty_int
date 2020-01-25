set(TASTY_INT_TEST_INCLUDE_DIR ${PROJECT_TEST_INCLUDE_DIR}/tasty_int_test)

add_library(tasty_int_test INTERFACE)
target_sources(
    tasty_int_test
    INTERFACE
    ${TASTY_INT_TEST_INCLUDE_DIR}/logarithmic_range.hpp
    ${TASTY_INT_TEST_INCLUDE_DIR}/logarithmic_range_values.hpp
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
