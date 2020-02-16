#include "tasty_int/detail/base_36_token_from_value.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::base_36_token_from_value;


TEST(Base36TokenFromValueTest, Value0MapsToToken0)
{
    EXPECT_EQ('0', base_36_token_from_value(0));
}

TEST(Base36TokenFromValueTest, Value1MapsToToken1)
{
    EXPECT_EQ('1', base_36_token_from_value(1));
}

TEST(Base36TokenFromValueTest, Value2MapsToToken2)
{
    EXPECT_EQ('2', base_36_token_from_value(2));
}

TEST(Base36TokenFromValueTest, Value3MapsToToken3)
{
    EXPECT_EQ('3', base_36_token_from_value(3));
}

TEST(Base36TokenFromValueTest, Value4MapsToToken4)
{
    EXPECT_EQ('4', base_36_token_from_value(4));
}

TEST(Base36TokenFromValueTest, Value5MapsToToken5)
{
    EXPECT_EQ('5', base_36_token_from_value(5));
}

TEST(Base36TokenFromValueTest, Value6MapsToToken6)
{
    EXPECT_EQ('6', base_36_token_from_value(6));
}

TEST(Base36TokenFromValueTest, Value7MapsToToken7)
{
    EXPECT_EQ('7', base_36_token_from_value(7));
}

TEST(Base36TokenFromValueTest, Value8MapsToToken8)
{
    EXPECT_EQ('8', base_36_token_from_value(8));
}

TEST(Base36TokenFromValueTest, Value9MapsToToken9)
{
    EXPECT_EQ('9', base_36_token_from_value(9));
}

TEST(Base36TokenFromValueTest, Value10MapsToTokenA)
{
    EXPECT_EQ('a', base_36_token_from_value(10));
}

TEST(Base36TokenFromValueTest, Value11MapsToTokenB)
{
    EXPECT_EQ('b', base_36_token_from_value(11));
}

TEST(Base36TokenFromValueTest, Value12MapsToTokenC)
{
    EXPECT_EQ('c', base_36_token_from_value(12));
}

TEST(Base36TokenFromValueTest, Value13MapsToTokenD)
{
    EXPECT_EQ('d', base_36_token_from_value(13));
}

TEST(Base36TokenFromValueTest, Value14MapsToTokenE)
{
    EXPECT_EQ('e', base_36_token_from_value(14));
}

TEST(Base36TokenFromValueTest, Value15MapsToTokenF)
{
    EXPECT_EQ('f', base_36_token_from_value(15));
}

TEST(Base36TokenFromValueTest, Value16MapsToTokenG)
{
    EXPECT_EQ('g', base_36_token_from_value(16));
}

TEST(Base36TokenFromValueTest, Value17MapsToTokenH)
{
    EXPECT_EQ('h', base_36_token_from_value(17));
}

TEST(Base36TokenFromValueTest, Value18MapsToTokenI)
{
    EXPECT_EQ('i', base_36_token_from_value(18));
}

TEST(Base36TokenFromValueTest, Value19MapsToTokenJ)
{
    EXPECT_EQ('j', base_36_token_from_value(19));
}

TEST(Base36TokenFromValueTest, Value20MapsToTokenK)
{
    EXPECT_EQ('k', base_36_token_from_value(20));
}

TEST(Base36TokenFromValueTest, Value21MapsToTokenL)
{
    EXPECT_EQ('l', base_36_token_from_value(21));
}

TEST(Base36TokenFromValueTest, Value22MapsToTokenM)
{
    EXPECT_EQ('m', base_36_token_from_value(22));
}

TEST(Base36TokenFromValueTest, Value23MapsToTokenN)
{
    EXPECT_EQ('n', base_36_token_from_value(23));
}

TEST(Base36TokenFromValueTest, Value24MapsToTokenO)
{
    EXPECT_EQ('o', base_36_token_from_value(24));
}

TEST(Base36TokenFromValueTest, Value25MapsToTokenP)
{
    EXPECT_EQ('p', base_36_token_from_value(25));
}

TEST(Base36TokenFromValueTest, Value26MapsToTokenQ)
{
    EXPECT_EQ('q', base_36_token_from_value(26));
}

TEST(Base36TokenFromValueTest, Value27MapsToTokenR)
{
    EXPECT_EQ('r', base_36_token_from_value(27));
}

TEST(Base36TokenFromValueTest, Value28MapsToTokenS)
{
    EXPECT_EQ('s', base_36_token_from_value(28));
}

TEST(Base36TokenFromValueTest, Value29MapsToTokenT)
{
    EXPECT_EQ('t', base_36_token_from_value(29));
}

TEST(Base36TokenFromValueTest, Value30MapsToTokenU)
{
    EXPECT_EQ('u', base_36_token_from_value(30));
}

TEST(Base36TokenFromValueTest, Value31MapsToTokenV)
{
    EXPECT_EQ('v', base_36_token_from_value(31));
}

TEST(Base36TokenFromValueTest, Value32MapsToTokenW)
{
    EXPECT_EQ('w', base_36_token_from_value(32));
}

TEST(Base36TokenFromValueTest, Value33MapsToTokenX)
{
    EXPECT_EQ('x', base_36_token_from_value(33));
}

TEST(Base36TokenFromValueTest, Value34MapsToTokenY)
{
    EXPECT_EQ('y', base_36_token_from_value(34));
}

TEST(Base36TokenFromValueTest, Value35MapsToTokenZ)
{
    EXPECT_EQ('z', base_36_token_from_value(35));
}

} // namespace
