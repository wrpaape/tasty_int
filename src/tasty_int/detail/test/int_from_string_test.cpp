#include "tasty_int/detail/int_from_string.hpp"

#include <cctype>

#include <limits>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/digits_from_string.hpp"
#include "tasty_int/detail/test/string_conversion_test_common.hpp"
#include "tasty_int/detail/test/int_test_common.hpp"


namespace {

using tasty_int::detail::Int;
using tasty_int::detail::Sign;
using tasty_int::detail::digit_type;
using tasty_int::detail::digits_from_string;
using tasty_int::detail::int_from_string;
using string_conversion_test_common::StringConversionTestParam;
using string_conversion_test_common::StringViewConversionTestParam;
using string_conversion_test_common::operator<<;


class EmptyTokensTest : public ::testing::TestWithParam<std::string>
{}; // class EmptyTokensTest

TEST_P(EmptyTokensTest, EmptyTokensThrowsInvalidArgument)
{
    std::string_view empty_tokens = GetParam();

    try {
        (void) int_from_string(empty_tokens, 0);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::string_view expected_message =
            "tasty_int::detail::int_from_string - empty tokens";

        EXPECT_EQ(expected_message, exception.what());
    }
}

struct EmptyTokenSet
{
    char whitespace;
    char sign;
    char lower_prefix;
}; // struct EmptyTokenSet

void
append_empty_combinations(EmptyTokenSet             empty_token_set,
                          std::vector<std::string> &empty_tokens)
{
    static const std::string ZERO("0");

    std::string whitespace(11, empty_token_set.whitespace);
    std::string sign(1, empty_token_set.sign);
    std::string lower_prefix = ZERO + empty_token_set.lower_prefix;
    std::string upper_prefix = ZERO
                             + char(std::toupper(empty_token_set.lower_prefix));

    empty_tokens.emplace_back(whitespace);
    empty_tokens.emplace_back(whitespace + sign);
    empty_tokens.emplace_back(whitespace + lower_prefix);
    empty_tokens.emplace_back(whitespace + upper_prefix);
    empty_tokens.emplace_back(whitespace + sign + lower_prefix);
    empty_tokens.emplace_back(whitespace + sign + upper_prefix);
    empty_tokens.emplace_back(sign);
    empty_tokens.emplace_back(sign + lower_prefix);
    empty_tokens.emplace_back(sign + upper_prefix);
    empty_tokens.emplace_back(lower_prefix);
    empty_tokens.emplace_back(upper_prefix);
}

std::vector<std::string>
make_empty_tokens()
{
    std::vector<std::string> empty_tokens;

    for (char whitespace_token : { ' ', '\t', '\r', '\n', '\f', '\v' })
        for (char sign_token : { '+', '-' })
            for (char lower_prefix_token : { 'x', 'b' })
                append_empty_combinations(
                    {
                        .whitespace   = whitespace_token,
                        .sign         = sign_token,
                        .lower_prefix = lower_prefix_token
                    },
                    empty_tokens
                );

    empty_tokens.emplace_back("");

    return empty_tokens;
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    EmptyTokensTest,
    ::testing::ValuesIn(make_empty_tokens())
);


class WhitespaceBetweenPrefixAndDigitsTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{}; // class WhitespaceBetweenPrefixAndDigitsTest

TEST_P(WhitespaceBetweenPrefixAndDigitsTest,
       WhitespaceBetweenPrefixAndDigitsThrowsInvalidArgument)
{
    auto [base, invalid_tokens] = GetParam();

    try {
        (void) int_from_string(invalid_tokens, base);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::string expected_message =
            "tasty_int::detail::digits_from_string - invalid token (' '): Token"
            " is not within the set of characters for specified base ("
           + std::to_string(base) + ").";

        EXPECT_EQ(expected_message, exception.what());
    }
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    WhitespaceBetweenPrefixAndDigitsTest,
    ::testing::ValuesIn(
        std::vector<StringViewConversionTestParam> {
            {  2, "0b 10101" },
            {  2, "0B 10101" },
            {  2, "+0b 10101" },
            {  2, "+0B 10101" },
            {  2, "-0b 10101" },
            {  2, "-0B 10101" },

            {  8, "0 76543210" },
            {  8, "+0 76543210" },
            {  8, "-0 76543210" },

            { 10, "+ 1234567890" },
            { 10, "- 1234567890" },

            { 16, "0x DeADbEeF" },
            { 16, "0X DeADbEeF" },
            { 16, "+0x DeADbEeF" },
            { 16, "+0X DeADbEeF" },
            { 16, "-0x DeADbEeF" },
            { 16, "-0X DeADbEeF" },
        }
    )
);


class IntFromExplicitBaseStringTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{
protected:
    IntFromExplicitBaseStringTest();

