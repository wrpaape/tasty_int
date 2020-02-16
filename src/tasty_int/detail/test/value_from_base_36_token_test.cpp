#include "tasty_int/detail/value_from_base_36_token.hpp"

#include <limits>

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::value_from_base_36_token;


TEST(ValueFromBase36TokenTest, TokensLessThan0AreInvalid)
{
    for (char token = std::numeric_limits<char>::min(); token < '0'; ++token)
        ASSERT_GE(value_from_base_36_token(token), 36); // assert to avoid flood
}

TEST(ValueFromBase36TokenTest, TokensFrom0To9MapToValues0To9)
{
    EXPECT_EQ(0, value_from_base_36_token('0'));
    EXPECT_EQ(1, value_from_base_36_token('1'));
    EXPECT_EQ(2, value_from_base_36_token('2'));
    EXPECT_EQ(3, value_from_base_36_token('3'));
    EXPECT_EQ(4, value_from_base_36_token('4'));
    EXPECT_EQ(5, value_from_base_36_token('5'));
    EXPECT_EQ(6, value_from_base_36_token('6'));
    EXPECT_EQ(7, value_from_base_36_token('7'));
    EXPECT_EQ(8, value_from_base_36_token('8'));
    EXPECT_EQ(9, value_from_base_36_token('9'));
}

TEST(ValueFromBase36TokenTest, TokensBetween9AndAAreInvalid)
{
    for (char token = '9' + 1; token < 'A'; ++token)
        ASSERT_GE(value_from_base_36_token(token), 36); // assert to avoid flood
}

TEST(ValueFromBase36TokenTest, TokensFromCapitalAToZMapToValues10To35)
{
    EXPECT_EQ(10, value_from_base_36_token('A'));
    EXPECT_EQ(11, value_from_base_36_token('B'));
    EXPECT_EQ(12, value_from_base_36_token('C'));
    EXPECT_EQ(13, value_from_base_36_token('D'));
    EXPECT_EQ(14, value_from_base_36_token('E'));
    EXPECT_EQ(15, value_from_base_36_token('F'));
    EXPECT_EQ(16, value_from_base_36_token('G'));
    EXPECT_EQ(17, value_from_base_36_token('H'));
    EXPECT_EQ(18, value_from_base_36_token('I'));
    EXPECT_EQ(19, value_from_base_36_token('J'));
    EXPECT_EQ(20, value_from_base_36_token('K'));
    EXPECT_EQ(21, value_from_base_36_token('L'));
    EXPECT_EQ(22, value_from_base_36_token('M'));
    EXPECT_EQ(23, value_from_base_36_token('N'));
    EXPECT_EQ(24, value_from_base_36_token('O'));
    EXPECT_EQ(25, value_from_base_36_token('P'));
    EXPECT_EQ(26, value_from_base_36_token('Q'));
    EXPECT_EQ(27, value_from_base_36_token('R'));
    EXPECT_EQ(28, value_from_base_36_token('S'));
    EXPECT_EQ(29, value_from_base_36_token('T'));
    EXPECT_EQ(30, value_from_base_36_token('U'));
    EXPECT_EQ(31, value_from_base_36_token('V'));
    EXPECT_EQ(32, value_from_base_36_token('W'));
    EXPECT_EQ(33, value_from_base_36_token('X'));
    EXPECT_EQ(34, value_from_base_36_token('Y'));
    EXPECT_EQ(35, value_from_base_36_token('Z'));
}

TEST(ValueFromBase36TokenTest, TokensBetweenCapitalZAndLowercaseAAreInvalid)
{
    for (char token = 'Z' + 1; token < 'a'; ++token)
        ASSERT_GE(value_from_base_36_token(token), 36); // assert to avoid flood
}

TEST(ValueFromBase36TokenTest, TokensFromLowercaseAToZMapToValues10To35)
{
    EXPECT_EQ(10, value_from_base_36_token('a'));
    EXPECT_EQ(11, value_from_base_36_token('b'));
    EXPECT_EQ(12, value_from_base_36_token('c'));
    EXPECT_EQ(13, value_from_base_36_token('d'));
    EXPECT_EQ(14, value_from_base_36_token('e'));
    EXPECT_EQ(15, value_from_base_36_token('f'));
    EXPECT_EQ(16, value_from_base_36_token('g'));
    EXPECT_EQ(17, value_from_base_36_token('h'));
    EXPECT_EQ(18, value_from_base_36_token('i'));
    EXPECT_EQ(19, value_from_base_36_token('j'));
    EXPECT_EQ(20, value_from_base_36_token('k'));
    EXPECT_EQ(21, value_from_base_36_token('l'));
    EXPECT_EQ(22, value_from_base_36_token('m'));
    EXPECT_EQ(23, value_from_base_36_token('n'));
    EXPECT_EQ(24, value_from_base_36_token('o'));
    EXPECT_EQ(25, value_from_base_36_token('p'));
    EXPECT_EQ(26, value_from_base_36_token('q'));
    EXPECT_EQ(27, value_from_base_36_token('r'));
    EXPECT_EQ(28, value_from_base_36_token('s'));
    EXPECT_EQ(29, value_from_base_36_token('t'));
    EXPECT_EQ(30, value_from_base_36_token('u'));
    EXPECT_EQ(31, value_from_base_36_token('v'));
    EXPECT_EQ(32, value_from_base_36_token('w'));
    EXPECT_EQ(33, value_from_base_36_token('x'));
    EXPECT_EQ(34, value_from_base_36_token('y'));
    EXPECT_EQ(35, value_from_base_36_token('z'));
}

TEST(ValueFromBase36TokenTest, TokensGreaterThanLowercaseZAreInvalid)
{
    for (char token = 'z' + 1;; ++token) {
        ASSERT_GE(value_from_base_36_token(token), 36); // assert to avoid flood
        if (token == std::numeric_limits<char>::max())
            break; // avoid overflow at max value
    }
}

} // namespace
