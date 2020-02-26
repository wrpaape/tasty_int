#include "tasty_int/detail/conversions/integral_from_digits.hpp"

#include <cassert>


namespace tasty_int {
namespace detail {
namespace conversions {

std::uintmax_t
integral_from_digits(const std::vector<digit_type> &digits)
{
    assert(!digits.empty());

    std::uintmax_t value = digits.front();

    if (digits.size() > 1) {
        auto next_digit  = static_cast<std::uintmax_t>(digits[1]);
        value           |= (next_digit << DIGIT_TYPE_BITS);
    }

    return value;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
