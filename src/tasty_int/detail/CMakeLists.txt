add_library(tasty_int-detail-digit_from_nonnegative_value INTERFACE)
target_sources(
    tasty_int-detail-digit_from_nonnegative_value
    INTERFACE
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
    ${PROJECT_SRC_DIR}/tasty_int/detail/digit_from_nonnegative_value.hpp
)

add_library(
    tasty_int-detail-size_digits_from_nonnegative_floating_point
    OBJECT
    size_digits_from_nonnegative_floating_point.cpp
    size_digits_from_nonnegative_floating_point.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

foreach(kind signed unsigned)
    add_library(tasty_int-detail-sign_from_${kind}_arithmetic INTERFACE)
    target_sources(
        tasty_int-detail-sign_from_${kind}_arithmetic
        INTERFACE
        ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
        ${PROJECT_SRC_DIR}/tasty_int/detail/sign_from_${kind}_arithmetic.hpp
    )
endforeach()
add_library(
    tasty_int-detail-sign_from_digits
    OBJECT
    sign_from_digits.cpp
    sign_from_digits.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-trailing_zero
    OBJECT
    trailing_zero.cpp
    trailing_zero.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(tasty_int-detail-integral_digits_view INTERFACE)
target_sources(
    tasty_int-detail-integral_digits_view
    INTERFACE
    ${PROJECT_SRC_DIR}/tasty_int/detail/integral_digits_view.hpp
)
target_link_libraries(
    tasty_int-detail-integral_digits_view
    INTERFACE
    tasty_int-detail-digit_from_nonnegative_value
)

add_library(tasty_int-detail-floating_point_digits_iterator INTERFACE)
target_sources(
    tasty_int-detail-floating_point_digits_iterator
    INTERFACE
    ${PROJECT_SRC_DIR}/tasty_int/detail/floating_point_digits_iterator.hpp
)
target_link_libraries(
    tasty_int-detail-floating_point_digits_iterator
    INTERFACE
    tasty_int-detail-digit_from_nonnegative_value
)

add_library(
    tasty_int-detail-digits_comparison
    STATIC
    digits_comparison.cpp
    digits_comparison.hpp
    $<TARGET_OBJECTS:tasty_int-detail-size_digits_from_nonnegative_floating_point>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-digits_comparison
    tasty_int-detail-floating_point_digits_iterator
    tasty_int-detail-integral_digits_view
)

add_library(
    tasty_int-detail-digits_addition
    STATIC
    digits_addition.cpp
    digits_addition.hpp
    $<TARGET_OBJECTS:tasty_int-detail-size_digits_from_nonnegative_floating_point>
    $<TARGET_OBJECTS:tasty_int-detail-trailing_zero>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-digits_addition
    tasty_int-detail-digit_from_nonnegative_value
    tasty_int-detail-floating_point_digits_iterator
    tasty_int-detail-integral_digits_view
)

add_library(
    tasty_int-detail-digits_subtraction
    STATIC
    digits_subtraction.cpp
    digits_subtraction.hpp
    $<TARGET_OBJECTS:tasty_int-detail-size_digits_from_nonnegative_floating_point>
    $<TARGET_OBJECTS:tasty_int-detail-trailing_zero>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-digits_subtraction
    tasty_int-detail-digits_addition
    tasty_int-detail-digit_from_nonnegative_value
    tasty_int-detail-floating_point_digits_iterator
    tasty_int-detail-sign_from_digits
)

add_library(
    tasty_int-detail-integer
    STATIC
    integer.cpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
)
target_link_libraries(
    tasty_int-detail-integer
    tasty_int-detail-digits_comparison
    tasty_int-detail-digits_addition
    tasty_int-detail-digits_subtraction
    tasty_int-detail-sign_from_signed_arithmetic
    tasty_int-detail-sign_from_unsigned_arithmetic
)

add_subdirectory(conversions)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
