include(add_google_test)

find_package(GTest REQUIRED)


foreach(base 36 64)
    add_google_test(
        NAME      ${CURRENT_NAMESPACE}value_from_base_${base}_token_test
        SOURCES   value_from_base_${base}_token_test.cpp
        LIBRARIES ${CURRENT_NAMESPACE}value_from_base_${base}_token
    )
endforeach()


add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_from_integral_test
    SOURCES   digits_from_integral_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}digits_from_integral>
    LIBRARIES tasty_int_test
)

add_library(
    ${CURRENT_NAMESPACE}integer_from_integral_test_common
    OBJECT
    integer_from_integral_test_common.cpp
    integer_from_integral_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}integer_from_integral_test_common
    GTest::GTest
)
foreach(kind signed unsigned)
    add_google_test(
        NAME      ${CURRENT_NAMESPACE}integer_from_${kind}_integral_test
        SOURCES   integer_from_${kind}_integral_test.cpp
                  $<TARGET_OBJECTS:${CURRENT_NAMESPACE}integer_from_integral_test_common>
        LIBRARIES ${CURRENT_NAMESPACE}integer_from_${kind}_integral
                  tasty_int_test
    )
endforeach()


add_library(
    ${CURRENT_NAMESPACE}from_floating_point_test_common
    OBJECT
    from_floating_point_test_common.cpp
    from_floating_point_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}from_floating_point_test_common
    GTest::GTest
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_from_floating_point_test
    SOURCES   digits_from_floating_point_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}from_floating_point_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}digits_from_floating_point
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_from_floating_point_test
    SOURCES   integer_from_floating_point_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}from_floating_point_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}integer_from_floating_point
              ${tasty_int-detail-}integer_test_common
              tasty_int_test
)


add_library(${CURRENT_NAMESPACE}base_support_test_common INTERFACE)
target_sources(
    ${CURRENT_NAMESPACE}base_support_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/base_support_test_common.hpp
)
target_link_libraries(
    ${CURRENT_NAMESPACE}base_support_test_common
    INTERFACE
    tasty_int_test
    GTest::GTest
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}ensure_base_is_supported_test
    SOURCES   ensure_base_is_supported_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}ensure_base_is_supported>
    LIBRARIES ${CURRENT_NAMESPACE}base_support_test_common
)

add_library(
    ${CURRENT_NAMESPACE}string_conversion_test_common
    OBJECT
    string_conversion_test_common.cpp
    string_conversion_test_common.hpp
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_from_string_test
    SOURCES   digits_from_string_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}string_conversion_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}digits_from_string
              ${CURRENT_NAMESPACE}base_support_test_common
)

add_google_test(
    NAME    ${CURRENT_NAMESPACE}base_prefix_length_from_string_test
    SOURCES base_prefix_length_from_string_test.cpp
            $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_prefix_length_from_string>
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_from_string_test
    SOURCES   integer_from_string_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}string_conversion_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}integer_from_string
              ${tasty_int-detail-}integer_test_common
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}digits_from_user_type_integration_test
    SOURCES   digits_from_user_type_integration_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_from_integral
              ${CURRENT_NAMESPACE}digits_from_floating_point
              ${CURRENT_NAMESPACE}digits_from_string
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integer_from_user_type_integration_test
    SOURCES   integer_from_user_type_integration_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}integer_from_unsigned_integral
              ${CURRENT_NAMESPACE}integer_from_signed_integral
              ${CURRENT_NAMESPACE}integer_from_floating_point
              ${CURRENT_NAMESPACE}integer_from_string
              ${tasty_int-detail-}integer_test_common
              tasty_int_test
)


foreach(base 36 64)
    add_google_test(
        NAME    ${CURRENT_NAMESPACE}base_${base}_token_from_value_test
        SOURCES base_${base}_token_from_value_test.cpp
                $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_${base}_token_from_value>
    )
endforeach()

add_google_test(
    NAME      ${CURRENT_NAMESPACE}integral_from_digits_test
    SOURCES   integral_from_digits_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}integral_from_digits>
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}digits_from_integral>
    LIBRARIES tasty_int_test
)

foreach(kind signed unsigned)
    add_google_test(
        NAME      ${CURRENT_NAMESPACE}${kind}_integral_from_integer_test
        SOURCES   ${kind}_integral_from_integer_test.cpp
        LIBRARIES ${CURRENT_NAMESPACE}${kind}_integral_from_integer
                  ${CURRENT_NAMESPACE}integer_from_${kind}_integral
                  tasty_int_test
    )
endforeach()
target_link_libraries(
    ${CURRENT_NAMESPACE}unsigned_integral_from_integer_test
    ${CURRENT_NAMESPACE}integer_from_signed_integral
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}floating_point_from_digits_test
    SOURCES   floating_point_from_digits_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}floating_point_from_digits>
    LIBRARIES ${CURRENT_NAMESPACE}digits_from_string
              ${CURRENT_NAMESPACE}digits_from_floating_point
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}floating_point_from_integer_test
    SOURCES   floating_point_from_integer_test.cpp
    LIBRARIES ${CURRENT_NAMESPACE}floating_point_from_integer
              ${CURRENT_NAMESPACE}integer_from_floating_point
              ${CURRENT_NAMESPACE}integer_from_string
              tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}token_values_from_digits_test
    SOURCES   token_values_from_digits_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}token_values_from_digits>
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}string_conversion_test_common>
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_36_token_from_value>
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_64_token_from_value>
    LIBRARIES ${CURRENT_NAMESPACE}digits_from_string
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}string_from_integer_test
    SOURCES   string_from_integer_test.cpp
              $<TARGET_OBJECTS:${CURRENT_NAMESPACE}string_conversion_test_common>
    LIBRARIES ${CURRENT_NAMESPACE}string_from_integer
              ${CURRENT_NAMESPACE}digits_from_string
)

add_google_test(
    NAME    ${CURRENT_NAMESPACE}base_prefix_format_from_ios_format_test
    SOURCES base_prefix_format_from_ios_format_test.cpp
            $<TARGET_OBJECTS:${CURRENT_NAMESPACE}base_prefix_format_from_ios_format>
)
