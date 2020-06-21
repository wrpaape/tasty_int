# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# build internal implementation
add_subdirectory(detail)

add_library(tasty_int INTERFACE)

target_sources(
    tasty_int
    INTERFACE
    ${PROJECT_INCLUDE_DIR}/tasty_int/tasty_int.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/concepts.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_comparison.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_addition.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_subtraction.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_multiplication.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_division.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_input.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer_output.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_floating_point.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_signed_integral.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_unsigned_integral.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/integer_from_string.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/floating_point_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/signed_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/unsigned_integral_from_integer.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/conversions/string_from_integer.hpp
)
target_link_libraries(
    tasty_int
    INTERFACE
    tasty_int-detail-integer_comparison
    tasty_int-detail-integer_addition
    tasty_int-detail-integer_subtraction
    tasty_int-detail-integer_multiplication
    tasty_int-detail-integer_division
    tasty_int-detail-integer_input
    tasty_int-detail-integer_output
    tasty_int-detail-conversions-integer_from_floating_point
    tasty_int-detail-conversions-integer_from_signed_integral
    tasty_int-detail-conversions-integer_from_unsigned_integral
    tasty_int-detail-conversions-integer_from_string
    tasty_int-detail-conversions-floating_point_from_integer
    tasty_int-detail-conversions-signed_integral_from_integer
    tasty_int-detail-conversions-unsigned_integral_from_integer
    tasty_int-detail-conversions-string_from_integer
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
