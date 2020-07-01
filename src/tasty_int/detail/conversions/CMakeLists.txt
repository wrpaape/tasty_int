push_namespace(conversions)
concat_namespaces("${CURRENT_NAMESPACE}" codegen CODEGEN_NAMESPACE)


add_subdirectory(code_generator)


foreach(base 36 64)
    add_library(
        ${CURRENT_NAMESPACE}value_from_base_${base}_token
        STATIC
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
        $<TARGET_OBJECTS:${CODEGEN_NAMESPACE}base_${base}_token_values>
    )
endforeach()

add_library(
    ${CURRENT_NAMESPACE}digits_from_integral
    OBJECT
    digits_from_integral.cpp
    digits_from_integral.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_from_integral
    ${tasty_int-detail-}digit_from_nonnegative_value
)

foreach(kind signed unsigned)
    add_library(
        ${CURRENT_NAMESPACE}integer_from_${kind}_integral
        STATIC
        integer_from_${kind}_integral.cpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_${kind}_integral.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    )
    target_link_libraries(
        ${CURRENT_NAMESPACE}integer_from_${kind}_integral
        ${tasty_int-detail-}sign_from_${kind}_arithmetic
        ${CURRENT_NAMESPACE}digits_from_integral
    )
endforeach()
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_from_signed_integral
    ${tasty_int-detail-}absolute_value_from_arithmetic
)

add_library(
    ${CURRENT_NAMESPACE}digits_from_floating_point
    STATIC
    digits_from_floating_point.cpp
    digits_from_floating_point.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_from_floating_point
    ${tasty_int-detail-}floating_point_digits_iterator
    ${tasty_int-detail-}size_digits_from_nonnegative_floating_point
    ${tasty_int-detail-}trailing_zero
)

add_library(
    ${CURRENT_NAMESPACE}integer_from_floating_point
    STATIC
    integer_from_floating_point.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_floating_point.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_from_floating_point
    ${tasty_int-detail-}sign_from_signed_arithmetic
    ${CURRENT_NAMESPACE}digits_from_floating_point
)

add_library(
    ${CURRENT_NAMESPACE}ensure_base_is_supported
    OBJECT
    ensure_base_is_supported.cpp
    ensure_base_is_supported.hpp
)

add_library(
    ${CURRENT_NAMESPACE}digits_from_string
    STATIC
    digits_from_string.cpp
    digits_from_string.hpp
    $<TARGET_OBJECTS:${CODEGEN_NAMESPACE}digits_per_token_table>
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}ensure_base_is_supported>
)
target_link_libraries(
    ${CURRENT_NAMESPACE}digits_from_string
    ${CURRENT_NAMESPACE}value_from_base_36_token
    ${CURRENT_NAMESPACE}value_from_base_64_token
    ${tasty_int-detail-}digit_from_nonnegative_value
)

add_library(
    ${CURRENT_NAMESPACE}base_prefix_length_from_string
    OBJECT
    base_prefix_length_from_string.cpp
    base_prefix_length_from_string.hpp
)

add_library(
    ${CURRENT_NAMESPACE}integer_from_string
    STATIC
    integer_from_string.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_string.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_from_string
    ${CURRENT_NAMESPACE}digits_from_string
    ${CURRENT_NAMESPACE}base_prefix_length_from_string
    ${tasty_int-detail-}sign_from_digits
)

foreach(base 36 64)
    add_library(
        ${CURRENT_NAMESPACE}base_${base}_token_from_value
        OBJECT
        base_${base}_token_from_value.cpp
        base_${base}_token_from_value.hpp
    )
endforeach()

add_library(
    ${CURRENT_NAMESPACE}integral_from_digits
    OBJECT
    integral_from_digits.cpp
    integral_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    ${CURRENT_NAMESPACE}unsigned_integral_from_integer
    STATIC
    unsigned_integral_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/unsigned_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}integral_from_digits>
)

add_library(
    ${CURRENT_NAMESPACE}signed_integral_from_integer
    STATIC
    signed_integral_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/signed_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}signed_integral_from_integer
    ${CURRENT_NAMESPACE}unsigned_integral_from_integer
    ${tasty_int-detail-}intmax_t_from_uintmax_t
)

add_library(
    ${CURRENT_NAMESPACE}floating_point_from_digits
    OBJECT
    floating_point_from_digits.cpp
    floating_point_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    ${CURRENT_NAMESPACE}floating_point_from_integer
    STATIC
    floating_point_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/floating_point_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}floating_point_from_integer
    ${CURRENT_NAMESPACE}floating_point_from_digits
)

add_library(
    ${CURRENT_NAMESPACE}token_values_from_digits
    OBJECT
    token_values_from_digits.cpp
    token_values_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    ${CURRENT_NAMESPACE}string_from_integer
    STATIC
    string_from_integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/string_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_36_token_from_value>
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_64_token_from_value>
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}ensure_base_is_supported>
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}token_values_from_digits>
    $<TARGET_OBJECTS:${CODEGEN_NAMESPACE}digits_per_token_table>
)

add_library(
    ${CURRENT_NAMESPACE}base_prefix_format_from_ios_format
    OBJECT
    base_prefix_format_from_ios_format.cpp
    base_prefix_format_from_ios_format.hpp
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
