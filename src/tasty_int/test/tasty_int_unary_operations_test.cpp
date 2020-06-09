#include "tasty_int/tasty_int.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::TastyInt;


TEST(TastyIntUnaryOperationsTest, UnaryPlusReturnsSameValue)
{
    TastyInt number(+11111);

    EXPECT_EQ(+11111, +number);
}

TEST(TastyIntUnaryOperationsTest, UnaryPlusReturnsCopy)
{
    TastyInt number(+22222);

    auto &&result = +number;

    EXPECT_NE(&number, &result);
}


TEST(TastyIntUnaryOperationsTest, UnaryMinusReturnsNegativeValue)
{
    TastyInt number(+33333);

    EXPECT_EQ(-33333, -number);
}

TEST(TastyIntUnaryOperationsTest, UnaryMinusReturnsCopy)
{
    TastyInt number(+44444);

    auto &&result = -number;

    EXPECT_NE(&number, &result);
}


TEST(TastyIntUnaryOperationsTest, PostIncrementIncrementsByOne)
{
    TastyInt number(+55554);

    ++number;

    EXPECT_EQ(+55555, number);
}

TEST(TastyIntUnaryOperationsTest, PostIncrementReturnsReference)
{
    TastyInt number(+66666);

    auto &&result = ++number;

    EXPECT_EQ(&number, &result);
}


TEST(TastyIntUnaryOperationsTest, PreIncrementIncrementsByOne)
{
    TastyInt number(+77776);

    number++;

    EXPECT_EQ(+77777, number);
}

TEST(TastyIntUnaryOperationsTest, PreIncrementReturnsCopy)
{
    TastyInt number(+88888);

    auto &&result = number++;

    EXPECT_NE(&number, &result);
}

TEST(TastyIntUnaryOperationsTest, PreIncrementReturnsOriginalValue)
{
    TastyInt number(+99999);

    EXPECT_EQ(+99999, number++);
}


TEST(TastyIntUnaryOperationsTest, PostDecrementDecrementsByOne)
{
    TastyInt number(+55555);

    --number;

    EXPECT_EQ(+55554, number);
}

TEST(TastyIntUnaryOperationsTest, PostDecrementReturnsReference)
{
    TastyInt number(+66666);

    auto &&result = --number;

    EXPECT_EQ(&number, &result);
}


TEST(TastyIntUnaryOperationsTest, PreDecrementDecrementsByOne)
{
    TastyInt number(+77777);

    number--;

    EXPECT_EQ(+77776, number);
}

TEST(TastyIntUnaryOperationsTest, PreDecrementReturnsCopy)
{
    TastyInt number(+88888);

    auto &&result = number--;

    EXPECT_NE(&number, &result);
}

TEST(TastyIntUnaryOperationsTest, PreDecrementReturnsOriginalValue)
{
    TastyInt number(+99999);

    EXPECT_EQ(+99999, number--);
}

} // namespace
