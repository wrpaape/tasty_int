#include "tasty_int/tasty_int.hpp"

#include <cmath>

#include <iomanip>
#include <sstream>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int::TastyInt;


TEST(TastyIntDefaultConstructorTest, DefaultValueIsZero)
{
    EXPECT_EQ(0, TastyInt().to_number<int>());
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntArithmeticTypeConversionTest : public ::testing::Test
{
protected:
    void test_value(ArithmeticType value)
    {
        TastyInt tasty_int(value);

        ArithmeticType converted_value = tasty_int.to_number<ArithmeticType>();

        if constexpr (std::is_integral_v<ArithmeticType>)
            EXPECT_EQ(value, converted_value);
        else
            EXPECT_EQ(std::trunc(value), converted_value);
    }
}; // class TastyIntArithmeticTypeConversionTest


TYPED_TEST_SUITE(TastyIntArithmeticTypeConversionTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsMinimumValue)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::MINIMUM
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsLowerQuartileValue)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::LOWER_QUARTILE
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsMedianValue)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::MEDIAN
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsUpperQuartileValue)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::UPPER_QUARTILE
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsMaximumValue)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::MAXIMUM
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsZero)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::ZERO
    );
}

TYPED_TEST(TastyIntArithmeticTypeConversionTest, ConvertsOne)
{
    TestFixture::test_value(
        tasty_int_test::SampleArithmetic<TypeParam>::ONE
    );
}


class TastyIntStringConversionTest : public ::testing::Test
{
protected:
    static void
    test_constructor_explicit_base_all_signs(
        unsigned int       expected_base,
        const std::string &unsigned_tokens
    );
    static void
    test_constructor_explicit_base(
        unsigned int     expected_base,
        std::string_view expected_tokens,
        std::string_view tokens
    );

    static void
    test_constructor_default_base_all_signs(
        unsigned int       expected_base,
        const std::string &expected_unsigned_tokens,
        const std::string &unsigned_tokens
    );
    static void
    test_constructor_default_base(
        unsigned int     expected_base,
        std::string_view expected_tokens,
        std::string_view tokens
    );
}; // class TastyIntArithmeticTypeConversionTest

void
TastyIntStringConversionTest::test_constructor_explicit_base_all_signs(
    unsigned int       explicit_base,
    const std::string &unsigned_tokens
)
{
    test_constructor_explicit_base(
       explicit_base, "-" + unsigned_tokens,
                      "-" + unsigned_tokens
    );

    test_constructor_explicit_base(
       explicit_base, unsigned_tokens,
                      "+" + unsigned_tokens
    );

    test_constructor_explicit_base(
       explicit_base, unsigned_tokens,
                      unsigned_tokens
    );
}

void
TastyIntStringConversionTest::test_constructor_explicit_base(
    unsigned int     explicit_base,
    std::string_view expected_tokens,
    std::string_view tokens
)
{
    TastyInt tasty_int(tokens, explicit_base);

    std::string converted_tokens = tasty_int.to_string(explicit_base);

    EXPECT_EQ(expected_tokens, converted_tokens);
}

void
TastyIntStringConversionTest::test_constructor_default_base_all_signs(
    unsigned int       expected_base,
    const std::string &expected_unsigned_tokens,
    const std::string &unsigned_tokens
)
{
    test_constructor_default_base(
       expected_base, "-" + expected_unsigned_tokens,
                      "-" + unsigned_tokens
    );

    test_constructor_default_base(
       expected_base, expected_unsigned_tokens,
                      "+" + unsigned_tokens
    );

    test_constructor_default_base(
       expected_base, expected_unsigned_tokens,
                      unsigned_tokens
    );
}

void
TastyIntStringConversionTest::test_constructor_default_base(
    unsigned int     expected_base,
    std::string_view expected_tokens,
    std::string_view tokens
)
{
    TastyInt tasty_int(tokens);

    std::string converted_tokens = tasty_int.to_string(expected_base);

    EXPECT_EQ(expected_tokens, converted_tokens);
}

TEST_F(TastyIntStringConversionTest, 
       StringViewConstructorExplicitBase3)
{
    test_constructor_explicit_base_all_signs(3, "210210210");
}

TEST_F(TastyIntStringConversionTest, 
       StringViewConstructorExplicitBase36)
{
    test_constructor_explicit_base_all_signs(
        36,
        "1234567890abcdefghijklmnopqrstuvwzyz"
    );
}

TEST_F(TastyIntStringConversionTest, 
       StringViewConstructorExplicitBase64)
{
    // base 64 does not support signed tokens since '+' is part of its token set
    test_constructor_explicit_base(
        64,
        "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/",
        "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/"
    );
}

