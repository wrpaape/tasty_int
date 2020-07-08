include(namespaces)
include(add_google_test)


push_namespace(tasty_int_test)


add_google_test(
    NAME      ${CURRENT_NAMESPACE}make_arithmetic_printable_test
    SOURCES   make_arithmetic_printable_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}logarithmic_range_values_test
    SOURCES   logarithmic_range_values_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}sample_arithmetic_test
    SOURCES   sample_arithmetic_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}base_10_integer_string_from_arithmetic_test
    SOURCES   base_10_integer_string_from_arithmetic_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}approximately_equal_test
    SOURCES   approximately_equal_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}cartesian_product_test
    SOURCES   cartesian_product_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}combine_types_test
    SOURCES   combine_types_test.cpp
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      ${CURRENT_NAMESPACE}floating_point_integral_limits_test
    SOURCES   floating_point_integral_limits_test.cpp
    LIBRARIES tasty_int_test
)
