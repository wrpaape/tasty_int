include(add_google_test)

add_google_test(
    NAME      tasty_int_test-logarithmic_range_values_test
    SOURCES   logarithmic_range_values_test.cpp
    LIBRARIES tasty_int_test
)
