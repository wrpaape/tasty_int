include(add_google_test)

find_package(GTest REQUIRED)


add_library(
    tasty_int-detail-sign_test_common
    OBJECT
    sign_test_common.cpp
    sign_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
)

add_library(
    tasty_int-detail-integer_test_common
    STATIC
    integer_test_common.cpp
    integer_test_common.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/integer.hpp
    $<TARGET_OBJECTS:tasty_int-detail-sign_test_common>
)
target_link_libraries(
    tasty_int-detail-integer_test_common
    tasty_int-detail-integer
)


add_google_test(
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_test(
    NAME    tasty_int-detail-digit_accumulator_operations_test
    SOURCES digit_accumulator_operations_test.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(tasty_int-detail-comparison_test_common INTERFACE)
target_sources(
    tasty_int-detail-comparison_test_common
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/comparison_test_common.hpp
)
target_link_libraries(
    tasty_int-detail-comparison_test_common
    INTERFACE
    GTest::GTest
)

add_google_test(
    NAME      tasty_int-detail-digits_comparison_operators_test
    SOURCES   digits_comparison_operators_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_comparison_operators>
    LIBRARIES tasty_int-detail-comparison_test_common
)

add_google_test(
    NAME      tasty_int-detail-integer_comparison_operators_test
    SOURCES   integer_comparison_operators_test.cpp
    LIBRARIES tasty_int-detail-integer
              tasty_int-detail-comparison_test_common
              tasty_int-detail-integer_test_common
)
