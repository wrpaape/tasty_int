include(add_google_test)

find_package(GTest REQUIRED)


add_library(
    ${CURRENT_NAMESPACE}sign_test_common
    OBJECT
    sign_test_common.cpp
    sign_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
)

add_library(
    ${CURRENT_NAMESPACE}integer_test_common
    STATIC
    integer_test_common.cpp
    integer_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_test_common>
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_test_common
    ${CURRENT_NAMESPACE}integer_comparison
)

add_library(
    ${CURRENT_NAMESPACE}integer_arithmetic_test_common
    STATIC
    integer_arithmetic_test_common.cpp
    integer_arithmetic_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_arithmetic_test_common
    ${CURRENT_NAMESPACE}integer_test_common
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}signed_integral_from_integer
    ${tasty_int-detail-conversions-}floating_point_from_integer
    tasty_int_test
    GTest::GTest
)


add_google_test(
    NAME    ${CURRENT_NAMESPACE}sign_test
    SOURCES sign_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
            $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_test_common>
)

add_google_test(
    NAME    ${CURRENT_NAMESPACE}digit_type_test
    SOURCES digit_type_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME    ${CURRENT_NAMESPACE}digit_accumulator_operations_test
    SOURCES digit_accumulator_operations_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digit_from_nonnegative_value_test
    SOURCES   digit_from_nonnegative_value_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digit_from_nonnegative_value
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point_test
    SOURCES   size_digits_from_nonnegative_floating_point_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point>
    LIBRARIES ${tasty_int-detail-conversions-}digits_from_floating_point
              tasty_int_test
)

foreach(kind signed unsigned)
    add_google_test(
        NAME      ${CURRENT_NAMESPACE}sign_from_${kind}_arithmetic_test
        SOURCES   sign_from_${kind}_arithmetic_test.cpp
                  $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_test_common>
        LIBRARIES ${CURRENT_NAMESPACE}sign_from_${kind}_arithmetic
                  tasty_int_test
    )
endforeach()

add_google_test(
    NAME      ${CURRENT_NAMESPACE}absolute_value_from_arithmetic_test
    SOURCES   absolute_value_from_arithmetic_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}absolute_value_from_arithmetic
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}is_zero_test
    SOURCES   is_zero_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}is_zero
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}sign_from_digits_test
    SOURCES   sign_from_digits_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_from_digits>
    LIBRARIES ${CURRENT_NAMESPACE}sign_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}trailing_zero_test
    SOURCES   trailing_zero_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}trailing_zero
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}order_by_size_test
    SOURCES   order_by_size_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}order_by_size
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}split_digits_test
    SOURCES   split_digits_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}split_digits
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}count_leading_zero_bits_test
    SOURCES   count_leading_zero_bits_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}count_leading_zero_bits
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t_test
    SOURCES   intmax_t_from_uintmax_t_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}next_power_of_two_test
    SOURCES   next_power_of_two_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}next_power_of_two
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_operation_test
    SOURCES   integer_operation_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}integer_operation
              ${CURRENT_NAMESPACE}sign_from_signed_arithmetic
              ${CURRENT_NAMESPACE}sign_from_unsigned_arithmetic
              ${CURRENT_NAMESPACE}integer_test_common
              tasty_int_test
)

