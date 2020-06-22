#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"

#include "tasty_int/detail/absolute_value_from_arithmetic.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

Integer
integer_from_signed_integral(std::intmax_t value)
{
    Integer result;
    result.sign   = sign_from_signed_arithmetic(value);
    result.digits = digits_from_integral(absolute_value_from_arithmetic(value));
    return result;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
