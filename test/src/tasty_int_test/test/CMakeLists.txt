include(add_google_test)

add_google_test(
    NAME      tasty_int_test-make_arithmetic_printable_test
    SOURCES   make_arithmetic_printable_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int_test-logarithmic_range_values_test
    SOURCES   logarithmic_range_values_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int_test-sample_arithmetic_test
    SOURCES   sample_arithmetic_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int_test-base_10_integer_string_from_arithmetic_test
    SOURCES   base_10_integer_string_from_arithmetic_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int_test-approximately_equal_test
    SOURCES   approximately_equal_test.cpp
    LIBRARIES tasty_int_test
)
