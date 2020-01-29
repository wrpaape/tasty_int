#include "tasty_int/detail/int_from_floating_point.hpp"

#include <cmath>

#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/digits_from_floating_point.hpp"


namespace tasty_int {
namespace detail {

Int
int_from_floating_point(long double value)
{
    Int result;
    result.sign   = sign_from_signed_arithmetic(value);
    result.digits = digits_from_floating_point(std::abs(value));
    return result;
}

} // namespace detail
} // namespace tasty_int
