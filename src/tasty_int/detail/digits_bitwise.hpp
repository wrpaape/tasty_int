#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * A pair of offsets that describe an arbitrary shift of
 * `DIGIT_TYPE_BITS*digits + bits` bits.
 */
struct DigitsShiftOffset
{
    /// number of digits
    std::vector<digit_type>::size_type digits;
    /// number of leftover bits (require < DIGIT_TYPE_BITS)
    unsigned int                       bits;
}; // struct DigitsShiftOffset

/**
 * @brief Counts the number of 0-bits beyond the most-significant 1-bit.
 *
 * @param[in] digit a positive digit
 */
unsigned int
count_leading_zero_bits_from_digit(digit_type digit);

/**
 * @brief Left shift @p digits by @p digit_offset digits.
 *
 * @param[in] digits       the digits to be shifted
 * @param[in] digit_offset the desired number of digits to be shifted
 * @return a reference to @p digits
 */
std::vector<digit_type> &
operator<<=(std::vector<digit_type>            &digits,
            std::vector<digit_type>::size_type  digit_offset);

/**
 * @brief Left shift @p digits by @p offset.
 *
 * @details Equivalent to a multiplication of @p digits by
 *     `DIGIT_BASE^offset.digits * 2^offset.bits`.
 *
 * @param[in] digits the digits to be shifted
 * @param[in] offset the size of the shift
 * @return @p digits shifted left by @p offset
 *
 * @pre `offset.bits < DIGIT_TYPE_BITS`
 */
std::vector<digit_type>
operator<<(const std::vector<digit_type> &digits,
           DigitsShiftOffset              offset);

/**
 * @brief Right shift @p digits by @p offset.
 *
 * @details Equivalent to a division of @p digits by `DIGIT_BASE^offset.digits
 *     2^offset.bits`.
 *
 * @param[in] digits the digits to be shifted
 * @param[in] offset the size of the shift
 * @return @p digits shifted left by @p offset
 *
 * @pre `offset.bits < DIGIT_TYPE_BITS`
 */
std::vector<digit_type> &
operator>>=(std::vector<digit_type> &digits,
            DigitsShiftOffset        offset);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP
