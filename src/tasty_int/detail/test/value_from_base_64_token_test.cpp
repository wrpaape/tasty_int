#include "tasty_int/detail/value_from_base_64_token.hpp"

#include <limits>

#include "gtest/gtest.h"


using tasty_int::detail::value_from_base_64_token;

TEST(ValueFromBase64TokenTest, TokensLessThanPlusAreInvalid)
{
    for (char token = std::numeric_limits<char>::min(); token < '+'; ++token)
        ASSERT_LT(value_from_base_64_token(token), 0); // assert to avoid flood
}

TEST(ValueFromBase64TokenTest, PlusTokenMapsTo62)
{
    EXPECT_EQ(62, value_from_base_64_token('+'));
}

TEST(ValueFromBase64TokenTest, TokensBetweenPlusAndForwardSlashAreInvalid)
{
    for (char token = '+' + 1; token < '/'; ++token)
        ASSERT_LT(value_from_base_64_token(token), 0); // assert to avoid flood
}

TEST(ValueFromBase64TokenTest, ForwardSlashTokenMapsTo63)
{
    EXPECT_EQ(63, value_from_base_64_token('/'));
}

TEST(ValueFromBase64TokenTest, TokensFrom0ToForwardSlashMapToValues52To61)
{
    EXPECT_EQ(52, value_from_base_64_token('0'));
    EXPECT_EQ(53, value_from_base_64_token('1'));
    EXPECT_EQ(54, value_from_base_64_token('2'));
    EXPECT_EQ(55, value_from_base_64_token('3'));
    EXPECT_EQ(56, value_from_base_64_token('4'));
    EXPECT_EQ(57, value_from_base_64_token('5'));
    EXPECT_EQ(58, value_from_base_64_token('6'));
    EXPECT_EQ(59, value_from_base_64_token('7'));
    EXPECT_EQ(60, value_from_base_64_token('8'));
    EXPECT_EQ(61, value_from_base_64_token('9'));
}

TEST(ValueFromBase64TokenTest, TokensBetween9AndAAreInvalid)
{
    for (char token = '9' + 1; token < 'A'; ++token)
        ASSERT_LT(value_from_base_64_token(token), 0); // assert to avoid flood
}

TEST(ValueFromBase64TokenTest, TokensFromCapitalAToZMapToValues0To25)
{
    EXPECT_EQ( 0, value_from_base_64_token('A'));
    EXPECT_EQ( 1, value_from_base_64_token('B'));
    EXPECT_EQ( 2, value_from_base_64_token('C'));
    EXPECT_EQ( 3, value_from_base_64_token('D'));
    EXPECT_EQ( 4, value_from_base_64_token('E'));
    EXPECT_EQ( 5, value_from_base_64_token('F'));
    EXPECT_EQ( 6, value_from_base_64_token('G'));
    EXPECT_EQ( 7, value_from_base_64_token('H'));
    EXPECT_EQ( 8, value_from_base_64_token('I'));
    EXPECT_EQ( 9, value_from_base_64_token('J'));
    EXPECT_EQ(10, value_from_base_64_token('K'));
    EXPECT_EQ(11, value_from_base_64_token('L'));
    EXPECT_EQ(12, value_from_base_64_token('M'));
    EXPECT_EQ(13, value_from_base_64_token('N'));
    EXPECT_EQ(14, value_from_base_64_token('O'));
    EXPECT_EQ(15, value_from_base_64_token('P'));
    EXPECT_EQ(16, value_from_base_64_token('Q'));
    EXPECT_EQ(17, value_from_base_64_token('R'));
    EXPECT_EQ(18, value_from_base_64_token('S'));
    EXPECT_EQ(19, value_from_base_64_token('T'));
    EXPECT_EQ(20, value_from_base_64_token('U'));
    EXPECT_EQ(21, value_from_base_64_token('V'));
    EXPECT_EQ(22, value_from_base_64_token('W'));
    EXPECT_EQ(23, value_from_base_64_token('X'));
    EXPECT_EQ(24, value_from_base_64_token('Y'));
    EXPECT_EQ(25, value_from_base_64_token('Z'));
}

TEST(ValueFromBase64TokenTest, TokensBetweenCapitalZAndLowercaseAAreInvalid)
{
    for (char token = 'Z' + 1; token < 'a'; ++token)
        ASSERT_LT(value_from_base_64_token(token), 0); // assert to avoid flood
}

TEST(ValueFromBase64TokenTest, TokensFromLowercaseAToZMapToValues26To51)
{
    EXPECT_EQ(26, value_from_base_64_token('a'));
    EXPECT_EQ(27, value_from_base_64_token('b'));
    EXPECT_EQ(28, value_from_base_64_token('c'));
    EXPECT_EQ(29, value_from_base_64_token('d'));
    EXPECT_EQ(30, value_from_base_64_token('e'));
    EXPECT_EQ(31, value_from_base_64_token('f'));
    EXPECT_EQ(32, value_from_base_64_token('g'));
    EXPECT_EQ(33, value_from_base_64_token('h'));
    EXPECT_EQ(34, value_from_base_64_token('i'));
    EXPECT_EQ(35, value_from_base_64_token('j'));
    EXPECT_EQ(36, value_from_base_64_token('k'));
    EXPECT_EQ(37, value_from_base_64_token('l'));
    EXPECT_EQ(38, value_from_base_64_token('m'));
    EXPECT_EQ(39, value_from_base_64_token('n'));
    EXPECT_EQ(40, value_from_base_64_token('o'));
    EXPECT_EQ(41, value_from_base_64_token('p'));
    EXPECT_EQ(42, value_from_base_64_token('q'));
    EXPECT_EQ(43, value_from_base_64_token('r'));
    EXPECT_EQ(44, value_from_base_64_token('s'));
    EXPECT_EQ(45, value_from_base_64_token('t'));
    EXPECT_EQ(46, value_from_base_64_token('u'));
    EXPECT_EQ(47, value_from_base_64_token('v'));
    EXPECT_EQ(48, value_from_base_64_token('w'));
    EXPECT_EQ(49, value_from_base_64_token('x'));
    EXPECT_EQ(50, value_from_base_64_token('y'));
    EXPECT_EQ(51, value_from_base_64_token('z'));
}

TEST(ValueFromBase64TokenTest, TokensGreaterThanLowercaseZAreInvalid)
{
    for (char token = 'z' + 1;; ++token) {
        ASSERT_LT(value_from_base_64_token(token), 0); // assert to avoid flood
        if (token == std::numeric_limits<char>::max())
            break; // avoid overflow at max value
    }
}

