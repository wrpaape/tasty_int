include(add_google_test)


add_library(
    tasty_int-detail-sign_test_common
    OBJECT
    sign_test_common.cpp
    sign_test_common.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/sign.hpp
)

add_library(
    tasty_int-detail-integer_test_common
    STATIC
    integer_test_common.cpp
    integer_test_common.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/integer.hpp
    $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
)


add_google_test(
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
            ${TASTY_INT_INCLUDE_DIR}/detail/digit_type.hpp
)

add_google_test(
    NAME    tasty_int-detail-digit_accumulator_operations_test
    SOURCES digit_accumulator_operations_test.cpp
            ${TASTY_INT_INCLUDE_DIR}/detail/digit_type.hpp
)
