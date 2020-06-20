#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"

#include <cassert>

#include "tasty_int/detail/conversions/integral_from_digits.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

std::uintmax_t
unsigned_integral_from_integer(const Integer &integer)
{
    assert((integer.sign == Sign::NEGATIVE) ||
           (integer.sign == Sign::ZERO)     ||
           (integer.sign == Sign::POSITIVE));
    assert(!integer.digits.empty());

    std::uintmax_t value = integral_from_digits(integer.digits);

    // unsigned overflow cannot occur - modulo wrapping is well-defined
    // behavior: C11 standard (ISO/IEC 9899:2011) section 6.3 Conversions (p:
    // 50-56)
    if (integer.sign < Sign::ZERO)
        value = -value;

    return value;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
