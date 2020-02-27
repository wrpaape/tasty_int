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

add_library(
    tasty_int-detail-trim_trailing_zero
    OBJECT
    trim_trailing_zero.cpp
    trim_trailing_zero.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-digits_comparison
    OBJECT
    digits_comparison.cpp
    digits_comparison.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
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
)

add_library(
    tasty_int-detail-digits_addition
    STATIC
    digits_addition.cpp
    digits_addition.hpp
    $<TARGET_OBJECTS:tasty_int-detail-size_digits_from_nonnegative_floating_point>
    $<TARGET_OBJECTS:tasty_int-detail-trim_trailing_zero>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-digits_addition
    tasty_int-detail-digit_from_nonnegative_value
)

add_subdirectory(conversions)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
