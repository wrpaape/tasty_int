#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/conversions/digit_from_nonnegative_value.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

long double
log_digit_base(long double value)
{
    constexpr long double LOG2_DIGIT_BASE = DIGIT_TYPE_BITS;

    return std::log2(value) / LOG2_DIGIT_BASE;
}

std::vector<digit_type>::size_type
size_digits(long double value)
{
    return (value > 1.0L)
        ? static_cast<std::vector<digit_type>::size_type>(
              std::floor(log_digit_base(value))
          ) + 1
        : 1;
}

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

bool
have_trailing_zero(const std::vector<digit_type> &result)
{
    return ((result.size() > 1) && (result.back() == 0));
}

void
trim_trailing_zero(std::vector<digit_type> &result)
{
    if (have_trailing_zero(result))
        result.pop_back();
}

} // namespace


std::vector<digit_type>
digits_from_floating_point(long double value)
{
    assert(std::isfinite(value));
    assert(value >= 0.0L);

    std::vector<digit_type> result(size_digits(value));

    fill_digits(value, result);

    trim_trailing_zero(result);

    return result;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
