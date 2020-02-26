#include "tasty_int/detail/conversions/floating_point_from_digits.hpp"

#include <cassert>


namespace tasty_int {
namespace detail {
namespace conversions {

long double
floating_point_from_digits(const std::vector<digit_type> &digits)
{
    assert(!digits.empty());

    constexpr long double LONG_DOUBLE_DIGIT_BASE = DIGIT_BASE;

    long double value = 0.0;

    auto digit       = digits.rbegin();
    auto digits_rend = digits.rend();
    while (true)
    {
        value += *digit;

        if (++digit == digits_rend)
            break;

        value *= LONG_DOUBLE_DIGIT_BASE;
    }

    return value;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
