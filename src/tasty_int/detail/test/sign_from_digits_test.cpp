#include "tasty_int/detail/sign_from_digits.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/sign_test_common.hpp"


namespace {

using tasty_int::detail::sign_from_digits;
using tasty_int::detail::Sign;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;


const auto POSSIBLE_SIGNS = ::testing::Values(Sign::NEGATIVE,
                                              Sign::ZERO,
                                              Sign::POSITIVE);


class SignFromZeroDigitsTest : public ::testing::TestWithParam<Sign>
{}; //  class SignFromZeroDigitsTest

TEST_P(SignFromZeroDigitsTest, ReturnsZeroIfDigitsAreZero)
{
    std::vector<digit_type> ZERO = { 0 };
    Sign tentative_sign = GetParam();

    EXPECT_EQ(Sign::ZERO, sign_from_digits(ZERO, tentative_sign));
}

INSTANTIATE_TEST_SUITE_P(
    SignFromDigitsTest,
    SignFromZeroDigitsTest,
    POSSIBLE_SIGNS
);


class SignFromNonzeroDigitsTest
    : public ::testing::TestWithParam<std::tuple<Sign, std::vector<digit_type>>>
{}; //  class SignFromNonzeroDigitsTest

TEST_P(SignFromNonzeroDigitsTest, ReturnsTentativeSignIfDigitsAreNonzero)
{
    Sign                           tentative_sign = std::get<0>(GetParam());
    const std::vector<digit_type>& nonzero_digits = std::get<1>(GetParam());

    EXPECT_EQ(tentative_sign, sign_from_digits(nonzero_digits, tentative_sign));
}

INSTANTIATE_TEST_SUITE_P(
    SignFromDigitsTest,
    SignFromNonzeroDigitsTest,
    ::testing::Combine(
        POSSIBLE_SIGNS,
        ::testing::ValuesIn(
            std::vector<std::vector<digit_type>> {
                { 1 },
                { 2 },
                { DIGIT_TYPE_MAX },
                { 0, 1 },
                { 1, 2 },
                { 0, 0, 1 },
                { 1, 2, 3 },
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
            }
        )
    )
);

} // namespace
