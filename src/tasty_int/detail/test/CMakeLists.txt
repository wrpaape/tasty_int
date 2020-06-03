include(add_google_test)

find_package(GTest REQUIRED)


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
target_link_libraries(
    tasty_int-detail-integer_test_common
    tasty_int-detail-integer
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
    NAME      tasty_int-detail-digit_from_nonnegative_value_test
    SOURCES   digit_from_nonnegative_value_test.cpp
    LIBRARIES tasty_int-detail-digit_from_nonnegative_value
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-size_digits_from_nonnegative_floating_point_test
    SOURCES   size_digits_from_nonnegative_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-size_digits_from_nonnegative_floating_point>
    LIBRARIES tasty_int-detail-conversions-digits_from_floating_point
              tasty_int_test
)

foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-sign_from_${kind}_arithmetic_test
        SOURCES   sign_from_${kind}_arithmetic_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
        LIBRARIES tasty_int-detail-sign_from_${kind}_arithmetic
                  tasty_int_test
    )
endforeach()

add_google_test(
    NAME      tasty_int-detail-is_zero_test
    SOURCES   is_zero_test.cpp
    LIBRARIES tasty_int-detail-is_zero
)

add_google_test(
    NAME      tasty_int-detail-sign_from_digits_test
    SOURCES   sign_from_digits_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-sign_from_digits>
    LIBRARIES tasty_int-detail-sign_test_common
)

add_google_test(
    NAME      tasty_int-detail-trailing_zero_test
    SOURCES   trailing_zero_test.cpp
    LIBRARIES tasty_int-detail-trailing_zero
)

add_google_test(
    NAME      tasty_int-detail-flip_sign_test
    SOURCES   flip_sign_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
    LIBRARIES tasty_int-detail-flip_sign
)

add_google_test(
    NAME      tasty_int-detail-order_by_size_test
    SOURCES   order_by_size_test.cpp
    LIBRARIES tasty_int-detail-order_by_size
)

add_google_test(
    NAME      tasty_int-detail-split_digits_test
    SOURCES   split_digits_test.cpp
    LIBRARIES tasty_int-detail-split_digits
)

add_google_test(
    NAME      tasty_int-detail-count_leading_zero_bits_test
    SOURCES   count_leading_zero_bits_test.cpp
    LIBRARIES tasty_int-detail-count_leading_zero_bits
)

add_google_test(
    NAME      tasty_int-detail-next_power_of_two_test
    SOURCES   next_power_of_two_test.cpp
    LIBRARIES tasty_int-detail-next_power_of_two
)

add_library(tasty_int-detail-comparison_test_common INTERFACE)
target_sources(
    tasty_int-detail-comparison_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/comparison_test_common.hpp
)
target_link_libraries(
    tasty_int-detail-comparison_test_common
    INTERFACE
    GTest::GTest
)

add_google_test(
    NAME      tasty_int-detail-digits_comparison_test
    SOURCES   digits_comparison_test.cpp
    LIBRARIES tasty_int-detail-digits_comparison
              tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int-detail-comparison_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-integer_comparison_test
    SOURCES   integer_comparison_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-sign_from_digits>
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int-detail-conversions-integer_from_signed_integral
              tasty_int-detail-conversions-integer_from_unsigned_integral
              tasty_int-detail-conversions-integer_from_floating_point
              tasty_int-detail-comparison_test_common
              tasty_int-detail-integer_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-integral_digits_view_test
    SOURCES   integral_digits_view_test
    LIBRARIES tasty_int-detail-integral_digits_view
              tasty_int-detail-digit_from_nonnegative_value
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-floating_point_digits_iterator_test
    SOURCES   floating_point_digits_iterator_test
    LIBRARIES tasty_int-detail-floating_point_digits_iterator
              tasty_int-detail-digit_from_nonnegative_value
              tasty_int_test
)

add_library(tasty_int-detail-binary_digits_operation_test_common INTERFACE)
target_sources(
    tasty_int-detail-binary_digits_operation_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/binary_digits_operation_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME      tasty_int-detail-digits_bitwise_test
    SOURCES   digits_bitwise_test.cpp
    LIBRARIES tasty_int-detail-digits_bitwise
              tasty_int-detail-digit_from_nonnegative_value
)

add_google_test(
    NAME      tasty_int-detail-digits_addition_test
    SOURCES   digits_addition_test.cpp
    LIBRARIES tasty_int-detail-digits_addition
              tasty_int-detail-integral_digits_view
              tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int-detail-binary_digits_operation_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-integer_addition_test
    SOURCES   integer_addition_test.cpp
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-conversions-integer_from_string
              tasty_int-detail-integer_test_common
)


add_google_test(
    NAME      tasty_int-detail-digits_subtraction_test
    SOURCES   digits_subtraction_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-sign_from_digits>
    LIBRARIES tasty_int-detail-digits_subtraction
              tasty_int-detail-sign_from_signed_arithmetic
              tasty_int-detail-sign_from_unsigned_arithmetic
              tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int-detail-binary_digits_operation_test_common
              tasty_int-detail-integer_test_common
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-digits_subtraction_arithmetic_integration_test
    SOURCES   digits_subtraction_arithmetic_integration_test.cpp
    LIBRARIES tasty_int-detail-digits_subtraction
              tasty_int-detail-integer_test_common
              tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-integer_subtraction_test
    SOURCES   integer_subtraction_test.cpp
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-conversions-integer_from_floating_point
              tasty_int-detail-conversions-integer_from_string
              tasty_int-detail-integer_test_common
)

add_google_test(
    NAME      tasty_int-detail-digits_multiplication_test
    SOURCES   digits_multiplication_test.cpp
    LIBRARIES tasty_int-detail-digits_multiplication
              tasty_int-detail-integral_digits_view
              tasty_int-detail-digit_from_nonnegative_value
              tasty_int-detail-conversions-digits_from_string
)

add_google_test(
    NAME      tasty_int-detail-integer_multiplication_test
    SOURCES   integer_multiplication_test.cpp
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-conversions-integer_from_string
              tasty_int-detail-integer_test_common
)

add_google_test(
    NAME      tasty_int-detail-digits_division_test
    SOURCES   digits_division_test.cpp
    LIBRARIES tasty_int-detail-digits_division
              tasty_int-detail-digits_addition
              tasty_int-detail-digits_multiplication
              tasty_int-detail-conversions-digits_from_integral
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-integer_output_test
    SOURCES   integer_output_test.cpp
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-conversions-integer_from_signed_integral
)
