#include "tasty_int/detail/int_from_signed_integral.hpp"

#include <cmath>

#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/digits_from_integral.hpp"


namespace tasty_int {
namespace detail {

/**
 * TODO
 */
Int
int_from_signed_integral(std::intmax_t value)
{
    Int result;
    result.sign   = sign_from_signed_arithmetic(value);
    result.digits = digits_from_integral(std::abs(value));
    return result;
}

} // namespace detail
} // namespace tasty_int
