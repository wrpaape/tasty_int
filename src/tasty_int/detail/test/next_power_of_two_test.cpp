#include "tasty_int/detail/next_power_of_two.hpp"

#include "gtest/gtest.h"

#include <limits>
#include <utility>
#include <vector>


namespace {

using tasty_int::detail::next_power_of_two;


std::vector<std::pair<std::uintmax_t, std::uintmax_t>>
make_test_params()
{
    constexpr auto MAX_EXPONENT =
        std::numeric_limits<std::uintmax_t>::digits - 1;

    std::vector<std::pair<std::uintmax_t, std::uintmax_t>> test_params;

    for (auto exponent = 0; exponent < MAX_EXPONENT; ++exponent) {
        auto next_exponent = exponent + 1;
        auto next_power    = std::uintmax_t(1) << next_exponent;
        auto power         = next_power >> 1;
        auto next_value    = power + (power > 1);
        auto mid_value     = power + ((next_power - power) / 2);
        auto last_value    = next_power - 1;

        test_params.emplace_back(power,      next_power);
        test_params.emplace_back(next_value, next_power);
        test_params.emplace_back(mid_value,  next_power);
        test_params.emplace_back(last_value, next_power);
    }

    return test_params;
}


class NextPowerOfTwoTest
    : public ::testing::TestWithParam<std::pair<std::uintmax_t, std::uintmax_t>>
{}; // class NextPowerOfTwoTest

TEST_P(NextPowerOfTwoTest, TestNextPowerOfTwo)
{
    auto [value, expected_result] = GetParam();

    auto result = next_power_of_two(value);

    EXPECT_EQ(expected_result, result);
}

INSTANTIATE_TEST_SUITE_P(
   NextPowerOfTwoTest,
   NextPowerOfTwoTest,
   ::testing::ValuesIn(
        make_test_params()
   )
);

} // namespace
