#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP

#include <cstdint>

#include <utility>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @defgroup DigitsAdditionOperators Digits Addition Operators
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 *
 * @pre input digits vectors must be non-empty
 * @pre input digits may have no leading zeros
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */
/// @{
std::vector<digit_type> &
operator+=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs);

std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs);

std::uintmax_t &
operator+=(std::uintmax_t                &lhs,
           const std::vector<digit_type> &rhs);

/**
 * @defgroup DigitsAdditionFloatingPointOverloads Digits Addition Floating Point Overloads
 *
 * These operations truncate their operand towards zero to the nearest integer
 * before adding.
 *
 * @pre floating point operand is finite
 */
/**
 * @ingroup DigitsAdditionFloatingPointOverloads
 *
 * /@pre `rhs >= 0.0`
 */
std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           long double              rhs);

/**
 * @ingroup DigitsAdditionFloatingPointOverloads
 *
 * @note this overload does have the same restrictions on its floating point
 *     operand, @p lhs, as the other floating point overloads and does not
 *     truncate it before adding.
 */
long double &
operator+=(long double                   &lhs,
           const std::vector<digit_type> &rhs);

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs);

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs);

std::vector<digit_type>
operator+(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs);

/// @ingroup DigitsAdditionFloatingPointOverloads
std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          long double                    rhs);

/// @ingroup DigitsAdditionFloatingPointOverloads
std::vector<digit_type>
operator+(long double                    lhs,
          const std::vector<digit_type> &rhs);
/// @}

/**
 * @defgroup LowLevelDigitsAdditionOperations Low-Level Digits Addition Operations
 *
 * These lower-level addition operations are exposed for re-use in other
 * modules requiring finer-controlled addition.  No dynamic memory allocation
 * takes place in these operations.
 */
/// @{
/**
 * @brief Add a series of digits, @p addend, into the lower digits of @p augend
 *     without applying applying the carry.
 *
 * @param[in]     addend the digits to be added into @p augend
 * @param[in,out] augend the accumulating digits
 *
 * @return `{ .first = <carry>, .second = augend.begin() + addend.size() }`
 *
 * @pre `augend.size() >= addend.size()`
 */
std::pair<digit_accumulator_type, std::vector<digit_type>::iterator>
add_into(const std::vector<digit_type> &addend,
         std::vector<digit_type>       &augend);

/**
 * @brief Perform a carry operation.
 *
 * @param[in] carry         the overflow from lower-order addition
 * @param[in] augend_cursor the first position of the destination digits that
 *     @p carry should be applied
 * @param[in] augend_end    one past the end of the destination digits
 *
 * @return 0 if the carry could be applied to the destination digits without
 *     overflow, otherwise, the value of the overflow
 *
 * @pre `augend.size() >= addend.size()`
 */
digit_accumulator_type
propagate_carry(digit_accumulator_type                  carry,
                std::vector<digit_type>::iterator       augend_cursor,
                std::vector<digit_type>::const_iterator augend_end);

/**
 * @brief Add into a single digit.
 *
 * @param[in] addend        the value to be added
 * @param[in] augend_cursor the destination digit
 *
 * @return carry
 *
 * @pre `augend.size() >= addend.size()`
 */
digit_accumulator_type
add_at(digit_accumulator_type            addend,
       std::vector<digit_type>::iterator augend_cursor);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP
