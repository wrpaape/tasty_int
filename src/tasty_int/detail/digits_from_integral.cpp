#include "tasty_int/detail/digits_from_integral.hpp"

namespace tasty_int {
namespace detail {

std::vector<digit_type>
digits_from_integral(std::uintmax_t value)
{
    std::vector<digit_type> digits;
    digits.reserve(2);
    digits.emplace_back(static_cast<digit_type>(value));
    if (value > DIGIT_TYPE_MAX)
        digits.emplace_back(static_cast<digit_type>(value >> DIGIT_TYPE_BITS));

    return digits;
}

} // namespace detail
} // namespace tasty_int
