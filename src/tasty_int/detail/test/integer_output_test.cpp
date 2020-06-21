#include "tasty_int/detail/integer_output.hpp"

#include "gtest/gtest.h"

#include <iomanip>
#include <sstream>

#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"


namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::conversions::integer_from_signed_integral;


TEST(IntegerOutputTest, OutputReturnsReferenceToSelf)
{
    std::ostringstream output;

    EXPECT_EQ(&output, &(output << integer_from_signed_integral(0)));
}

TEST(IntegerOutputTest, NonnegativeNoFormat)
{
    std::ostringstream output;

    output << integer_from_signed_integral(1234567890);

    EXPECT_EQ("1234567890", output.str());
}

TEST(IntegerOutputTest, NonnegativeShowbase)
{
    std::ostringstream output;

    output << std::showbase
           << integer_from_signed_integral(1234567890);

    EXPECT_EQ("1234567890", output.str());
}

TEST(IntegerOutputTest, NonnegativeShowpos)
{
    std::ostringstream output;

    output << std::showpos
           << integer_from_signed_integral(1234567890);

    EXPECT_EQ("+1234567890", output.str());
}

TEST(IntegerOutputTest, NonnegativeShowbaseShowpos)
{
    std::ostringstream output;

    output << std::showbase
           << std::showpos
           << integer_from_signed_integral(1234567890);

    EXPECT_EQ("+1234567890", output.str());
}

TEST(IntegerOutputTest, NonnegativeHex)
{
    std::ostringstream output;

    output << std::hex
           << integer_from_signed_integral(0xdeadf00);

    EXPECT_EQ("deadf00", output.str());
}

TEST(IntegerOutputTest, NonnegativeHexShowbase)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << integer_from_signed_integral(0xdeadf00);

    EXPECT_EQ("0xdeadf00", output.str());
}

TEST(IntegerOutputTest, NonnegativeHexShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showpos
           << integer_from_signed_integral(0xdeadf00);

    EXPECT_EQ("+deadf00", output.str());
}

TEST(IntegerOutputTest, NonnegativeHexShowbaseShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << std::showpos
           << integer_from_signed_integral(0xdeadf00);

    EXPECT_EQ("+0xdeadf00", output.str());
}

TEST(IntegerOutputTest, NonnegativeOct)
{
    std::ostringstream output;

    output << std::oct
           << integer_from_signed_integral(0777);
   
    EXPECT_EQ("777", output.str());
}

TEST(IntegerOutputTest, NonnegativeOctShowbase)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << integer_from_signed_integral(0777);

    EXPECT_EQ("0777", output.str());
}

TEST(IntegerOutputTest, NonnegativeOctShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showpos
           << integer_from_signed_integral(0777);

    EXPECT_EQ("+777", output.str());
}

TEST(IntegerOutputTest, NonnegativeOctShowbaseShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << std::showpos
           << integer_from_signed_integral(0777);

    EXPECT_EQ("+0777", output.str());
}

TEST(IntegerOutputTest, NegativeNoFormat)
{
    std::ostringstream output;

    output << integer_from_signed_integral(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(IntegerOutputTest, NegativeShowbase)
{
    std::ostringstream output;

    output << std::showbase
           << integer_from_signed_integral(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(IntegerOutputTest, NegativeShowpos)
{
    std::ostringstream output;

    output << std::showpos
           << integer_from_signed_integral(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(IntegerOutputTest, NegativeShowbaseShowpos)
{
    std::ostringstream output;

    output << std::showbase
           << std::showpos
           << integer_from_signed_integral(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(IntegerOutputTest, NegativeHex)
{
    std::ostringstream output;

    output << std::hex
           << integer_from_signed_integral(-0xdeadf00);

    EXPECT_EQ("-deadf00", output.str());
}

TEST(IntegerOutputTest, NegativeHexShowbase)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << integer_from_signed_integral(-0xdeadf00);

    EXPECT_EQ("-0xdeadf00", output.str());
}

TEST(IntegerOutputTest, NegativeHexShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showpos
           << integer_from_signed_integral(-0xdeadf00);

    EXPECT_EQ("-deadf00", output.str());
}

TEST(IntegerOutputTest, NegativeHexShowbaseShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << std::showpos
           << integer_from_signed_integral(-0xdeadf00);

    EXPECT_EQ("-0xdeadf00", output.str());
}

TEST(IntegerOutputTest, NegativeOct)
{
    std::ostringstream output;

    output << std::oct
           << integer_from_signed_integral(-0777);
   
    EXPECT_EQ("-777", output.str());
}

TEST(IntegerOutputTest, NegativeOctShowbase)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << integer_from_signed_integral(-0777);

    EXPECT_EQ("-0777", output.str());
}

TEST(IntegerOutputTest, NegativeOctShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showpos
           << integer_from_signed_integral(-0777);

    EXPECT_EQ("-777", output.str());
}

TEST(IntegerOutputTest, NegativeOctShowbaseShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << std::showpos
           << integer_from_signed_integral(-0777);

    EXPECT_EQ("-0777", output.str());
}

} // namespace
