include(add_google_test)

add_google_test(
    NAME      tasty_int-tasty_int_conversions_test
    SOURCES   tasty_int_conversions_test.cpp
    LIBRARIES tasty_int
              tasty_int_test
)
