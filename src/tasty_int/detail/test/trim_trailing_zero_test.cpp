#include "tasty_int/detail/trim_trailing_zero.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::trim_trailing_zero;


TEST(TrimTrailingZeroTest, TrimTrailingZeroDoesNotTrimSingleZero)
{
    std::vector<digit_type> digits     = { 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zero(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZeroTest, TrimTrailingZeroTrimsExtraTrailingZero)
{
    std::vector<digit_type> digits     = { 0, 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zero(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZeroTest, TrimTrailingZeroDoesNotTrimTrailingNonzero)
{
    std::vector<digit_type> digits     = { 0, 1 };
    std::vector<digit_type> after_trim = { 0, 1 };

    trim_trailing_zero(digits);

    EXPECT_EQ(after_trim, digits);
}

} // namespace
