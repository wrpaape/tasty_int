#include "tasty_int/detail/conversions/base_prefix_length_from_string.hpp"

#include "gtest/gtest.h"


namespace tasty_int {
namespace detail {
namespace conversions {

bool
operator==(const BasePrefixLength &lhs, const BasePrefixLength &rhs)
{
    return (lhs.prefix_length == rhs.prefix_length)
        && (lhs.base          == rhs.base);
}

void
PrintTo(const BasePrefixLength &base_prefix_length,
        std::ostream           *output)
{
    *output << "{ base=" << base_prefix_length.base
            << ", prefix_length=" << base_prefix_length.prefix_length
            << " }";
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int


namespace {

using tasty_int::detail::conversions::BasePrefixLength;
using tasty_int::detail::conversions::base_prefix_length_from_string;


TEST(BasePrefixLengthFromStringTest, InterpretsPrefix0bAsBinary)
{
    BasePrefixLength binary = {
        .prefix_length = 2,
        .base          = 2
    };

    EXPECT_EQ(binary, base_prefix_length_from_string("0b"));
}

TEST(BasePrefixLengthFromStringTest, InterpretsPrefix0BAsBinary)
{
    BasePrefixLength binary = {
        .prefix_length = 2,
        .base          = 2
    };

    EXPECT_EQ(binary, base_prefix_length_from_string("0B"));
}

TEST(BasePrefixLengthFromStringTest, InterpretsPrefix0AsOctal)
{
    BasePrefixLength octal = {
        .prefix_length = 1,
        .base          = 8
    };

    EXPECT_EQ(octal, base_prefix_length_from_string("0123"));
}

TEST(BasePrefixLengthFromStringTest, Interprets0AsDecimal)
{
    BasePrefixLength decimal = {
        .prefix_length = 0,
        .base          = 10
    };

    EXPECT_EQ(decimal, base_prefix_length_from_string("0"));
}

TEST(BasePrefixLengthFromStringTest, InterpretsPrefix0xAsHexidecimal)
{
    BasePrefixLength hexidecimal = {
        .prefix_length = 2,
        .base          = 16
    };

    EXPECT_EQ(hexidecimal, base_prefix_length_from_string("0x"));
}

TEST(BasePrefixLengthFromStringTest, InterpretsPrefix0XAsHexidecimal)
{
    BasePrefixLength hexidecimal = {
        .prefix_length = 2,
        .base          = 16
    };

    EXPECT_EQ(hexidecimal, base_prefix_length_from_string("0X"));
}

class DefaultBehaviorTest : public testing::TestWithParam<std::string_view>
{}; // class DefaultBehaviorTest

TEST_P(DefaultBehaviorTest, DefaultsToDecimal)
{
    BasePrefixLength decimal = {
        .prefix_length = 0,
        .base          = 10
    };

    EXPECT_EQ(decimal, base_prefix_length_from_string(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    BasePrefixLengthFromStringTest,
    DefaultBehaviorTest,
    ::testing::Values(
        "10",
        "-10101",
        "+076543210",
        "FOOBAR",
        "こにちわ",
        ""
    )
);

} // namespace