    const unsigned int     base;
    const std::string_view tokens_without_sign;
    const Int              expected_int;
}; // class IntFromExplicitBaseStringTest

IntFromExplicitBaseStringTest::IntFromExplicitBaseStringTest()
    : base(GetParam().base)
    , tokens_without_sign(GetParam().tokens)
    , expected_int({
          .sign   = Sign::POSITIVE,
          .digits = digits_from_string(tokens_without_sign, base)
      })
{}

TEST_P(IntFromExplicitBaseStringTest, TokensWithExplicitBaseYieldCorrectInt)
{
    Int result = int_from_string(tokens_without_sign, base);

    EXPECT_EQ(expected_int, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    IntFromExplicitBaseStringTest,
    ::testing::ValuesIn(
        std::vector<StringViewConversionTestParam> {
            {  2, "10101" },
            {  8, "076543210" },
            { 10, "1234567890" },
            { 16, "DeADbEeF" },
            { 36, "123abc" },
            { 62, "ABCabc123" },
            { 64, "+/ABCabc123" }
        }
    )
);


struct SignTestParam
{
    char sign_token;
    Sign expected_sign;
}; // struct SignTestParam

class IntFromExplicitSignAndBaseStringTest
    : public ::testing::TestWithParam<
          std::tuple<SignTestParam, StringViewConversionTestParam>
      >
{
protected:
    IntFromExplicitSignAndBaseStringTest();
    IntFromExplicitSignAndBaseStringTest(
        SignTestParam       sign_test_param,
        StringViewConversionTestParam from_string_test_param
    );

    const unsigned int base;
    std::string        tokens_with_sign;
    Int                expected_int;
}; // class IntFromExplicitSignAndBaseStringTest

IntFromExplicitSignAndBaseStringTest::IntFromExplicitSignAndBaseStringTest()
    : IntFromExplicitSignAndBaseStringTest(std::get<0>(GetParam()),
                                           std::get<1>(GetParam()))
{}

IntFromExplicitSignAndBaseStringTest::IntFromExplicitSignAndBaseStringTest(
    SignTestParam       sign_test_param,
    StringViewConversionTestParam from_string_test_param
)
    : base(from_string_test_param.base)
{
    char sign_token                      = sign_test_param.sign_token;
    std::string_view tokens_without_sign = from_string_test_param.tokens;

    tokens_with_sign += sign_token;
    tokens_with_sign += tokens_without_sign;

    expected_int.sign   = sign_test_param.expected_sign;
    expected_int.digits = digits_from_string(tokens_without_sign, base);
}

TEST_P(IntFromExplicitSignAndBaseStringTest,
       TokensWithExplicitSignAndBaseYieldCorrectInt)
{
    Int result = int_from_string(tokens_with_sign, base);

    EXPECT_EQ(expected_int, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    IntFromExplicitSignAndBaseStringTest,
    ::testing::Combine(
        ::testing::Values(
            SignTestParam{ '+', Sign::POSITIVE },
            SignTestParam{ '-', Sign::NEGATIVE }
        ),
        ::testing::ValuesIn(
            std::vector<StringViewConversionTestParam> {
                {  2, "10101" },
                {  8, "076543210" },
                { 10, "1234567890" },
                { 16, "DeAdBEeF" },
                { 36, "123abc" },
                { 62, "ABCabc123" }
                // exclude bases >= 63 for which '+' is a reserved value
            }
        )
    )
);


struct ExplicitBaseWithPrefixTestParam
{
    StringViewConversionTestParam input;
    std::string_view              tokens_without_prefix;
}; // struct SignTestParam

std::ostream &
operator<<(std::ostream                          &output,
           const ExplicitBaseWithPrefixTestParam &test_param)
{
    return output << "{ input=\"" << test_param.input
                  << "\", tokens_without_prefix="
                  << test_param.tokens_without_prefix << " }";
}

class ExplicitBaseWithPrefixTest
    : public ::testing::TestWithParam<ExplicitBaseWithPrefixTestParam>
{
protected:
    ExplicitBaseWithPrefixTest();

    const std::string_view input_tokens;
    const unsigned int     base;
    const Int              expected_int;
}; // class ExplicitBaseWithPrefixTest

ExplicitBaseWithPrefixTest::ExplicitBaseWithPrefixTest()
    : input_tokens(GetParam().input.tokens)
    , base(GetParam().input.base)
    , expected_int({
        .sign   = Sign::POSITIVE,
        .digits = digits_from_string(GetParam().tokens_without_prefix,
                                     GetParam().input.base)
      })
{}

TEST_P(ExplicitBaseWithPrefixTest, BasePrefixIsOnlyProcessedForMatchingBases)
{
    Int result = int_from_string(input_tokens, base);

    EXPECT_EQ(expected_int, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    ExplicitBaseWithPrefixTest,
    ::testing::ValuesIn(
        std::vector<ExplicitBaseWithPrefixTestParam> {
            { { 36, "0b10101" },    "0b10101" },
            { {  2, "0b10101" },      "10101" },

            { { 36, "0B10101" },    "0B10101" },
            { {  2, "0B10101" },      "10101" },

            { { 10, "076543210" },  "076543210" },
            { {  8, "076543210" },   "76543210" },

            { { 10, "0076543210" }, "0076543210" },
            { {  8, "0076543210" },  "076543210" },

            { { 64, "0xDeADbEeF" }, "0xDeADbEeF" },
            { { 16, "0xDeADbEeF" },   "DeADbEeF" },

            { { 64, "0XDeADbEeF" }, "0XDeADbEeF" },
            { { 16, "0XDeADbEeF" },   "DeADbEeF" }
        }
    )
);


struct InterprettedBaseTestParam
{
    std::string_view    input_tokens;
    StringViewConversionTestParam expected_interpretation;
}; // struct SignTestParam

std::ostream &
operator<<(std::ostream                    &output,
           const InterprettedBaseTestParam &test_param)
{
    return output << "{ input_tokens=\"" << test_param.input_tokens
                  << "\", expected_interpretation="
                  << test_param.expected_interpretation << " }";
}

class InterprettedBaseTest
    : public ::testing::TestWithParam<InterprettedBaseTestParam>
{
protected:
    InterprettedBaseTest();

    const std::string_view input_tokens;
    const Int              expected_int;
}; // class InterprettedBaseTest

InterprettedBaseTest::InterprettedBaseTest()
    : input_tokens(GetParam().input_tokens)
    , expected_int({
        .sign   = Sign::POSITIVE,
        .digits = digits_from_string(GetParam().expected_interpretation.tokens,
                                     GetParam().expected_interpretation.base)
      })
{}

TEST_P(InterprettedBaseTest, TokensWithInterprettedBaseYieldCorrectInt)
{
    Int result = int_from_string(input_tokens, 0);

    EXPECT_EQ(expected_int, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    InterprettedBaseTest,
    ::testing::ValuesIn(
        std::vector<InterprettedBaseTestParam> {
            { "0b10101",    {  2, "10101" } },
            { "0B10101",    {  2, "10101" } },

            { "076543210",  {  8, "76543210" } },
            { "0076543210", {  8, "076543210" } },

            { "0xDeADbEeF", { 16, "DeADbEeF" } },
            { "0XDeADbEeF", { 16, "DeADbEeF" } },

            { "10101",      { 10, "10101" } },
            { "1234567890", { 10, "1234567890" } }
        }
    )
);

TEST(IntFromStringTest, SingleZeroWithInterprettedBaseYieldsZeroInt)
{
    const Int ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    Int result = int_from_string("0", 0);

    EXPECT_EQ(ZERO, result);
}


std::vector<StringConversionTestParam>
make_zero_test_params()
{
    const std::vector<std::string> BASE_62_AND_UNDER_VALID_SIGNS = {
        "", "+", "-"
    };
    const std::vector<std::string> BASE_63_AND_OVER_VALID_SIGNS = {
        ""
    };
    const char BASE_36_AND_UNDER_ZERO_TOKEN = '0';
    const char BASE_37_AND_OVER_ZERO_TOKEN  = 'A';

    std::vector<StringConversionTestParam> zero_test_params;

    // start at base 0, skip base 1, then process bases 2 through 64
    for (unsigned int base = 0, step = 2; base <= 64; base += step, step = 1) {
           const auto& valid_signs = (base <= 62)
                                   ? BASE_62_AND_UNDER_VALID_SIGNS
                                   : BASE_63_AND_OVER_VALID_SIGNS;
           char zero_token         = (base <= 36)
                                   ? BASE_36_AND_UNDER_ZERO_TOKEN
                                   : BASE_37_AND_OVER_ZERO_TOKEN;

           for (const auto& valid_sign : valid_signs) {
               for (unsigned int num_zero_tokens : { 1, 4 }) {
                   zero_test_params.emplace_back(StringConversionTestParam{
                       .base   = base,
                       .tokens = valid_sign
                               + std::string(num_zero_tokens, zero_token)
                   });
               }
           }
    };

    return zero_test_params;
}

class ZeroTest : public ::testing::TestWithParam<StringConversionTestParam>
{}; // ZeroTest

TEST_P(ZeroTest, RepresentationsOfZeroAreInterprettedAsZero)
{
    const Int ZERO = { .sign = Sign::ZERO, .digits = { 0 } };
    auto [base, zero_tokens] = GetParam();

    Int result = int_from_string(zero_tokens, base);

    EXPECT_EQ(ZERO, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    ZeroTest,
    ::testing::ValuesIn(make_zero_test_params())
);


class EquivalentRepresentationTest
    : public ::testing::TestWithParam<std::string_view>
{
protected:
    static const std::string_view MINIMAL_BASE_16_REPRESENTATION;
}; // class EquivalentRepresentationTest

TEST_P(EquivalentRepresentationTest, EquivalentRepresentationsYieldEqualInts)
{
    std::string_view alternate_representation = GetParam();

    Int expected = int_from_string(MINIMAL_BASE_16_REPRESENTATION, 16);
    Int result   = int_from_string(alternate_representation,       16);

    EXPECT_EQ(expected, result);
}

const std::string_view
EquivalentRepresentationTest::MINIMAL_BASE_16_REPRESENTATION =
    "-1234567890abcdef";

INSTANTIATE_TEST_SUITE_P(
    IntFromStringTest,
    EquivalentRepresentationTest,
    ::testing::ValuesIn(
        std::vector<std::string_view> {
            " \t \r \n \f \v -1234567890abcdef",
            " \t \r \n \f \v -1234567890ABCDEF",
            " \t \r \n \f \v -00001234567890abcdef",
            " \t \r \n \f \v -00001234567890ABCDEF",
            " \t \r \n \f \v -0x00001234567890abcdef",
            " \t \r \n \f \v -0X00001234567890abcdef",
            " \t \r \n \f \v -0x00001234567890ABCDEF",
            " \t \r \n \f \v -0X00001234567890ABCDEF",
            "-0x1234567890abcdef",
            "-0X1234567890abcdef",
            "-0x0000001234567890abcdef",
            "-0X0000001234567890abcdef",
            "-0x1234567890ABCDEF",
            "-0X1234567890ABCDEF",
            "-0x0000001234567890ABCDEF",
            "-0X0000001234567890ABCDEF",
            "-00001234567890abcdef",
            "-00001234567890ABCDEF",
            "-1234567890ABCDEF"
        }
    )
);

} // namespace
