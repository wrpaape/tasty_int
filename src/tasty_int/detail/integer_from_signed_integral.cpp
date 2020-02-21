#include "tasty_int/detail/integer_from_signed_integral.hpp"

#include <cmath>

#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/digits_from_integral.hpp"


namespace tasty_int {
namespace detail {

Integer
integer_from_signed_integral(std::intmax_t value)
{
    Integer result;
    result.sign   = sign_from_signed_arithmetic(value);
    result.digits = digits_from_integral(std::abs(value));
    return result;
}

} // namespace detail
} // namespace tasty_int
