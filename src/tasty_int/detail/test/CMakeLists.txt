include(add_google_test)

foreach(base 36 64)
    add_google_test(
        NAME      tasty_int-detail-value_from_base_${base}_token_test
        SOURCES   value_from_base_${base}_token_test.cpp
        LIBRARIES tasty_int-detail-value_from_base_${base}_token
    )
endforeach()

add_google_test(
    NAME    tasty_int-detail-sign_from_signed_arithmetic_test
    SOURCES sign_from_signed_arithmetic_test.cpp
            ${TASTY_INT_DETAIL_DIR}/sign_from_signed_arithmetic.hpp
)

add_google_test(
    NAME    tasty_int-detail-sign_from_unsigned_arithmetic_test
    SOURCES sign_from_unsigned_arithmetic_test.cpp
            ${TASTY_INT_DETAIL_DIR}/sign_from_unsigned_arithmetic.hpp
)

add_google_test(
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
)

add_google_test(
    NAME      tasty_int-detail-digits_from_integral_test
    SOURCES   digits_from_integral_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_from_integral>
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-int_from_integral_test
    SOURCES   int_from_integral_test.cpp
    LIBRARIES tasty_int-detail-int_from_integral
              tasty_int_test
)
