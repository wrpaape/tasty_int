#include "tasty_int/detail/count_leading_zero_bits.hpp"

#include <type_traits>

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::count_leading_zero_bits;


TEST(CountLeadingZeroBitsTest, DenseBitPatternTest)
{
    for (std::uintmax_t value = std::numeric_limits<std::uintmax_t>::max(),
         expected_count       = 0;
         value > 0;
         value >>= 1,
         ++expected_count)
        EXPECT_EQ(expected_count, count_leading_zero_bits(value));
}

TEST(CountLeadingZeroBitsTest, SingleBitTest)
{
    constexpr std::uintmax_t MAX_EXPONENT =
        std::numeric_limits<std::uintmax_t>::digits - 1;

    for (std::uintmax_t value = std::uintmax_t(1) << MAX_EXPONENT,
         expected_count       = 0;
         value > 0;
         value >>= 1,
         ++expected_count)
        EXPECT_EQ(expected_count, count_leading_zero_bits(value));
}

} // namespace
