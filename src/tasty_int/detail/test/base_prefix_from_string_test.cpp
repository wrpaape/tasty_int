#include "tasty_int/detail/base_prefix_from_string.hpp"

#include "gtest/gtest.h"


namespace tasty_int {
namespace detail {

bool
operator==(const BasePrefix &lhs, const BasePrefix &rhs)
{
    return (lhs.prefix_length == rhs.prefix_length)
        && (lhs.base          == rhs.base);
}

std::ostream &
operator<<(std::ostream     &output,
           const BasePrefix &base_prefix)
{
    return output << "[base=" << base_prefix.base
                  << ", prefix_length=" << base_prefix.prefix_length << ']';
}

} // namespace detail
} // namespace tasty_int

namespace {

using tasty_int::detail::BasePrefix;
using tasty_int::detail::base_prefix_from_string;

TEST(BaseFromStringTest, InterpretsPrefix0bAsBinary)
{
    BasePrefix binary = {
        .prefix_length = 2,
        .base          = 2
    };

    EXPECT_EQ(binary, base_prefix_from_string("0b"));
}

TEST(BaseFromStringTest, InterpretsPrefix0BAsBinary)
{
    BasePrefix binary = {
        .prefix_length = 2,
        .base          = 2
    };

    EXPECT_EQ(binary, base_prefix_from_string("0B"));
}

TEST(BaseFromStringTest, InterpretsPrefix0AsOctal)
{
    BasePrefix octal = {
        .prefix_length = 1,
        .base          = 8
    };

    EXPECT_EQ(octal, base_prefix_from_string("0123"));
}

TEST(BaseFromStringTest, Interprets0AsDecimal)
{
    BasePrefix decimal = {
        .prefix_length = 0,
        .base          = 10
    };

    EXPECT_EQ(decimal, base_prefix_from_string("0"));
}

TEST(BaseFromStringTest, InterpretsPrefix0xAsHexidecimal)
{
    BasePrefix hexidecimal = {
        .prefix_length = 2,
        .base          = 16
    };

    EXPECT_EQ(hexidecimal, base_prefix_from_string("0x"));
}

TEST(BaseFromStringTest, InterpretsPrefix0XAsHexidecimal)
{
    BasePrefix hexidecimal = {
        .prefix_length = 2,
        .base          = 16
    };

    EXPECT_EQ(hexidecimal, base_prefix_from_string("0X"));
}

class DefaultBehaviorTest : public testing::TestWithParam<std::string_view>
{}; // class DefaultBehaviorTest

TEST_P(DefaultBehaviorTest, DefaultsToDecimal)
{
    BasePrefix decimal = {
        .prefix_length = 0,
        .base          = 10
    };

    EXPECT_EQ(decimal, base_prefix_from_string(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    BaseFromStringTest,
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
