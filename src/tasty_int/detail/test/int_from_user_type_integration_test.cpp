#include "tasty_int/detail/int_from_unsigned_integral.hpp"
#include "tasty_int/detail/int_from_signed_integral.hpp"
#include "tasty_int/detail/int_from_floating_point.hpp"
#include "tasty_int/detail/int_from_string.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/from_user_type_integration_test_common.hpp"
#include "tasty_int/detail/test/int_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::int_from_floating_point;
using tasty_int::detail::int_from_signed_integral;
using tasty_int::detail::int_from_string;
using tasty_int::detail::int_from_unsigned_integral;
using from_user_type_integration_test_common::base_10_integer_string_from_arithmetic;


class SameNegativeIntegralValueTest
    : public ::testing::TestWithParam<std::intmax_t>
{}; // class SameNegativeIntegralValueTest

TEST_P(SameNegativeIntegralValueTest, SameIntFromSignedIntegralAndFloatingPoint)
{
    std::intmax_t negative_integral_value = GetParam();
    auto floating_point_value             =
        static_cast<long double>(negative_integral_value);

    EXPECT_EQ(int_from_signed_integral(negative_integral_value),
              int_from_floating_point(floating_point_value));
}

TEST_P(SameNegativeIntegralValueTest, SameIntFromSignedIntegralAndString)
{
    std::intmax_t negative_integral_value = GetParam();
    std::string base_10_string_value      =
        base_10_integer_string_from_arithmetic(negative_integral_value);

    EXPECT_EQ(int_from_signed_integral(negative_integral_value),
              int_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromUserTypeIntegrationTest,
    SameNegativeIntegralValueTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);


class SameNegativeFloatingPointValueTest
    : public ::testing::TestWithParam<long double>
{}; // class SameNegativeFloatingPointValueTest

TEST_P(SameNegativeFloatingPointValueTest, SameIntFromFloatingPointAndString)
{
    long double negative_floating_point_value = GetParam();
    std::string base_10_string_value          =
        base_10_integer_string_from_arithmetic(negative_floating_point_value);

    EXPECT_EQ(int_from_floating_point(negative_floating_point_value),
              int_from_string(base_10_string_value, 10))
        << "base_10_string_value: " << base_10_string_value
        << ", negative_floating_point_value: " << negative_floating_point_value << std::endl;
}

INSTANTIATE_TEST_SUITE_P(
    IntFromUserTypeIntegrationTest,
    SameNegativeFloatingPointValueTest,
    tasty_int_test::logarithmic_range<long double>(
        -std::numeric_limits<long double>::epsilon(),
        std::numeric_limits<long double>::lowest(),
        1.0e80L
    )
);


class SameNonnegativeIntegralTest
    : public ::testing::TestWithParam<std::uintmax_t>
{}; // class SameNonnegativeIntegralTest

TEST_P(SameNonnegativeIntegralTest,
       SameIntFromUnsignedIntegralAndSignedIntegral)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    auto signed_integral_value                =
        static_cast<std::intmax_t>(nonnegative_integral_value);

    EXPECT_EQ(int_from_unsigned_integral(nonnegative_integral_value),
              int_from_signed_integral(signed_integral_value));
}

TEST_P(SameNonnegativeIntegralTest, SameIntFromUnsignedIntegralAndFloatingPoint)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    auto floating_point_value                 =
        static_cast<long double>(nonnegative_integral_value);

    EXPECT_EQ(int_from_unsigned_integral(nonnegative_integral_value),
              int_from_floating_point(floating_point_value));
}

TEST_P(SameNonnegativeIntegralTest, SameIntFromUnsignedIntegralAndString)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    std::string base_10_string_value          =
        base_10_integer_string_from_arithmetic(nonnegative_integral_value);

    EXPECT_EQ(int_from_unsigned_integral(nonnegative_integral_value),
              int_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromUserTypeIntegrationTest,
    SameNonnegativeIntegralTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::intmax_t>::max(), 2
    )
);


class SameNonnegativeFloatingPointValueTest
    : public ::testing::TestWithParam<long double>
{}; // class SameNonnegativeFloatingPointValueTest

TEST_P(SameNonnegativeFloatingPointValueTest, SameIntFromFloatingPointAndString)
{
    long double nonnegative_floating_point_value = GetParam();
    std::string base_10_string_value = base_10_integer_string_from_arithmetic(
        nonnegative_floating_point_value
    );

    EXPECT_EQ(int_from_floating_point(nonnegative_floating_point_value),
              int_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromUserTypeIntegrationTest,
    SameNonnegativeFloatingPointValueTest,
    tasty_int_test::logarithmic_range<long double>(
        0, std::numeric_limits<long double>::max(), 1.0e80L
    )
);

} // namespace