TEST_F(TastyIntStringConversionTest,
       StringViewConstructorDefaultBaseInterpretsBinaryBase)
{
    test_constructor_default_base_all_signs(2, "1010101010101010110",
                                               "0b1010101010101010110");

    test_constructor_default_base_all_signs(2, "1010101010101010110",
                                               "0B1010101010101010110");
}

TEST_F(TastyIntStringConversionTest,
       StringViewConstructorDefaultBaseInterpretsOctalBase)
{
    test_constructor_default_base_all_signs(8, "7060504030201",
                                              "07060504030201");
}

TEST_F(TastyIntStringConversionTest,
       StringViewConstructorDefaultBaseInterpretsDecimalBase)
{
    test_constructor_default_base_all_signs(10, "1234567890",
                                                "1234567890");
}

TEST_F(TastyIntStringConversionTest,
       StringViewConstructorDefaultBaseInterpretsHexidecimalBase)
{
    test_constructor_default_base_all_signs(16, "deadbeef",
                                                "0xdeadbeef");

    test_constructor_default_base_all_signs(16, "deadbeef",
                                                "0xDEADBEEF");
}

TEST_F(TastyIntStringConversionTest, ToStringBaseDefaultsToBase10)
{
    TastyInt tasty_int("0x3a0c92075c0dbf3b8acbc5f96ce3f0ad2", 16);

    EXPECT_EQ("1234567890123456789012345678901234567890",
              tasty_int.to_string());
}


TEST(TastyIntInputTest, InputReturnsReferenceToSelf)
{
    std::istringstream input("0");
    TastyInt tasty_int;

    EXPECT_EQ(&input, &(input >> tasty_int));
}

TEST(TastyIntInputTest, InvalidInputSetsFailbit)
{
    std::istringstream input("InvalidInput!");
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_TRUE(input.fail());
}

