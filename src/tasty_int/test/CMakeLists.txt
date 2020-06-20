include(add_google_test)

find_package(GTest REQUIRED)


add_library(tasty_int-tasty_int_arithmetic_test_common INTERFACE)
target_sources(
    tasty_int-tasty_int_arithmetic_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/tasty_int_arithmetic_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/concepts.hpp
)
target_link_libraries(
    tasty_int-tasty_int_arithmetic_test_common
    INTERFACE
    tasty_int_test
    GTest::GTest
)


add_google_test(
    NAME      tasty_int-tasty_int_conversion_test
    SOURCES   tasty_int_conversion_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_unary_operations_test
    SOURCES   tasty_int_unary_operations_test.cpp
    LIBRARIES tasty_int
)

add_google_test(
    NAME      tasty_int-tasty_int_comparison_test
    SOURCES   tasty_int_comparison_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_addition_test
    SOURCES   tasty_int_addition_test.cpp
    LIBRARIES tasty_int
              tasty_int-tasty_int_arithmetic_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_subtraction_test
    SOURCES   tasty_int_subtraction_test.cpp
    LIBRARIES tasty_int
              tasty_int-tasty_int_arithmetic_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_multiplication_test
    SOURCES   tasty_int_multiplication_test.cpp
    LIBRARIES tasty_int
              tasty_int-tasty_int_arithmetic_test_common
              tasty_int_test
)
