#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::size_digits_from_nonnegative_floating_point;
using tasty_int::detail::conversions::digits_from_floating_point;


class SizeDigitsFromNonnegativeFloatingPointTest
    : public ::testing::TestWithParam<long double>
{}; // class SizeDigitsFromNonnegativeFloatingPointTest


TEST_P(SizeDigitsFromNonnegativeFloatingPointTest,
       ExpectEqualToOrOneGreaterThanActualSizeDigits)
{
    long double value  = GetParam();
    auto actual_digits = digits_from_floating_point(value);

    std::size_t size_digits =
        size_digits_from_nonnegative_floating_point(value);

    EXPECT_LE(size_digits - actual_digits.size(), 1)
        << "size_digits="            << size_digits
        << ", actual_digits.size()=" << actual_digits.size();
}

INSTANTIATE_TEST_SUITE_P(
    SizeDigitsFromNonnegativeFloatingPointTest,
    SizeDigitsFromNonnegativeFloatingPointTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0L, std::numeric_limits<long double>::max(), 1.0e5L
    )
);

} // namespace
