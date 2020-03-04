#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"
#include "tasty_int/detail/trailing_zero.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

void
fill_digits(long double              value,
            std::vector<digit_type> &result)
{
    constexpr long double LONG_DOUBLE_DIGIT_BASE = DIGIT_BASE;

    auto cursor = result.begin();
    auto end    = result.end();
    do {
        *cursor = digit_from_nonnegative_value(value);
        value /= LONG_DOUBLE_DIGIT_BASE;
    } while (++cursor != end);
}

} // namespace


std::vector<digit_type>
digits_from_floating_point(long double value)
{
    assert(std::isfinite(value));
    assert(value >= 0.0L);

    std::vector<digit_type> result(
        size_digits_from_nonnegative_floating_point(value)
    );

    fill_digits(value, result);

    trim_trailing_zero(result);

    return result;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
