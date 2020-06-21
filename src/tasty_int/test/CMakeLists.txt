include(add_google_test)


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
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_subtraction_test
    SOURCES   tasty_int_subtraction_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_multiplication_test
    SOURCES   tasty_int_multiplication_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-tasty_int_division_test
    SOURCES   tasty_int_division_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)
