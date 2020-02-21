#include "tasty_int/detail/conversions/base_64_token_from_value.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::conversions::base_64_token_from_value;



TEST(Base64TokenFromValueTest, Value0MapsToTokenA)
{
    EXPECT_EQ('A', base_64_token_from_value(0));
}

TEST(Base64TokenFromValueTest, Value1MapsToTokenB)
{
    EXPECT_EQ('B', base_64_token_from_value(1));
}

TEST(Base64TokenFromValueTest, Value2MapsToTokenC)
{
    EXPECT_EQ('C', base_64_token_from_value(2));
}

TEST(Base64TokenFromValueTest, Value3MapsToTokenD)
{
    EXPECT_EQ('D', base_64_token_from_value(3));
}

TEST(Base64TokenFromValueTest, Value4MapsToTokenE)
{
    EXPECT_EQ('E', base_64_token_from_value(4));
}

TEST(Base64TokenFromValueTest, Value5MapsToTokenF)
{
    EXPECT_EQ('F', base_64_token_from_value(5));
}

TEST(Base64TokenFromValueTest, Value6MapsToTokenG)
{
    EXPECT_EQ('G', base_64_token_from_value(6));
}

TEST(Base64TokenFromValueTest, Value7MapsToTokenH)
{
    EXPECT_EQ('H', base_64_token_from_value(7));
}

TEST(Base64TokenFromValueTest, Value8MapsToTokenI)
{
    EXPECT_EQ('I', base_64_token_from_value(8));
}

TEST(Base64TokenFromValueTest, Value9MapsToTokenJ)
{
    EXPECT_EQ('J', base_64_token_from_value(9));
}

TEST(Base64TokenFromValueTest, Value10MapsToTokenK)
{
    EXPECT_EQ('K', base_64_token_from_value(10));
}

TEST(Base64TokenFromValueTest, Value11MapsToTokenL)
{
    EXPECT_EQ('L', base_64_token_from_value(11));
}

TEST(Base64TokenFromValueTest, Value12MapsToTokenM)
{
    EXPECT_EQ('M', base_64_token_from_value(12));
}

TEST(Base64TokenFromValueTest, Value13MapsToTokenN)
{
    EXPECT_EQ('N', base_64_token_from_value(13));
}

TEST(Base64TokenFromValueTest, Value14MapsToTokenO)
{
    EXPECT_EQ('O', base_64_token_from_value(14));
}

TEST(Base64TokenFromValueTest, Value15MapsToTokenP)
{
    EXPECT_EQ('P', base_64_token_from_value(15));
}

TEST(Base64TokenFromValueTest, Value16MapsToTokenQ)
{
    EXPECT_EQ('Q', base_64_token_from_value(16));
}

TEST(Base64TokenFromValueTest, Value17MapsToTokenR)
{
    EXPECT_EQ('R', base_64_token_from_value(17));
}

TEST(Base64TokenFromValueTest, Value18MapsToTokenS)
{
    EXPECT_EQ('S', base_64_token_from_value(18));
}

TEST(Base64TokenFromValueTest, Value19MapsToTokenT)
{
    EXPECT_EQ('T', base_64_token_from_value(19));
}

TEST(Base64TokenFromValueTest, Value20MapsToTokenU)
{
    EXPECT_EQ('U', base_64_token_from_value(20));
}

TEST(Base64TokenFromValueTest, Value21MapsToTokenV)
{
    EXPECT_EQ('V', base_64_token_from_value(21));
}

TEST(Base64TokenFromValueTest, Value22MapsToTokenW)
{
    EXPECT_EQ('W', base_64_token_from_value(22));
}

TEST(Base64TokenFromValueTest, Value23MapsToTokenX)
{
    EXPECT_EQ('X', base_64_token_from_value(23));
}

TEST(Base64TokenFromValueTest, Value24MapsToTokenY)
{
    EXPECT_EQ('Y', base_64_token_from_value(24));
}

TEST(Base64TokenFromValueTest, Value25MapsToTokenZ)
{
    EXPECT_EQ('Z', base_64_token_from_value(25));
}

TEST(Base64TokenFromValueTest, Value26MapsToTokena)
{
    EXPECT_EQ('a', base_64_token_from_value(26));
}

TEST(Base64TokenFromValueTest, Value27MapsToTokenb)
{
    EXPECT_EQ('b', base_64_token_from_value(27));
}

TEST(Base64TokenFromValueTest, Value28MapsToTokenc)
{
    EXPECT_EQ('c', base_64_token_from_value(28));
}

TEST(Base64TokenFromValueTest, Value29MapsToTokend)
{
    EXPECT_EQ('d', base_64_token_from_value(29));
}

TEST(Base64TokenFromValueTest, Value30MapsToTokene)
{
    EXPECT_EQ('e', base_64_token_from_value(30));
}

TEST(Base64TokenFromValueTest, Value31MapsToTokenf)
{
    EXPECT_EQ('f', base_64_token_from_value(31));
}

