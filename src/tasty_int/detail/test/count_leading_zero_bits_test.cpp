#include "tasty_int/detail/count_leading_zero_bits.hpp"

#include <type_traits>

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::count_leading_zero_bits;


constexpr auto MAX_EXPONENT = std::numeric_limits<std::uintmax_t>::digits - 1;

class CountLeadingZeroBitsTest : public ::testing::TestWithParam<int>
{}; // class CountLeadingZeroBitsTest

TEST_P(CountLeadingZeroBitsTest, DenseBitPatternTest)
{
    auto shift          = GetParam();
    auto value          = std::numeric_limits<std::uintmax_t>::max() >> shift;
    auto expected_count = shift;

    EXPECT_EQ(expected_count, count_leading_zero_bits(value));
}

TEST_P(CountLeadingZeroBitsTest, SingleBitTest)
{
    auto shift          = GetParam();
    auto value          = std::uintmax_t(1) << shift;
    auto expected_count = MAX_EXPONENT - shift;

    EXPECT_EQ(expected_count, count_leading_zero_bits(value));
}

INSTANTIATE_TEST_SUITE_P(
    CountLeadingZeroBitsTest,
    CountLeadingZeroBitsTest,
    ::testing::Range(0, MAX_EXPONENT)
);


} // namespace
