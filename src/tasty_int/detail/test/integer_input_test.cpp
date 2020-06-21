#include "tasty_int/detail/integer_input.hpp"

#include "gtest/gtest.h"

#include <iomanip>
#include <sstream>

#include "tasty_int/detail/test/integer_test_common.hpp"


namespace {

using tasty_int::detail::Integer;


TEST(IntegerInputTest, InputReturnsReferenceToSelf)
{
    std::istringstream input("0");
    Integer integer;

    EXPECT_EQ(&input, &(input >> integer));
}

TEST(IntegerInputTest, InvalidInputSetsFailbit)
{
    std::istringstream input("InvalidInput!");
    Integer integer;

    input >> integer;

    EXPECT_TRUE(input.fail());
}

TEST(IntegerInputTest, NonnegativeNoPrefixNoFormat)
{
    std::istringstream input("9876543210");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(9876543210), integer);
}

TEST(IntegerInputTest, NonnegativeHexPrefixNoFormat)
{
    std::istringstream input("0xFED321");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(0xFED321), integer);
}

TEST(IntegerInputTest, NonnegativeOctPrefixNoFormat)
{
    std::istringstream input("076543210");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(076543210), integer);
}

TEST(IntegerInputTest, NonnegativeBinaryPrefixNoFormat)
{
    std::istringstream input("0b111111");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(0b111111), integer);
}

TEST(IntegerInputTest, NonnegativeHex)
{
    std::istringstream input("deadf00");
    Integer integer;

    input >> std::hex >> integer;

    EXPECT_EQ(std::intmax_t(0xdeadf00), integer);
}

TEST(IntegerInputTest, NonnegativeDec)
{
    std::istringstream input("123");
    Integer integer;

    input >> std::dec >> integer;

    EXPECT_EQ(std::intmax_t(123), integer);
}

TEST(IntegerInputTest, NonnegativeOct)
{
    std::istringstream input("777");
    Integer integer;

    input >> std::oct >> integer;

    EXPECT_EQ(std::intmax_t(0777), integer);
}

TEST(IntegerInputTest, NegativeNoPrefixNoFormat)
{
    std::istringstream input("-9876543210");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(-9876543210), integer);
}

TEST(IntegerInputTest, NegativeHexPrefixNoFormat)
{
    std::istringstream input("-0xFED321");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(-0xFED321), integer);
}

TEST(IntegerInputTest, NegativeOctPrefixNoFormat)
{
    std::istringstream input("-076543210");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(-076543210), integer);
}

TEST(IntegerInputTest, NegativeBinaryPrefixNoFormat)
{
    std::istringstream input("-0b111111");
    input.unsetf(std::ios_base::dec);
    Integer integer;

    input >> integer;

    EXPECT_EQ(std::intmax_t(-0b111111), integer);
}

TEST(IntegerInputTest, NegativeHex)
{
    std::istringstream input("-deadf00");
    Integer integer;

    input >> std::hex >> integer;

    EXPECT_EQ(std::intmax_t(-0xdeadf00), integer);
}

TEST(IntegerInputTest, NegativeDec)
{
    std::istringstream input("-123");
    Integer integer;

    input >> std::dec >> integer;

    EXPECT_EQ(std::intmax_t(-123), integer);
}

TEST(IntegerInputTest, NegativeOct)
{
    std::istringstream input("-777");
    Integer integer;

    input >> std::oct >> integer;

    EXPECT_EQ(std::intmax_t(-0777), integer);
}

} // namespace
