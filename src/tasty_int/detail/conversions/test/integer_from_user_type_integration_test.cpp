#include "tasty_int/detail/conversions/integer_from_unsigned_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_floating_point.hpp"
#include "tasty_int/detail/conversions/integer_from_string.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::integer_from_floating_point;
using tasty_int::detail::conversions::integer_from_signed_integral;
using tasty_int::detail::conversions::integer_from_string;
using tasty_int::detail::conversions::integer_from_unsigned_integral;
using tasty_int_test::base_10_integer_string_from_arithmetic;


class SameNegativeIntegralValueTest
    : public ::testing::TestWithParam<std::intmax_t>
{}; // class SameNegativeIntegralValueTest

TEST_P(SameNegativeIntegralValueTest,
       SameIntegerFromSignedIntegralAndFloatingPoint)
{
    std::intmax_t negative_integral_value = GetParam();
    auto floating_point_value             =
        static_cast<long double>(negative_integral_value);

    EXPECT_EQ(integer_from_signed_integral(negative_integral_value),
              integer_from_floating_point(floating_point_value));
}

TEST_P(SameNegativeIntegralValueTest, SameIntegerFromSignedIntegralAndString)
{
    std::intmax_t negative_integral_value = GetParam();
    std::string base_10_string_value      =
        base_10_integer_string_from_arithmetic(negative_integral_value);

    EXPECT_EQ(integer_from_signed_integral(negative_integral_value),
              integer_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromUserTypeIntegrationTest,
    SameNegativeIntegralValueTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);


class SameNegativeFloatingPointValueTest
    : public ::testing::TestWithParam<long double>
{}; // class SameNegativeFloatingPointValueTest

TEST_P(SameNegativeFloatingPointValueTest,
       SameIntegerFromFloatingPointAndString)
{
    long double negative_floating_point_value = GetParam();
    std::string base_10_string_value          =
        base_10_integer_string_from_arithmetic(negative_floating_point_value);

    EXPECT_EQ(integer_from_floating_point(negative_floating_point_value),
              integer_from_string(base_10_string_value, 10))
        << "base_10_string_value: " << base_10_string_value
        << ", negative_floating_point_value: " << negative_floating_point_value
        << std::endl;
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromUserTypeIntegrationTest,
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
       SameIntegerFromUnsignedIntegralAndSignedIntegral)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    auto signed_integral_value                =
        static_cast<std::intmax_t>(nonnegative_integral_value);

    EXPECT_EQ(integer_from_unsigned_integral(nonnegative_integral_value),
              integer_from_signed_integral(signed_integral_value));
}

TEST_P(SameNonnegativeIntegralTest,
       SameIntegerFromUnsignedIntegralAndFloatingPoint)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    auto floating_point_value                 =
        static_cast<long double>(nonnegative_integral_value);

    EXPECT_EQ(integer_from_unsigned_integral(nonnegative_integral_value),
              integer_from_floating_point(floating_point_value));
}

TEST_P(SameNonnegativeIntegralTest, SameIntegerFromUnsignedIntegralAndString)
{
    std::uintmax_t nonnegative_integral_value = GetParam();
    std::string base_10_string_value          =
        base_10_integer_string_from_arithmetic(nonnegative_integral_value);

    EXPECT_EQ(integer_from_unsigned_integral(nonnegative_integral_value),
              integer_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromUserTypeIntegrationTest,
    SameNonnegativeIntegralTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::intmax_t>::max(), 2
    )
);


class SameNonnegativeFloatingPointValueTest
    : public ::testing::TestWithParam<long double>
{}; // class SameNonnegativeFloatingPointValueTest

TEST_P(SameNonnegativeFloatingPointValueTest,
       SameIntegerFromFloatingPointAndString)
{
    long double nonnegative_floating_point_value = GetParam();
    std::string base_10_string_value = base_10_integer_string_from_arithmetic(
        nonnegative_floating_point_value
    );

    EXPECT_EQ(integer_from_floating_point(nonnegative_floating_point_value),
              integer_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromUserTypeIntegrationTest,
    SameNonnegativeFloatingPointValueTest,
    tasty_int_test::logarithmic_range<long double>(
        0, std::numeric_limits<long double>::max(), 1.0e80L
    )
);

} // namespace
