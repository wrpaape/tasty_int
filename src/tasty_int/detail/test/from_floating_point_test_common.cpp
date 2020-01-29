#include "tasty_int/detail/test/from_floating_point_test_common.hpp"

#include <cmath>

#include "gtest/gtest.h"


using namespace tasty_int::detail;

namespace from_floating_point_test_common {

void
expect_digits_equal(long double                    expected,
                    const std::vector<digit_type> &digits)
{
    std::size_t index = 0;

    do {
        digit_type next_digit = static_cast<digit_type>(expected);
        EXPECT_EQ(next_digit, digits.at(index++));
        expected /= DIGIT_TYPE_MAX;
    } while (expected >= 1.0L);

    EXPECT_EQ(index, digits.size());
}

} // namespace from_floating_point_test_common
