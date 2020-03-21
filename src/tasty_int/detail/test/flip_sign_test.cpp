#include "tasty_int/detail/flip_sign.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/sign_test_common.hpp"


namespace {

using tasty_int::detail::Sign;


TEST(FlipSignTest, PositiveFlipsToNegative)
{
    EXPECT_EQ(Sign::NEGATIVE, flip_sign(Sign::POSITIVE));
}

TEST(FlipSignTest, NegativeFlipsToPositive)
{
    EXPECT_EQ(Sign::POSITIVE, flip_sign(Sign::NEGATIVE));
}

TEST(FlipSignTest, ZeroFlipsToZero)
{
    EXPECT_EQ(Sign::ZERO, flip_sign(Sign::ZERO));
}

} // namespace
