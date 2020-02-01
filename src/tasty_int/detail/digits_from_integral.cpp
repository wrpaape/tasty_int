#include "tasty_int/detail/digits_from_integral.hpp"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace tasty_int {
namespace detail {

std::vector<digit_type>
digits_from_integral(std::uintmax_t value)
{
    std::vector<digit_type> digits;
    digits.reserve(2);
    digits.emplace_back(digit_from_nonnegative_value(value));
    if (value > DIGIT_TYPE_MAX)
        digits.emplace_back(
            digit_from_nonnegative_value(value >> DIGIT_TYPE_BITS)
        );

    return digits;
}

} // namespace detail
} // namespace tasty_int