add_library(${CURRENT_NAMESPACE}comparison_test_common INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}comparison_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/comparison_test_common.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}comparison_test_common
    INTERFACE
    GTest::GTest
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_comparison_test
    SOURCES   digits_comparison_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_comparison
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              ${CURRENT_NAMESPACE}comparison_test_common
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_comparison_test
    SOURCES   integer_comparison_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_from_digits>
    LIBRARIES ${CURRENT_NAMESPACE}integer_comparison
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              ${tasty_int-detail-conversions-}integer_from_signed_integral
              ${tasty_int-detail-conversions-}integer_from_unsigned_integral
              ${tasty_int-detail-conversions-}integer_from_floating_point
              ${CURRENT_NAMESPACE}comparison_test_common
              ${CURRENT_NAMESPACE}integer_test_common
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integral_digits_view_test
    SOURCES   integral_digits_view_test
    LIBRARIES ${CURRENT_NAMESPACE}integral_digits_view
              ${CURRENT_NAMESPACE}digit_from_nonnegative_value
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}extended_digit_accumulator_test
    SOURCES   extended_digit_accumulator_test
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}extended_digit_accumulator>
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}floating_point_digits_iterator_test
    SOURCES   floating_point_digits_iterator_test
    LIBRARIES ${CURRENT_NAMESPACE}floating_point_digits_iterator
              ${CURRENT_NAMESPACE}digit_from_nonnegative_value
              tasty_int_test
)

add_library(${CURRENT_NAMESPACE}binary_digits_operation_test_common INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}binary_digits_operation_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/binary_digits_operation_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_bitwise_test
    SOURCES   digits_bitwise_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_bitwise
              ${CURRENT_NAMESPACE}digit_from_nonnegative_value
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_addition_test
    SOURCES   digits_addition_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_addition
              ${CURRENT_NAMESPACE}integral_digits_view
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              ${tasty_int-detail-conversions-}integral_from_digits
              ${tasty_int-detail-conversions-}floating_point_from_digits
              ${CURRENT_NAMESPACE}binary_digits_operation_test_common
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_addition_test
    SOURCES   integer_addition_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_addition
              ${tasty_int-detail-conversions-}integer_from_string
              ${CURRENT_NAMESPACE}integer_arithmetic_test_common
              ${CURRENT_NAMESPACE}integer_test_common
)


add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_subtraction_test
    SOURCES   digits_subtraction_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}sign_from_digits>
    LIBRARIES ${CURRENT_NAMESPACE}digits_subtraction
              ${CURRENT_NAMESPACE}sign_from_signed_arithmetic
              ${CURRENT_NAMESPACE}sign_from_unsigned_arithmetic
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              ${CURRENT_NAMESPACE}binary_digits_operation_test_common
              ${CURRENT_NAMESPACE}integer_test_common
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_subtraction_arithmetic_integration_test
    SOURCES   digits_subtraction_arithmetic_integration_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_subtraction
              ${CURRENT_NAMESPACE}integer_test_common
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_subtraction_test
    SOURCES   integer_subtraction_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_subtraction
              ${tasty_int-detail-conversions-}integer_from_floating_point
              ${tasty_int-detail-conversions-}integer_from_string
              ${CURRENT_NAMESPACE}integer_arithmetic_test_common
              ${CURRENT_NAMESPACE}integer_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_multiplication_test
    SOURCES   digits_multiplication_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_multiplication
              ${CURRENT_NAMESPACE}integral_digits_view
              ${CURRENT_NAMESPACE}digit_from_nonnegative_value
              ${tasty_int-detail-conversions-}digits_from_string
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_multiplication_test
    SOURCES   integer_multiplication_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_multiplication
              ${tasty_int-detail-conversions-}integer_from_string
              ${CURRENT_NAMESPACE}integer_arithmetic_test_common
              ${CURRENT_NAMESPACE}integer_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_division_test
    SOURCES   digits_division_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_division
              ${CURRENT_NAMESPACE}digits_addition
              ${CURRENT_NAMESPACE}digits_multiplication
              ${tasty_int-detail-conversions-}digits_from_integral
              ${tasty_int-detail-conversions-}digits_from_floating_point
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_division_test
    SOURCES   integer_division_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_division
              ${tasty_int-detail-conversions-}integer_from_string
              ${CURRENT_NAMESPACE}integer_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_input_test
    SOURCES   integer_input_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_input
              ${CURRENT_NAMESPACE}integer_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_output_test
    SOURCES   integer_output_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_output
              ${tasty_int-detail-conversions-}integer_from_signed_integral
)
