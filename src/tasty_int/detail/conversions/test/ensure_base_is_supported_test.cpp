#include "tasty_int/detail/conversions/ensure_base_is_supported.hpp"

#include <stdexcept>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/test/base_support_test_common.hpp"


namespace {

using tasty_int::detail::conversions::ensure_base_is_supported;
using base_support_test_common::unsupported_bases;
using base_support_test_common::supported_bases;


class UnsupportedBaseTest : public ::testing::TestWithParam<unsigned int>
{}; // class UnsupportedBaseTest

TEST_P(UnsupportedBaseTest, UnsupportedBaseThrowsInvalidArgument)
{
    unsigned int unsupported_base = GetParam();
    try {
        ensure_base_is_supported(unsupported_base);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int::detail::conversions::ensure_base_is_supported - invalid base ("
         << unsupported_base << "): Base is not within the range of supported "
            "values [2,64].";

        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

INSTANTIATE_TEST_SUITE_P(
    EnsureBaseIsSupportedTest,
    UnsupportedBaseTest,
    unsupported_bases()
);


class SupportedBaseTest : public ::testing::TestWithParam<unsigned int>
{}; // class SupportedBaseTest

TEST_P(SupportedBaseTest, SupportedBaseDoesNotThrowInvalidArgument)
{
    unsigned int supported_base = GetParam();

    EXPECT_NO_THROW({
        ensure_base_is_supported(supported_base);
    });
}

INSTANTIATE_TEST_SUITE_P(
    EnsureBaseIsSupportedTest,
    SupportedBaseTest,
    supported_bases()
);

} // namespace
