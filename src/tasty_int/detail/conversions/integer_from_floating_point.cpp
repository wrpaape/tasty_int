#include "tasty_int/detail/conversions/integer_from_floating_point.hpp"

#include <cmath>

#include "tasty_int/detail/conversions/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

Integer
integer_from_floating_point(long double value)
{
    Integer result;
    result.sign   = sign_from_signed_arithmetic(value);
    result.digits = digits_from_floating_point(std::abs(value));
    return result;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
