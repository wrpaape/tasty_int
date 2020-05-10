#include "tasty_int/detail/is_zero.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::is_zero;


TEST(IsZeroTest, ZeroIsZero)
{
    EXPECT_TRUE(is_zero({ 0 }));
}

TEST(IsZeroTest, SingleDigitNonzeroIsNotZero)
{
    EXPECT_FALSE(is_zero({ 1 }));
}

TEST(IsZeroTest, MultiDigitNonzeroIsNotZero)
{
    EXPECT_FALSE(is_zero({ 1, 2, 3 }));
}

} // namespace
