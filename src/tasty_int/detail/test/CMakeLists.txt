include(add_google_test)

find_package(GTest REQUIRED)


add_library(
    tasty_int-detail-sign_test_common
    OBJECT
    sign_test_common.cpp
    sign_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/sign.hpp
)

add_library(
    tasty_int-detail-int_test_common
    STATIC
    int_test_common.cpp
    int_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
    $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
)


foreach(base 36 64)
    add_google_test(
        NAME      tasty_int-detail-value_from_base_${base}_token_test
        SOURCES   value_from_base_${base}_token_test.cpp
        LIBRARIES tasty_int-detail-value_from_base_${base}_token
    )
endforeach()

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
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
            ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)


add_google_test(
    NAME    tasty_int-detail-digit_accumulator_operations_test
    SOURCES digit_accumulator_operations_test.cpp
            ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)


add_google_test(
    NAME      tasty_int-detail-digit_from_nonnegative_value_test
    SOURCES   digit_from_nonnegative_value_test.cpp
    LIBRARIES tasty_int-detail-digit_from_nonnegative_value
              tasty_int_test
)


add_google_test(
    NAME      tasty_int-detail-digits_from_integral_test
    SOURCES   digits_from_integral_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_from_integral>
    LIBRARIES tasty_int_test
)

add_library(
    tasty_int-detail-int_from_integral_test_common
    OBJECT
    int_from_integral_test_common.cpp
    int_from_integral_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
)
target_link_libraries(
    tasty_int-detail-int_from_integral_test_common
    GTest::GTest
)
foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-int_from_${kind}_integral_test
        SOURCES   int_from_${kind}_integral_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-int_from_integral_test_common>
        LIBRARIES tasty_int-detail-int_from_${kind}_integral
                  tasty_int_test
    )
endforeach()


add_library(
    tasty_int-detail-from_floating_point_test_common
    OBJECT
    from_floating_point_test_common.cpp
    from_floating_point_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-from_floating_point_test_common
    GTest::GTest
)

add_google_test(
    NAME      tasty_int-detail-digits_from_floating_point_test
    SOURCES   digits_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_from_floating_point>
              $<TARGET_OBJECTS:tasty_int-detail-from_floating_point_test_common>
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-int_from_floating_point_test
    SOURCES   int_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-from_floating_point_test_common>
    LIBRARIES tasty_int-detail-int_from_floating_point
              tasty_int-detail-int_test_common
              tasty_int_test
)


add_library(
    tasty_int-detail-from_string_test_common
    OBJECT
    from_string_test_common.cpp
    from_string_test_common.hpp
)

add_google_test(
    NAME      tasty_int-detail-digits_from_string_test
    SOURCES   digits_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-from_string_test_common>
    LIBRARIES tasty_int-detail-digits_from_string
)

add_google_test(
    NAME      tasty_int-detail-base_prefix_from_string_test
    SOURCES   base_prefix_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-base_prefix_from_string>
)

add_google_test(
    NAME      tasty_int-detail-int_from_string_test
    SOURCES   int_from_string_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-from_string_test_common>
    LIBRARIES tasty_int-detail-int_from_string
              tasty_int-detail-int_test_common
)

add_google_test(
    NAME      tasty_int-detail-digits_from_user_type_integration_test
    SOURCES   digits_from_user_type_integration_test.cpp
              from_user_type_integration_test_common.hpp
    LIBRARIES tasty_int-detail-digits_from_integral
              tasty_int-detail-digits_from_floating_point
              tasty_int-detail-digits_from_string
              tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-int_from_user_type_integration_test
    SOURCES   int_from_user_type_integration_test.cpp
              from_user_type_integration_test_common.hpp
    LIBRARIES tasty_int-detail-int_from_unsigned_integral
              tasty_int-detail-int_from_signed_integral
              tasty_int-detail-int_from_floating_point
              tasty_int-detail-int_from_string
              tasty_int-detail-int_test_common
              tasty_int_test
)


foreach(base 36 64)
    add_google_test(
        NAME    tasty_int-detail-base_${base}_token_from_value_test
        SOURCES base_${base}_token_from_value_test.cpp
                $<TARGET_OBJECTS:tasty_int-detail-base_${base}_token_from_value>
    )
endforeach()
