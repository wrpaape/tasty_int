push_namespace(detail)


add_library(
    ${CURRENT_NAMESPACE}trailing_zero
    STATIC
    trailing_zero.cpp
    trailing_zero.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(${CURRENT_NAMESPACE}intmax_t_from_uintmax_t INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/intmax_t_from_uintmax_t.hpp
)

add_library(${CURRENT_NAMESPACE}absolute_value_from_arithmetic INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}absolute_value_from_arithmetic
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/absolute_value_from_arithmetic.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/concepts.hpp
)

add_subdirectory(conversions)

add_library(${CURRENT_NAMESPACE}digit_from_nonnegative_value INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/digit_from_nonnegative_value.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    ${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point
    OBJECT
    size_digits_from_nonnegative_floating_point.cpp
    size_digits_from_nonnegative_floating_point.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

foreach(kind signed unsigned)
    add_library(${CURRENT_NAMESPACE}sign_from_${kind}_arithmetic INTERFACE)
    target_sources(
        ${CURRENT_NAMESPACE}sign_from_${kind}_arithmetic
        INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/sign_from_${kind}_arithmetic.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    )
endforeach()

add_library(${CURRENT_NAMESPACE}is_zero INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}is_zero
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/is_zero.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    ${CURRENT_NAMESPACE}sign_from_digits
    OBJECT
    sign_from_digits.cpp
    sign_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}sign_from_digits
    PRIVATE
    ${CURRENT_NAMESPACE}is_zero
)

add_library(${CURRENT_NAMESPACE}order_by_size INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}order_by_size
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/order_by_size.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(${CURRENT_NAMESPACE}split_digits INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}split_digits
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/split_digits.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}split_digits
    INTERFACE
    ${CURRENT_NAMESPACE}trailing_zero
)

add_library(
    ${CURRENT_NAMESPACE}count_leading_zero_bits
    OBJECT
    count_leading_zero_bits.cpp
    count_leading_zero_bits.hpp
)
include(set_intrinsic_count_leading_zero_bits)
set_intrinsic_count_leading_zero_bits(${CURRENT_NAMESPACE}count_leading_zero_bits)

add_library(
    ${CURRENT_NAMESPACE}next_power_of_two
    STATIC
    next_power_of_two.cpp
    next_power_of_two.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}count_leading_zero_bits>
)

add_library(${CURRENT_NAMESPACE}integral_digits_view INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}integral_digits_view
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/integral_digits_view.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integral_digits_view
    INTERFACE
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
)

add_library(
    ${CURRENT_NAMESPACE}extended_digit_accumulator
    OBJECT
    extended_digit_accumulator.cpp
    extended_digit_accumulator.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}extended_digit_accumulator
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}integral_digits_view
)

add_library(${CURRENT_NAMESPACE}floating_point_digits_iterator INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}floating_point_digits_iterator
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/floating_point_digits_iterator.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}floating_point_digits_iterator
    INTERFACE
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
)

add_library(
    ${CURRENT_NAMESPACE}digits_comparison
    STATIC
    digits_comparison.cpp
    digits_comparison.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_comparison
    ${CURRENT_NAMESPACE}floating_point_digits_iterator
    ${CURRENT_NAMESPACE}integral_digits_view
)

add_library(
    ${CURRENT_NAMESPACE}digits_bitwise
    STATIC
    digits_bitwise.cpp
    digits_bitwise.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}count_leading_zero_bits>
)

target_link_libraries(
    ${CURRENT_NAMESPACE}digits_bitwise
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}is_zero
)

add_library(
    ${CURRENT_NAMESPACE}digits_addition
    STATIC
    digits_addition.cpp
    digits_addition.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}floating_point_digits_iterator
    ${CURRENT_NAMESPACE}integral_digits_view
    ${CURRENT_NAMESPACE}order_by_size
    ${CURRENT_NAMESPACE}trailing_zero
)

add_library(
    ${CURRENT_NAMESPACE}digits_subtraction
    STATIC
    digits_subtraction.cpp
    digits_subtraction.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}size_digits_from_nonnegative_floating_point>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_subtraction
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}floating_point_digits_iterator
    ${CURRENT_NAMESPACE}integral_digits_view
    ${CURRENT_NAMESPACE}sign_from_digits
    ${CURRENT_NAMESPACE}trailing_zero
)

