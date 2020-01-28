#include "tasty_int/detail/int_from_unsigned_integral.hpp"

#include <cmath>

#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/digits_from_integral.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief constructs a new tasty_int::detail::Int from @p value
 *
 * @param[in] value an unsigned integer value
 * @return the tasty_int::detail:Int representation of @p value
 */
Int
int_from_unsigned_integral(std::uintmax_t value)
{
    Int result;
    result.sign   = sign_from_unsigned_arithmetic(value);
    result.digits = digits_from_integral(value);
    return result;
}

} // namespace detail
} // namespace tasty_int
