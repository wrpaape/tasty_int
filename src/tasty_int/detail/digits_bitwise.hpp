#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Multiply @p multiplicand by `DIGIT_BASE`.
 *
 * @param[in] multiplicand the digits to be multiplied
 * @return `multiplicand * DIGIT_BASE`
 *
 * @pre `multiplicand != 0`
 */
/// @todo: TODO: remove if not required by digits_division
std::vector<digit_type>
multiply_digit_base(const std::vector<digit_type> &multiplicand);

/**
 * @brief Multiply @p multiplicand by `DIGIT_BASE^exponent`.
 *
 * @param[in]     exponent     the desired power of `DIGIT_BASE`
 * @param[in,out] multiplicand the digits to be multiplied
 */
void
multiply_digit_base_power_in_place(
    std::vector<digit_type>::size_type  exponent,
    std::vector<digit_type>            &multiplicand
);

/**
 * A pair of exponents that describe the multiplier:
 *
 *     DIGIT_BASE^digit_base * 2^two
 */
struct MultiplierExponents
{
    std::vector<digit_type>::size_type digit_base;
    unsigned int                       two;
}; // struct MultiplierExponents
/**
 * @brief Multiply @p multiplicand by `DIGIT_BASE^exponents.digit_base *
 *    2^exponents.two`.
 *
 * @param[in] multiplicand the digits to be multiplied
 * @param[in] exponents    the desired power components of the multiplier
 * @return `multiplicand * DIGIT_BASE^exponents.digit_base * 2^exponents.two`.
 *
 * @pre `exponents.two < DIGIT_TYPE_BITS`
 * @pre `multiplicand != 0`
 */
std::vector<digit_type>
multiply_powers(const std::vector<digit_type> &multiplicand,
                MultiplierExponents           exponents);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_BITWISE_HPP