add_library(
    ${CURRENT_NAMESPACE}digits_multiplication
    STATIC
    digits_multiplication.cpp
    digits_multiplication.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_multiplication
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}is_zero
    ${CURRENT_NAMESPACE}order_by_size
    ${CURRENT_NAMESPACE}split_digits
    ${CURRENT_NAMESPACE}trailing_zero
    ${CURRENT_NAMESPACE}integral_digits_view
    ${CURRENT_NAMESPACE}digits_bitwise
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}digits_subtraction
    ${tasty_int-detail-conversions-}digits_from_floating_point
)

add_library(
    ${CURRENT_NAMESPACE}digits_division
    STATIC
    digits_division.cpp
    digits_division.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}extended_digit_accumulator>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_division
    ${CURRENT_NAMESPACE}digit_from_nonnegative_value
    ${CURRENT_NAMESPACE}is_zero
    ${CURRENT_NAMESPACE}split_digits
    ${CURRENT_NAMESPACE}trailing_zero
    ${CURRENT_NAMESPACE}next_power_of_two
    ${CURRENT_NAMESPACE}integral_digits_view
    ${CURRENT_NAMESPACE}digits_comparison
    ${CURRENT_NAMESPACE}digits_bitwise
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}digits_subtraction
    ${CURRENT_NAMESPACE}digits_multiplication
    ${tasty_int-detail-conversions-}digits_from_floating_point
)
add_library(${CURRENT_NAMESPACE}integer_operation INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}integer_operation
    INTERFACE
    ${PROJECT_INCLUDE_DIR}/tasty_int/concepts.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_operation
    INTERFACE
    ${CURRENT_NAMESPACE}sign_from_signed_arithmetic
    ${CURRENT_NAMESPACE}sign_from_unsigned_arithmetic
    ${CURRENT_NAMESPACE}absolute_value_from_arithmetic
)

add_library(
    ${CURRENT_NAMESPACE}integer_comparison
    STATIC
    integer_comparison.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_comparison.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/concepts.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_comparison
    ${CURRENT_NAMESPACE}integer_operation
    ${CURRENT_NAMESPACE}digits_comparison
    ${CURRENT_NAMESPACE}sign_from_signed_arithmetic
)

add_library(
    ${CURRENT_NAMESPACE}integer_addition
    STATIC
    integer_addition.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_addition.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_addition
    ${CURRENT_NAMESPACE}integer_operation
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}digits_subtraction
    ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}floating_point_from_integer
)
add_library(
    ${CURRENT_NAMESPACE}integer_subtraction
    STATIC
    integer_subtraction.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_subtraction.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_subtraction
    ${CURRENT_NAMESPACE}integer_operation
    ${CURRENT_NAMESPACE}digits_addition
    ${CURRENT_NAMESPACE}digits_subtraction
    ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}floating_point_from_integer
)

add_library(
    ${CURRENT_NAMESPACE}integer_multiplication
    STATIC
    integer_multiplication.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_multiplication.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_multiplication
    ${CURRENT_NAMESPACE}integer_operation
    ${CURRENT_NAMESPACE}digits_multiplication
    ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}floating_point_from_integer
)

add_library(
    ${CURRENT_NAMESPACE}integer_division
    STATIC
    integer_division.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_division.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_division
    ${CURRENT_NAMESPACE}integer_operation
    ${CURRENT_NAMESPACE}digits_division
    ${CURRENT_NAMESPACE}sign_from_digits
    ${CURRENT_NAMESPACE}intmax_t_from_uintmax_t
    ${tasty_int-detail-conversions-}integral_from_digits
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}floating_point_from_integer
)

add_library(
    ${CURRENT_NAMESPACE}integer_input
    STATIC
    integer_input.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_input.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_input
    ${tasty_int-detail-conversions-}integer_from_string
)

add_library(
    ${CURRENT_NAMESPACE}integer_output
    STATIC
    integer_output.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_output.hpp
    $<TARGET_OBJECTS:${tasty_int-detail-conversions-}base_prefix_format_from_ios_format>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_output
    ${tasty_int-detail-conversions-}string_from_integer
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARKING)
    add_subdirectory(benchmark)
endif()
