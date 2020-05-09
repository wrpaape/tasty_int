#include "tasty_int/detail/sign_from_digits.hpp"

#include <cassert>

#include "tasty_int/detail/is_zero.hpp"


namespace tasty_int {
namespace detail {

Sign
sign_from_digits(const std::vector<digit_type> &digits,
                 Sign                           nonzero_sign)
{
    assert((nonzero_sign == Sign::NEGATIVE) ||
           (nonzero_sign == Sign::ZERO)     ||
           (nonzero_sign == Sign::POSITIVE));

    auto is_zero_value      = static_cast<unsigned int>(is_zero(digits));
    auto nonzero_sign_mask  = is_zero_value - 1u;
    auto nonzero_sign_value = static_cast<unsigned int>(nonzero_sign);

    return static_cast<Sign>(nonzero_sign_mask & nonzero_sign_value);
}

} // namespace detail
} // namespace tasty_int
