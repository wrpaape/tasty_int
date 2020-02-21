include(add_google_test)

find_package(GTest REQUIRED)


foreach(base 36 64)
    add_google_test(
        NAME      tasty_int-detail-conversions-value_from_base_${base}_token_test
        SOURCES   value_from_base_${base}_token_test.cpp
        LIBRARIES tasty_int-detail-conversions-value_from_base_${base}_token
    )
endforeach()

foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-conversions-sign_from_${kind}_arithmetic_test
        SOURCES   sign_from_${kind}_arithmetic_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
        LIBRARIES tasty_int-detail-conversions-sign_from_${kind}_arithmetic
                  tasty_int_test
    )
endforeach()


add_google_test(
    NAME      tasty_int-detail-conversions-digit_from_nonnegative_value_test
    SOURCES   digit_from_nonnegative_value_test.cpp
    LIBRARIES tasty_int-detail-conversions-digit_from_nonnegative_value
              tasty_int_test
)


add_google_test(
    NAME      tasty_int-detail-conversions-digits_from_integral_test
    SOURCES   digits_from_integral_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-digits_from_integral>
    LIBRARIES tasty_int_test
)

add_library(
    tasty_int-detail-conversions-integer_from_integral_test_common
    OBJECT
    integer_from_integral_test_common.cpp
    integer_from_integral_test_common.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/digit_type.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/integer.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-integer_from_integral_test_common
    GTest::GTest
)
foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-conversions-integer_from_${kind}_integral_test
        SOURCES   integer_from_${kind}_integral_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-conversions-integer_from_integral_test_common>
        LIBRARIES tasty_int-detail-conversions-integer_from_${kind}_integral
                  tasty_int_test
    )
endforeach()


add_library(
    tasty_int-detail-conversions-from_floating_point_test_common
    OBJECT
    from_floating_point_test_common.cpp
    from_floating_point_test_common.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-from_floating_point_test_common
    GTest::GTest
)

add_google_test(
    NAME      tasty_int-detail-conversions-digits_from_floating_point_test
    SOURCES   digits_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-digits_from_floating_point>
              $<TARGET_OBJECTS:tasty_int-detail-conversions-from_floating_point_test_common>
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-conversions-integer_from_floating_point_test
    SOURCES   integer_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-from_floating_point_test_common>
    LIBRARIES tasty_int-detail-conversions-integer_from_floating_point
              tasty_int-detail-integer_test_common
              tasty_int_test
)


add_library(tasty_int-detail-conversions-base_support_test_common INTERFACE)
target_sources(
    tasty_int-detail-conversions-base_support_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/base_support_test_common.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-base_support_test_common
    INTERFACE
    tasty_int_test
    GTest::GTest
)

add_google_test(
    NAME      tasty_int-detail-conversions-ensure_base_is_supported_test
    SOURCES   ensure_base_is_supported_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-ensure_base_is_supported>
    LIBRARIES tasty_int-detail-conversions-base_support_test_common
)

add_library(
    tasty_int-detail-conversions-string_conversion_test_common
    OBJECT
    string_conversion_test_common.cpp
    string_conversion_test_common.hpp
)

add_google_test(
    NAME      tasty_int-detail-conversions-digits_from_string_test
    SOURCES   digits_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-string_conversion_test_common>
    LIBRARIES tasty_int-detail-conversions-digits_from_string
              tasty_int-detail-conversions-base_support_test_common
)

add_google_test(
    NAME      tasty_int-detail-conversions-base_prefix_from_string_test
    SOURCES   base_prefix_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-base_prefix_from_string>
)

add_google_test(
    NAME      tasty_int-detail-conversions-integer_from_string_test
    SOURCES   integer_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-string_conversion_test_common>
    LIBRARIES tasty_int-detail-conversions-integer_from_string
              tasty_int-detail-integer_test_common
)

add_google_test(
    NAME      tasty_int-detail-conversions-digits_from_user_type_integration_test
    SOURCES   digits_from_user_type_integration_test.cpp
              from_user_type_integration_test_common.hpp
    LIBRARIES tasty_int-detail-conversions-digits_from_integral
              tasty_int-detail-conversions-digits_from_floating_point
              tasty_int-detail-conversions-digits_from_string
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-conversions-integer_from_user_type_integration_test
    SOURCES   integer_from_user_type_integration_test.cpp
              from_user_type_integration_test_common.hpp
    LIBRARIES tasty_int-detail-conversions-integer_from_unsigned_integral
              tasty_int-detail-conversions-integer_from_signed_integral
              tasty_int-detail-conversions-integer_from_floating_point
              tasty_int-detail-conversions-integer_from_string
              tasty_int-detail-integer_test_common
              tasty_int_test
)


foreach(base 36 64)
    add_google_test(
        NAME    tasty_int-detail-conversions-base_${base}_token_from_value_test
        SOURCES base_${base}_token_from_value_test.cpp
                $<TARGET_OBJECTS:tasty_int-detail-conversions-base_${base}_token_from_value>
    )
endforeach()

add_google_test(
    NAME      tasty_int-detail-conversions-token_values_from_digits_test
    SOURCES   token_values_from_digits_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-token_values_from_digits>
              $<TARGET_OBJECTS:tasty_int-detail-conversions-string_conversion_test_common>
              $<TARGET_OBJECTS:tasty_int-detail-conversions-base_36_token_from_value>
              $<TARGET_OBJECTS:tasty_int-detail-conversions-base_64_token_from_value>
    LIBRARIES tasty_int-detail-conversions-digits_from_string
)

add_google_test(
    NAME      tasty_int-detail-conversions-string_from_integer_test
    SOURCES   string_from_integer_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-conversions-string_conversion_test_common>
    LIBRARIES tasty_int-detail-conversions-string_from_integer
              tasty_int-detail-conversions-digits_from_string
)
