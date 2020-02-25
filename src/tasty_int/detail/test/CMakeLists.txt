include(add_google_test)


add_library(
    tasty_int-detail-sign_test_common
    OBJECT
    sign_test_common.cpp
    sign_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
)

add_library(
    tasty_int-detail-integer_test_common
    STATIC
    integer_test_common.cpp
    integer_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
)


add_google_test(
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME    tasty_int-detail-digit_accumulator_operations_test
    SOURCES digit_accumulator_operations_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME      tasty_int-detail-comparisons-digits_comparison_operators_test
    SOURCES   digits_comparison_operators_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_comparison_operators>
)
