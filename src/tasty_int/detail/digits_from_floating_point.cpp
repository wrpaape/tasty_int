#include "tasty_int/detail/digits_from_floating_point.hpp"

#include <cassert>
#include <cmath>


namespace tasty_int {
namespace detail {
namespace {

constexpr long double LONG_DOUBLE_DIGIT_TYPE_MAX = DIGIT_TYPE_MAX;

long double
log_base_digit_type_max(long double value)
{
    static const long double LOG_OF_DIGIT_TYPE_MAX =
        std::log(LONG_DOUBLE_DIGIT_TYPE_MAX);

    return std::log(value) / LOG_OF_DIGIT_TYPE_MAX;
}

std::vector<digit_type>::size_type
size_digits(long double value)
{
    return (value != 0.0L)
        ? static_cast<std::vector<digit_type>::size_type>(
              std::ceil(log_base_digit_type_max(value))
          )
        : 1;
}

} // namespace


std::vector<digit_type>
digits_from_floating_point(long double value)
{
    assert(std::isfinite(value));
    assert(value >= 0.0L);

    std::vector<digit_type> result(size_digits(value));

    auto cursor = result.begin();
    auto end    = result.end();
    do {
        *cursor = static_cast<digit_type>(value);
        value /= LONG_DOUBLE_DIGIT_TYPE_MAX;
    } while (++cursor != end);

    return result;
}

} // namespace detail
} // namespace tasty_int
