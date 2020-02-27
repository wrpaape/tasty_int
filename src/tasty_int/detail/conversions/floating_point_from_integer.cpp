#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"

#include <cassert>

#include "tasty_int/detail/conversions/floating_point_from_digits.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

long double
floating_point_from_integer(const Integer &integer)
{
    assert((integer.sign == Sign::NEGATIVE) ||
           (integer.sign == Sign::ZERO)     ||
           (integer.sign == Sign::POSITIVE));
    assert(!integer.digits.empty());

    long double result = floating_point_from_digits(integer.digits);

    if (integer.sign < Sign::ZERO)
        result = -result;

    return result;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
