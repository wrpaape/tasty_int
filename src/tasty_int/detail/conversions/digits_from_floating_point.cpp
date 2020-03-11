#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/floating_point_digits_iterator.hpp"
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
    FloatingPointDigitsIterator value_cursor(value);
    auto result_cursor = result.begin();
    auto result_end    = result.end();
    do {
        *result_cursor = *value_cursor;
        ++value_cursor;
    } while (++result_cursor != result_end);
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
