add_subdirectory(code_generator)

foreach(base 36 64)
    add_library(
        tasty_int-detail-conversions-value_from_base_${base}_token
        STATIC
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
        $<TARGET_OBJECTS:tasty_int-detail-conversions-codegen-base_${base}_token_values>
    )
endforeach()

add_library(
    tasty_int-detail-conversions-digits_from_integral
    OBJECT
    digits_from_integral.cpp
    digits_from_integral.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-digits_from_integral
    tasty_int-detail-digit_from_nonnegative_value
)

foreach(kind signed unsigned)
    add_library(
        tasty_int-detail-conversions-integer_from_${kind}_integral
        STATIC
        integer_from_${kind}_integral.cpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_${kind}_integral.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    )
    target_link_libraries(
        tasty_int-detail-conversions-integer_from_${kind}_integral
        tasty_int-detail-sign_from_${kind}_arithmetic
        tasty_int-detail-conversions-digits_from_integral
    )
endforeach()

add_library(
    tasty_int-detail-conversions-digits_from_floating_point
    STATIC
    digits_from_floating_point.cpp
    digits_from_floating_point.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-digits_from_floating_point
    tasty_int-detail-floating_point_digits_iterator
    tasty_int-detail-size_digits_from_nonnegative_floating_point
    tasty_int-detail-trailing_zero
)

add_library(
    tasty_int-detail-conversions-integer_from_floating_point
    STATIC
    integer_from_floating_point.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_floating_point.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-integer_from_floating_point
    tasty_int-detail-sign_from_signed_arithmetic
    tasty_int-detail-conversions-digits_from_floating_point
)

add_library(
    tasty_int-detail-conversions-ensure_base_is_supported
    OBJECT
    ensure_base_is_supported.cpp
    ensure_base_is_supported.hpp
)

add_library(
    tasty_int-detail-conversions-digits_from_string
    STATIC
    digits_from_string.cpp
    digits_from_string.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-codegen-digits_per_token_table>
    $<TARGET_OBJECTS:tasty_int-detail-conversions-ensure_base_is_supported>
)
target_link_libraries(
    tasty_int-detail-conversions-digits_from_string
    tasty_int-detail-conversions-value_from_base_36_token
    tasty_int-detail-conversions-value_from_base_64_token
    tasty_int-detail-digit_from_nonnegative_value
)

add_library(
    tasty_int-detail-conversions-base_prefix_length_from_string
    OBJECT
    base_prefix_length_from_string.cpp
    base_prefix_length_from_string.hpp
)

add_library(
    tasty_int-detail-conversions-integer_from_string
    STATIC
    integer_from_string.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_string.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-integer_from_string
    tasty_int-detail-conversions-digits_from_string
    tasty_int-detail-conversions-base_prefix_length_from_string
    tasty_int-detail-sign_from_digits
)

foreach(base 36 64)
    add_library(
        tasty_int-detail-conversions-base_${base}_token_from_value
        OBJECT
        base_${base}_token_from_value.cpp
        base_${base}_token_from_value.hpp
    )
endforeach()

add_library(
    tasty_int-detail-conversions-integral_from_digits
    OBJECT
    integral_from_digits.cpp
    integral_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-conversions-unsigned_integral_from_integer
    STATIC
    unsigned_integral_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/unsigned_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-integral_from_digits>
)

add_library(
    tasty_int-detail-conversions-signed_integral_from_integer
    STATIC
    signed_integral_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/signed_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-signed_integral_from_integer
    tasty_int-detail-conversions-unsigned_integral_from_integer
    tasty_int-detail-intmax_t_from_uintmax_t
)

add_library(
    tasty_int-detail-conversions-floating_point_from_digits
    OBJECT
    floating_point_from_digits.cpp
    floating_point_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-conversions-floating_point_from_integer
    STATIC
    floating_point_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/floating_point_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-floating_point_from_integer
    tasty_int-detail-conversions-floating_point_from_digits
)

add_library(
    tasty_int-detail-conversions-token_values_from_digits
    OBJECT
    token_values_from_digits.cpp
    token_values_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-conversions-string_from_integer
    STATIC
    string_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/string_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-base_36_token_from_value>
    $<TARGET_OBJECTS:tasty_int-detail-conversions-base_64_token_from_value>
    $<TARGET_OBJECTS:tasty_int-detail-conversions-codegen-digits_per_token_table>
    $<TARGET_OBJECTS:tasty_int-detail-conversions-ensure_base_is_supported>
    $<TARGET_OBJECTS:tasty_int-detail-conversions-token_values_from_digits>
)

add_library(
    tasty_int-detail-conversions-base_prefix_format_from_ios_format
    OBJECT
    base_prefix_format_from_ios_format.cpp
    base_prefix_format_from_ios_format.hpp
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
