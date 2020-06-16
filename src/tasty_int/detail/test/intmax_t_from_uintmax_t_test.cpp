#include "tasty_int/detail/intmax_t_from_uintmax_t.hpp"

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::intmax_t_from_uintmax_t;


class IntmaxTFromUintmaxTTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class IntmaxTFromUintmaxTTest

TEST_P(IntmaxTFromUintmaxTTest, SafelyConvertsValue)
{
    std::intmax_t  original_value = GetParam();
    std::uintmax_t unsigned_value = static_cast<std::uintmax_t>(original_value);

    std::intmax_t signed_value = intmax_t_from_uintmax_t(unsigned_value);

    EXPECT_EQ(original_value, signed_value);
}

INSTANTIATE_TEST_SUITE_P(
    NonnegativeValuesTest,
    IntmaxTFromUintmaxTTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        0, std::numeric_limits<std::intmax_t>::max(), 2
    )
);

INSTANTIATE_TEST_SUITE_P(
    NegativeValuesTest,
    IntmaxTFromUintmaxTTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);

} // namespace
