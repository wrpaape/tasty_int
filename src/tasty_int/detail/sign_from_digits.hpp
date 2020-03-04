#ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_FROM_DIGITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SIGN_FROM_DIGITS_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"
#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Retrieve the appropriate sign for the input @p digits.
 *
 * @param[in] digits       a little-endian sequence of digits
 * @param[in] nonzero_sign the tentative nonzero sign of @p digits
 * @return @p nonzero_sign if @p digits is nonzero, otherwise Sign::ZERO
 *
 * @pre @p nonzero_sign is one of Sign::NEGATIVE, Sign::ZERO, or Sign::POSITIVE.
 */
Sign
sign_from_digits(const std::vector<digit_type> &digits,
                 Sign                           nonzero_sign);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_FROM_DIGITS_HPP