TEST(TastyIntInputTest, NonnegativeNoPrefixNoFormat)
{
    std::istringstream input("9876543210");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(9876543210, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeHexPrefixNoFormat)
{
    std::istringstream input("0xFED321");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(0xFED321, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeOctPrefixNoFormat)
{
    std::istringstream input("076543210");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(076543210, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeBinaryPrefixNoFormat)
{
    std::istringstream input("0b111111");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(0b111111, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeHex)
{
    std::istringstream input("deadf00");
    TastyInt tasty_int;

    input >> std::hex >> tasty_int;

    EXPECT_EQ(0xdeadf00, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeDec)
{
    std::istringstream input("123");
    TastyInt tasty_int;

    input >> std::dec >> tasty_int;

    EXPECT_EQ(123, tasty_int);
}

TEST(TastyIntInputTest, NonnegativeOct)
{
    std::istringstream input("777");
    TastyInt tasty_int;

    input >> std::oct >> tasty_int;

    EXPECT_EQ(0777, tasty_int);
}

TEST(TastyIntInputTest, NegativeNoPrefixNoFormat)
{
    std::istringstream input("-9876543210");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(-9876543210, tasty_int);
}

TEST(TastyIntInputTest, NegativeHexPrefixNoFormat)
{
    std::istringstream input("-0xFED321");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(-0xFED321, tasty_int);
}

TEST(TastyIntInputTest, NegativeOctPrefixNoFormat)
{
    std::istringstream input("-076543210");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(-076543210, tasty_int);
}

TEST(TastyIntInputTest, NegativeBinaryPrefixNoFormat)
{
    std::istringstream input("-0b111111");
    input.unsetf(std::ios_base::dec);
    TastyInt tasty_int;

    input >> tasty_int;

    EXPECT_EQ(-0b111111, tasty_int);
}

TEST(TastyIntInputTest, NegativeHex)
{
    std::istringstream input("-deadf00");
    TastyInt tasty_int;

    input >> std::hex >> tasty_int;

    EXPECT_EQ(-0xdeadf00, tasty_int);
}

TEST(TastyIntInputTest, NegativeDec)
{
    std::istringstream input("-123");
    TastyInt tasty_int;

    input >> std::dec >> tasty_int;

    EXPECT_EQ(-123, tasty_int);
}

TEST(TastyIntInputTest, NegativeOct)
{
    std::istringstream input("-777");
    TastyInt tasty_int;

    input >> std::oct >> tasty_int;

    EXPECT_EQ(-0777, tasty_int);
}


TEST(TastyIntOutputTest, OutputReturnsReferenceToSelf)
{
    std::ostringstream output;

    EXPECT_EQ(&output, &(output << TastyInt(0)));
}

TEST(TastyIntOutputTest, NonnegativeNoFormat)
{
    std::ostringstream output;

    output << TastyInt(1234567890);

    EXPECT_EQ("1234567890", output.str());
}

TEST(TastyIntOutputTest, NonnegativeShowbase)
{
    std::ostringstream output;

    output << std::showbase
           << TastyInt(1234567890);

    EXPECT_EQ("1234567890", output.str());
}

TEST(TastyIntOutputTest, NonnegativeShowpos)
{
    std::ostringstream output;

    output << std::showpos
           << TastyInt(1234567890);

    EXPECT_EQ("+1234567890", output.str());
}

TEST(TastyIntOutputTest, NonnegativeShowbaseShowpos)
{
    std::ostringstream output;

    output << std::showbase
           << std::showpos
           << TastyInt(1234567890);

    EXPECT_EQ("+1234567890", output.str());
}

TEST(TastyIntOutputTest, NonnegativeHex)
{
    std::ostringstream output;

    output << std::hex
           << TastyInt(0xdeadf00);

    EXPECT_EQ("deadf00", output.str());
}

TEST(TastyIntOutputTest, NonnegativeHexShowbase)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << TastyInt(0xdeadf00);

    EXPECT_EQ("0xdeadf00", output.str());
}

TEST(TastyIntOutputTest, NonnegativeHexShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showpos
           << TastyInt(0xdeadf00);

    EXPECT_EQ("+deadf00", output.str());
}

TEST(TastyIntOutputTest, NonnegativeHexShowbaseShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << std::showpos
           << TastyInt(0xdeadf00);

    EXPECT_EQ("+0xdeadf00", output.str());
}

TEST(TastyIntOutputTest, NonnegativeOct)
{
    std::ostringstream output;

    output << std::oct
           << TastyInt(0777);
   
    EXPECT_EQ("777", output.str());
}

TEST(TastyIntOutputTest, NonnegativeOctShowbase)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << TastyInt(0777);

    EXPECT_EQ("0777", output.str());
}

TEST(TastyIntOutputTest, NonnegativeOctShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showpos
           << TastyInt(0777);

    EXPECT_EQ("+777", output.str());
}

TEST(TastyIntOutputTest, NonnegativeOctShowbaseShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << std::showpos
           << TastyInt(0777);

    EXPECT_EQ("+0777", output.str());
}

TEST(TastyIntOutputTest, NegativeNoFormat)
{
    std::ostringstream output;

    output << TastyInt(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(TastyIntOutputTest, NegativeShowbase)
{
    std::ostringstream output;

    output << std::showbase
           << TastyInt(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(TastyIntOutputTest, NegativeShowpos)
{
    std::ostringstream output;

    output << std::showpos
           << TastyInt(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(TastyIntOutputTest, NegativeShowbaseShowpos)
{
    std::ostringstream output;

    output << std::showbase
           << std::showpos
           << TastyInt(-1234567890);

    EXPECT_EQ("-1234567890", output.str());
}

TEST(TastyIntOutputTest, NegativeHex)
{
    std::ostringstream output;

    output << std::hex
           << TastyInt(-0xdeadf00);

    EXPECT_EQ("-deadf00", output.str());
}

TEST(TastyIntOutputTest, NegativeHexShowbase)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << TastyInt(-0xdeadf00);

    EXPECT_EQ("-0xdeadf00", output.str());
}

TEST(TastyIntOutputTest, NegativeHexShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showpos
           << TastyInt(-0xdeadf00);

    EXPECT_EQ("-deadf00", output.str());
}

TEST(TastyIntOutputTest, NegativeHexShowbaseShowpos)
{
    std::ostringstream output;

    output << std::hex
           << std::showbase
           << std::showpos
           << TastyInt(-0xdeadf00);

    EXPECT_EQ("-0xdeadf00", output.str());
}

TEST(TastyIntOutputTest, NegativeOct)
{
    std::ostringstream output;

    output << std::oct
           << TastyInt(-0777);
   
    EXPECT_EQ("-777", output.str());
}

TEST(TastyIntOutputTest, NegativeOctShowbase)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << TastyInt(-0777);

    EXPECT_EQ("-0777", output.str());
}

TEST(TastyIntOutputTest, NegativeOctShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showpos
           << TastyInt(-0777);

    EXPECT_EQ("-777", output.str());
}

TEST(TastyIntOutputTest, NegativeOctShowbaseShowpos)
{
    std::ostringstream output;

    output << std::oct
           << std::showbase
           << std::showpos
           << TastyInt(-0777);

    EXPECT_EQ("-0777", output.str());
}

} // namespace
