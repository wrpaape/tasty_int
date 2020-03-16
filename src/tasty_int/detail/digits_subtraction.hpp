#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_SUBTRACTION_OPERATORS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_SUBTRACTION_OPERATORS_HPP

#include <cstdint>

#include <utility>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"
#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {

/**
 * @defgroup DigitsSubtractionOperations Digits Subtraction Operations
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 * They produce the signed result of `minuend - subtrahend`.
 *
 * @pre input digits vectors must be non-empty
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */

/**
 * @defgroup InPlaceDigitsSubtractionOperations In-Place Digits Subtraction Operations
 * @ingroup DigitsSubtractionOperations
 *
 * @brief Execute `minuend -= subtrahend`.
 *
 * @param[in]     subtrahend the value subtracted from @p minuend
 * @param[in,out] minuend    the value from which @p subtrahend is subtracted
 * @return the Sign of the result
 */
/// @{
Sign
subtract_in_place(const std::vector<digit_type> &subtrahend,
                  std::vector<digit_type>       &minuend);

Sign
subtract_in_place(std::uintmax_t           subtrahend,
                  std::vector<digit_type> &minuend);
Sign
subtract_in_place(long double              subtrahend,
                  std::vector<digit_type> &minuend);
/// @}

/**
 * @defgroup ImmutableDigitsSubtractionOperations Immutable Digits Subtraction Operations
 * @ingroup DigitsSubtractionOperations
 *
 * @brief Execute `minuend - subtrahend`.
 *
 * @param[in] minuend    the value from which @p subtrahend is subtracted
 * @param[in] subtrahend the value subtracted from @p minuend
 * @return `{ .first = <sign of result>, .second = <result digits> }`
 */
/// @{
std::pair<Sign, std::vector<digit_type>>
subtract(const std::vector<digit_type> &minuend,
         const std::vector<digit_type> &subtrahend);

std::pair<Sign, std::vector<digit_type>>
subtract(std::uintmax_t                 minuend,
         const std::vector<digit_type> &subtrahend);

std::pair<Sign, std::vector<digit_type>>
subtract(long double                    minuend,
         const std::vector<digit_type> &subtrahend);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_SUBTRACTION_OPERATORS_HPP
