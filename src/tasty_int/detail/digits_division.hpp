#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_DIVISION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_DIVISION_HPP

#include <cstddef>

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * The result of an immutable division operation involving digits.
 */
struct DigitsDivisionResult
{
    std::vector<digit_type> quotient;  ///< the division quotient
    std::vector<digit_type> remainder; ///< the division remainder
}; // struct DigitsDivisionResult


/**
 * @defgroup DigitsDivisionOperators Digits Division Operations
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 * They produce the quotient and remainder of `dividend / divisor`.
 *
 * @pre input digits vectors must be non-empty
 * @pre input digits may have no leading zeros
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */

/**
 * @defgroup InPlaceDigitsDivisionOperations In-Place Digits Division Operations
 * @ingroup DigitsDivisionOperations
 *
 * @brief Execute `dividend /= divisor`.
 *
 * @param[in]     divisor  the value by which @p dividend is divided
 * @param[in,out] dividend the value from which @p divisor is divided
 * @return the remainder
 */
/// @{
std::vector<digit_type>
divide_in_place(const std::vector<digit_type> &divisor,
                std::vector<digit_type>       &dividend);

std::vector<digit_type>
divide_in_place(std::uintmax_t           divisor,
                std::vector<digit_type> &dividend);
/// @}

/**
 * @defgroup ImmutableDigitsDivisionOperations Immutable Digits Division Operations
 * @ingroup DigitsDivisionOperations
 *
 * @brief Execute `dividend / divisor`.
 *
 * @param[in] dividend the value from which @p divisor is divided
 * @param[in] divisor  the value by which @p dividend is divided
 * @return the quotient and remainder
 */
/// @{
DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       const std::vector<digit_type> &divisor);

DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       std::uintmax_t                 divisor);
/// @}

/**
 * @defgroup DigitsDivisionAlgorithms Digits Division Algorithms
 *
 * These algorithms implement the `divide` routines.
 *
 * @param[in] dividend the value from which @p divisor is divided
 * @param[in] divisor  the value by which @p dividend is divided
 * @return the quotient and remainder
 */
/// @{
/// @pre `dividend > divisor`
DigitsDivisionResult
long_divide(const std::vector<digit_type> &dividend,
            const std::vector<digit_type> &divisor);

DigitsDivisionResult
divide_and_conquer_divide(const std::vector<digit_type> &dividend,
                          const std::vector<digit_type> &divisor);

/**
 * @pre `high digit(divisor) >= DIGIT_BASE/2`
 * @pre `dividend <= divisor*DIGIT_BASE^n` where `n` is defined as
 *     `DIGIT_BASE^n/2 <= divisor < DIGIT_BASE^n`
 */
DigitsDivisionResult
divide_normalized_2n_1n_split(const std::vector<digit_type> &dividend,
                              const std::vector<digit_type> &divisor);

/**
 * @pre `high digit(divisor) >= DIGIT_BASE/2`
 * @pre `dividend <= divisor*DIGIT_BASE^n` where `n` is defined as
 *     `DIGIT_BASE^(2n)/2 <= divisor < DIGIT_BASE^(2n)`
 */
DigitsDivisionResult
divide_normalized_3n_2n_split(const std::vector<digit_type> &dividend,
                              const std::vector<digit_type> &divisor);

/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_DIVISION_HPP
