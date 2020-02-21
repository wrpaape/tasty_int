set(TASTY_INT_DETAIL_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(code_generator)

foreach(base 36 64)
    add_library(
        tasty_int-detail-value_from_base_${base}_token
        STATIC
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
        $<TARGET_OBJECTS:tasty_int-detail-codegen-base_${base}_token_values>
    )
endforeach()

add_library(tasty_int-detail-digit_from_nonnegative_value INTERFACE)
target_sources(
    tasty_int-detail-digit_from_nonnegative_value
    INTERFACE
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
    ${TASTY_INT_DETAIL_DIR}/digit_from_nonnegative_value.hpp
)

add_library(
    tasty_int-detail-digits_from_integral
    OBJECT
    digits_from_integral.cpp
    digits_from_integral.hpp
)
target_link_libraries(
    tasty_int-detail-digits_from_integral
    tasty_int-detail-digit_from_nonnegative_value
)

foreach(kind signed unsigned)
    add_library(tasty_int-detail-sign_from_${kind}_arithmetic INTERFACE)
    target_sources(
        tasty_int-detail-sign_from_${kind}_arithmetic
        INTERFACE
        ${TASTY_INT_DETAIL_INCLUDE_DIR}/sign.hpp
        ${TASTY_INT_DETAIL_DIR}/sign_from_${kind}_arithmetic.hpp
    )

    add_library(
        tasty_int-detail-int_from_${kind}_integral
        STATIC
        int_from_${kind}_integral.cpp
        ${TASTY_INT_DETAIL_INCLUDE_DIR}/int_from_${kind}_integral.hpp
        ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
    )
    target_link_libraries(
        tasty_int-detail-int_from_${kind}_integral
        tasty_int-detail-sign_from_${kind}_arithmetic
        tasty_int-detail-digits_from_integral
    )
endforeach()

add_library(
    tasty_int-detail-digits_from_floating_point
    OBJECT
    digits_from_floating_point.cpp
    digits_from_floating_point.hpp
)
target_link_libraries(
    tasty_int-detail-digits_from_floating_point
    tasty_int-detail-digit_from_nonnegative_value
)

add_library(
    tasty_int-detail-int_from_floating_point
    STATIC
    int_from_floating_point.cpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int_from_floating_point.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
)
target_link_libraries(
    tasty_int-detail-int_from_floating_point
    tasty_int-detail-sign_from_signed_arithmetic
    tasty_int-detail-digits_from_floating_point
)

add_library(
    tasty_int-detail-ensure_base_is_supported
    OBJECT
    ensure_base_is_supported.cpp
    ensure_base_is_supported.hpp
)

add_library(
    tasty_int-detail-digits_from_string
    STATIC
    digits_from_string.cpp
    digits_from_string.hpp
    $<TARGET_OBJECTS:tasty_int-detail-codegen-digits_per_token_table>
    $<TARGET_OBJECTS:tasty_int-detail-ensure_base_is_supported>
)
target_link_libraries(
    tasty_int-detail-digits_from_string
    tasty_int-detail-value_from_base_36_token
    tasty_int-detail-value_from_base_64_token
    tasty_int-detail-digit_from_nonnegative_value
)

add_library(
    tasty_int-detail-base_prefix_from_string
    OBJECT
    base_prefix_from_string.cpp
    base_prefix_from_string.hpp
)

add_library(
    tasty_int-detail-int_from_string
    STATIC
    int_from_string.cpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int_from_string.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
)
target_link_libraries(
    tasty_int-detail-int_from_string
    tasty_int-detail-digits_from_string
    tasty_int-detail-base_prefix_from_string
)

foreach(base 36 64)
    add_library(
        tasty_int-detail-base_${base}_token_from_value
        OBJECT
        base_${base}_token_from_value.cpp
        base_${base}_token_from_value.hpp
    )
endforeach()

add_library(
    tasty_int-detail-token_values_from_digits
    OBJECT
    token_values_from_digits.cpp
    token_values_from_digits.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)

add_library(
    tasty_int-detail-string_from_int
    STATIC
    string_from_int.cpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/string_from_int.hpp
    $<TARGET_OBJECTS:tasty_int-detail-base_36_token_from_value>
    $<TARGET_OBJECTS:tasty_int-detail-base_64_token_from_value>
    $<TARGET_OBJECTS:tasty_int-detail-codegen-digits_per_token_table>
    $<TARGET_OBJECTS:tasty_int-detail-ensure_base_is_supported>
    $<TARGET_OBJECTS:tasty_int-detail-token_values_from_digits>
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
