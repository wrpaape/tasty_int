#include "tasty_int/detail/trailing_zero.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::have_trailing_zero;
using tasty_int::detail::trim_trailing_zero;
using tasty_int::detail::trim_trailing_zeros;

TEST(HaveTrailingZeroTest, SingleZeroDoesNotHaveTrailingZero)
{
    std::vector<digit_type> zero = { 0 };

    EXPECT_FALSE(have_trailing_zero(zero));
}

TEST(HaveTrailingZeroTest, TrailingZeroHasTrailingZero)
{
    std::vector<digit_type> trailing_zero = { 0, 0 };

    EXPECT_TRUE(have_trailing_zero(trailing_zero));
}

TEST(HaveTrailingZeroTest, TrailingNonzeroDoesNotHaveTrailingZero)
{
    std::vector<digit_type> trailing_nonzero = { 0, 1 };

    EXPECT_FALSE(have_trailing_zero(trailing_nonzero));
}

TEST(TrimTrailingZeroTest, TrimTrailingZeroDoesNotTrimSingleZero)
{
    std::vector<digit_type> digits     = { 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zero(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZeroTest, TrimTrailingZeroTrimsTrailingZero)
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

TEST(TrimTrailingZerosTest, TrimTrailingZerosDoesNotTrimSingleZeros)
{
    std::vector<digit_type> digits     = { 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zeros(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZerosTest, TrimTrailingZerosTrimsSingleTrailingZero)
{
    std::vector<digit_type> digits     = { 0, 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zeros(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZerosTest, TrimTrailingZerosTrimsMultipleTrailingZeros)
{
    std::vector<digit_type> digits     = { 0, 0, 0, 0, 0 };
    std::vector<digit_type> after_trim = { 0 };

    trim_trailing_zeros(digits);

    EXPECT_EQ(after_trim, digits);
}

TEST(TrimTrailingZerosTest, TrimTrailingZerosDoesNotTrimTrailingNonzeros)
{
    std::vector<digit_type> digits     = { 0, 1 };
    std::vector<digit_type> after_trim = { 0, 1 };

    trim_trailing_zeros(digits);

    EXPECT_EQ(after_trim, digits);
}

} // namespace
