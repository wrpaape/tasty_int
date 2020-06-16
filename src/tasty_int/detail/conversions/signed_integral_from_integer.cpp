#include "tasty_int/detail/conversions/signed_integral_from_integer.hpp"

#include <cassert>

#include <limits>

#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/intmax_t_from_uintmax_t.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

std::intmax_t
signed_integral_from_integer(const Integer &integer)
{
    assert((integer.sign == Sign::NEGATIVE) ||
           (integer.sign == Sign::ZERO)     ||
           (integer.sign == Sign::POSITIVE));
    assert(!integer.digits.empty());

    std::uintmax_t unsigned_value = unsigned_integral_from_integer(integer);

    std::intmax_t value = intmax_t_from_uintmax_t(unsigned_value);

    return value;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
