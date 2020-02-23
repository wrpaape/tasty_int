include(add_google_test)

add_google_test(
    NAME      tasty_int-detail-comparisons-digits_comparison_operators_test
    SOURCES   digits_comparison_operators_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-comparisons-digits_comparison_operators>
)
