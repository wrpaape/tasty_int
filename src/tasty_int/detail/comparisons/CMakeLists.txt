add_library(
    tasty_int-detail-comparisons-digits_comparison_operators
    OBJECT
    digits_comparison_operators.cpp
    digits_comparison_operators.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
