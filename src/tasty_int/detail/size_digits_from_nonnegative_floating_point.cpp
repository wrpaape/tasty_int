#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace {

long double
log_digit_base(long double value)
{
    constexpr long double LOG2_DIGIT_BASE = DIGIT_TYPE_BITS;

    return std::log2(value) / LOG2_DIGIT_BASE;
}

} // namespace


std::size_t
size_digits_from_nonnegative_floating_point(long double value)
{
    assert(std::isfinite(value));
    assert(value >= 0.0L);

    constexpr long double LONG_DOUBLE_DIGIT_TYPE_MAX = DIGIT_TYPE_MAX;

    std::size_t digits_size = 1;

    if (value > LONG_DOUBLE_DIGIT_TYPE_MAX)
        digits_size += static_cast<std::size_t>(std::floor(log_digit_base(value)));

    return digits_size;
}

} // namespace detail
} // namespace tasty_int