TEST(Base64TokenFromValueTest, Value32MapsToTokeng)
{
    EXPECT_EQ('g', base_64_token_from_value(32));
}

TEST(Base64TokenFromValueTest, Value33MapsToTokenh)
{
    EXPECT_EQ('h', base_64_token_from_value(33));
}

TEST(Base64TokenFromValueTest, Value34MapsToTokeni)
{
    EXPECT_EQ('i', base_64_token_from_value(34));
}

TEST(Base64TokenFromValueTest, Value35MapsToTokenj)
{
    EXPECT_EQ('j', base_64_token_from_value(35));
}

TEST(Base64TokenFromValueTest, Value36MapsToTokenk)
{
    EXPECT_EQ('k', base_64_token_from_value(36));
}

TEST(Base64TokenFromValueTest, Value37MapsToTokenl)
{
    EXPECT_EQ('l', base_64_token_from_value(37));
}

TEST(Base64TokenFromValueTest, Value38MapsToTokenm)
{
    EXPECT_EQ('m', base_64_token_from_value(38));
}

TEST(Base64TokenFromValueTest, Value39MapsToTokenn)
{
    EXPECT_EQ('n', base_64_token_from_value(39));
}

TEST(Base64TokenFromValueTest, Value40MapsToTokeno)
{
    EXPECT_EQ('o', base_64_token_from_value(40));
}

TEST(Base64TokenFromValueTest, Value41MapsToTokenp)
{
    EXPECT_EQ('p', base_64_token_from_value(41));
}

TEST(Base64TokenFromValueTest, Value42MapsToTokenq)
{
    EXPECT_EQ('q', base_64_token_from_value(42));
}

TEST(Base64TokenFromValueTest, Value43MapsToTokenr)
{
    EXPECT_EQ('r', base_64_token_from_value(43));
}

TEST(Base64TokenFromValueTest, Value44MapsToTokens)
{
    EXPECT_EQ('s', base_64_token_from_value(44));
}

TEST(Base64TokenFromValueTest, Value45MapsToTokent)
{
    EXPECT_EQ('t', base_64_token_from_value(45));
}

TEST(Base64TokenFromValueTest, Value46MapsToTokenu)
{
    EXPECT_EQ('u', base_64_token_from_value(46));
}

TEST(Base64TokenFromValueTest, Value47MapsToTokenv)
{
    EXPECT_EQ('v', base_64_token_from_value(47));
}

TEST(Base64TokenFromValueTest, Value48MapsToTokenw)
{
    EXPECT_EQ('w', base_64_token_from_value(48));
}

TEST(Base64TokenFromValueTest, Value49MapsToTokenx)
{
    EXPECT_EQ('x', base_64_token_from_value(49));
}

TEST(Base64TokenFromValueTest, Value50MapsToTokeny)
{
    EXPECT_EQ('y', base_64_token_from_value(50));
}

TEST(Base64TokenFromValueTest, Value51MapsToTokenz)
{
    EXPECT_EQ('z', base_64_token_from_value(51));
}

TEST(Base64TokenFromValueTest, Value52MapsToToken0)
{
    EXPECT_EQ('0', base_64_token_from_value(52));
}

TEST(Base64TokenFromValueTest, Value53MapsToToken1)
{
    EXPECT_EQ('1', base_64_token_from_value(53));
}

TEST(Base64TokenFromValueTest, Value54MapsToToken2)
{
    EXPECT_EQ('2', base_64_token_from_value(54));
}

TEST(Base64TokenFromValueTest, Value55MapsToToken3)
{
    EXPECT_EQ('3', base_64_token_from_value(55));
}

TEST(Base64TokenFromValueTest, Value56MapsToToken4)
{
    EXPECT_EQ('4', base_64_token_from_value(56));
}

TEST(Base64TokenFromValueTest, Value57MapsToToken5)
{
    EXPECT_EQ('5', base_64_token_from_value(57));
}

TEST(Base64TokenFromValueTest, Value58MapsToToken6)
{
    EXPECT_EQ('6', base_64_token_from_value(58));
}

TEST(Base64TokenFromValueTest, Value59MapsToToken7)
{
    EXPECT_EQ('7', base_64_token_from_value(59));
}

TEST(Base64TokenFromValueTest, Value60MapsToToken8)
{
    EXPECT_EQ('8', base_64_token_from_value(60));
}

TEST(Base64TokenFromValueTest, Value61MapsToToken9)
{
    EXPECT_EQ('9', base_64_token_from_value(61));
}

TEST(Base64TokenFromValueTest, Value62MapsToTokenPlus)
{
    EXPECT_EQ('+', base_64_token_from_value(62));
}

TEST(Base64TokenFromValueTest, Value63MapsToTokenForwardSlash)
{
    EXPECT_EQ('/', base_64_token_from_value(63));
}

} // namespace
