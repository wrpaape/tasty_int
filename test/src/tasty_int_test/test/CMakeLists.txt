include(add_google_test)

add_google_test(
    NAME      tasty_int_test-logarithmic_range_values_test
    SOURCES   logarithmic_range_values_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int_test-base_10_integer_string_from_arithmetic_test
    SOURCES   base_10_integer_string_from_arithmetic_test.cpp
    LIBRARIES tasty_int_test
)
