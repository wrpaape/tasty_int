add_library(
    tasty_int-detail-digits_comparison_operators
    OBJECT
    digits_comparison_operators.cpp
    digits_comparison_operators.hpp
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
    tasty_int-detail-digits_comparison_operators
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

add_subdirectory(conversions)
