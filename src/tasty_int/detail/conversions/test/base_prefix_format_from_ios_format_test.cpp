#include "tasty_int/detail/conversions/base_prefix_format_from_ios_format.hpp"

#include "gtest/gtest.h"


namespace tasty_int {
namespace detail {
namespace conversions {

bool
operator==(const BasePrefixFormat &lhs, const BasePrefixFormat &rhs)
{
    return (lhs.base             == rhs.base)
        && (lhs.nonnegative_sign == rhs.nonnegative_sign)
        && (lhs.prefix           == rhs.prefix);
}

void
PrintTo(const BasePrefixFormat &base_prefix_format,
        std::ostream           *output)
{
    *output << "{ base="               << base_prefix_format.base
            << ", nonnegative_sign=\"" << base_prefix_format.nonnegative_sign
            << "\", prefix=\""         << base_prefix_format.prefix
            << "\" }";
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int


namespace {

using tasty_int::detail::conversions::BasePrefixFormat;
using tasty_int::detail::conversions::base_prefix_format_from_ios_format;

TEST(BasePrefixFormatFromIosFormatTest, ShowposAndShowbaseAndHex)
{
    BasePrefixFormat expected = {
        .base = 16, .nonnegative_sign = "+", .prefix = "0x"
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos  |
            std::ios_base::showbase |
            std::ios_base::hex
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, ShowposAndNoShowbaseAndHex)
{
    BasePrefixFormat expected = {
        .base = 16, .nonnegative_sign = "+", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos | std::ios_base::hex
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, ShowposAndShowbaseAndOct)
{
    BasePrefixFormat expected = {
        .base = 8, .nonnegative_sign = "+", .prefix = "0"
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos  |
            std::ios_base::showbase |
            std::ios_base::oct
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, ShowposAndNoShowbaseAndOct)
{
    BasePrefixFormat expected = {
        .base = 8, .nonnegative_sign = "+", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos | std::ios_base::oct
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, ShowPosAndShowbaseAndNoBase)
{
    BasePrefixFormat expected = {
        .base = 10, .nonnegative_sign = "+", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos | std::ios_base::showbase
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, ShowposAndNoShowBaseAndNoBase)
{
    BasePrefixFormat expected = {
        .base = 10, .nonnegative_sign = "+", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showpos
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowposAndShowbaseAndHex)
{
    BasePrefixFormat expected = {
        .base = 16, .nonnegative_sign = "", .prefix = "0x"
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showbase | std::ios_base::hex
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowposAndNoShowbaseAndHex)
{
    BasePrefixFormat expected = {
        .base = 16, .nonnegative_sign = "", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::hex
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowposAndShowbaseAndOct)
{
    BasePrefixFormat expected = {
        .base = 8, .nonnegative_sign = "", .prefix = "0"
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showbase | std::ios_base::oct
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowposAndNoShowbaseAndOct)
{
    BasePrefixFormat expected = {
        .base = 8, .nonnegative_sign = "", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::oct
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowPosAndShowbaseAndNoBase)
{
    BasePrefixFormat expected = {
        .base = 10, .nonnegative_sign = "", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::showbase
        )
    );
}

TEST(BasePrefixFormatFromIosFormatTest, NoShowposAndNoShowBaseAndNoBase)
{
    BasePrefixFormat expected = {
        .base = 10, .nonnegative_sign = "", .prefix = ""
    };

    EXPECT_EQ(
        expected,
        base_prefix_format_from_ios_format(
            std::ios_base::fmtflags()
        )
    );
}

} // namespace
