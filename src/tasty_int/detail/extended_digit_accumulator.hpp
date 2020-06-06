#ifndef TASTY_INT_TASTY_INT_DETAIL_EXTENDED_DIGIT_ACCUMULATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_EXTENDED_DIGIT_ACCUMULATOR_HPP

#include <cstddef>

#include <array>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/integral_digits_view.hpp"


namespace tasty_int {
namespace detail {

/**
 * This class provides a 3-digit buffer for handling arithmetic where a
 * digit_accumulator_type would otherwise overflow.
 */
class ExtendedDigitAccumulator : public std::array<digit_accumulator_type, 2>
{
public:
    /**
     * @brief Access the least-significant digit of the accumulator.
     *
     * @return the least-significant digit
     */
    digit_type
    low_digit() const
    {
        return digit_from_nonnegative_value(front());
    }

    /**
     * @brief Access the middle digit of the accumulator.
     *
     * @return the middle digit
     */
    digit_type
    middle_digit() const
    {
        return digit_from_nonnegative_value(front() >> DIGIT_TYPE_BITS);
    }

    /**
     * @brief Access the upper digit of the accumulator.
     *
     * @return the upper digit
     */
    digit_type
    high_digit() const
    {
        return digit_from_nonnegative_value(back());
    }

    /**
     * @brief Query the number of digits required to represent the accumulator.
     *
     * @return the number of digits required to represent the accumulator
     */
    std::size_t
    digits_size() const
    {
        auto have_middle_digit = (middle_digit() != 0);
        auto have_high_digit   = (high_digit()   != 0);

        return 1
             + (have_middle_digit | have_high_digit)
             + have_high_digit;
    }

    /**
     * @brief Left shift the accumulator by `DIGIT_TYPE_BITS`.
     */
    void
    multiply_digit_base()
    {
        back()  <<= DIGIT_TYPE_BITS;
        back()   |= (front() >> DIGIT_TYPE_BITS);
        front() <<= DIGIT_TYPE_BITS;
    }

    /**
     * @brief Left shift the accumulator by `DIGIT_TYPE_BITS` and add @p addend.
     *
     * @param[in] the digit to be added
     */
    void
    multiply_digit_base_accumulate(digit_type addend)
    {
        multiply_digit_base();
        front() |= addend;
    }
}; // class ExtendedDigitAccumulator


/**
 * @defgroup ExtendedDigitAccumulatorComparisonOperators ExtendedDigitAccumulator Comparison Operators
 *
 * These operations compare @p lhs and @p rhs as arrays of little-endian
 * digits.
 */
/// @{
bool
operator==(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs);
bool
operator!=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs);
bool
operator<(ExtendedDigitAccumulator lhs,
          ExtendedDigitAccumulator rhs);
bool
operator>(ExtendedDigitAccumulator lhs,
          ExtendedDigitAccumulator rhs);
bool
operator<=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs);
bool
operator>=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs);
/// @}


/**
 * @defgroup ExtendedDigitAccumulatorMultiplicationOperators ExtendedDigitAccumulator Multiplication Operators
 *
 * These operations return the produce of @p lhs and @p rhs as an array of
 * little-endian digits.
 */
/// @{
ExtendedDigitAccumulator
operator*(IntegralDigitsView lhs,
          digit_type         rhs);
ExtendedDigitAccumulator
operator*(digit_type         lhs,
          IntegralDigitsView rhs);
/// @}


/**
 * @defgroup ExtendedDigitAccumulatorSubtractionOperators ExtendedDigitAccumulator Subtraction Operators
 *
 * Subtract @p rhs from @lhs to produce a nonnegative result.
 *
 * @pre `lhs >= rhs`
 */
/// @{
ExtendedDigitAccumulator &
operator-=(ExtendedDigitAccumulator &lhs,
           ExtendedDigitAccumulator  rhs);
ExtendedDigitAccumulator &
operator-=(ExtendedDigitAccumulator &lhs,
           IntegralDigitsView        rhs);
/// @}


/**
 * @defgroup ExtendedDigitAccumulatorBitwiseOperators ExtendedDigitAccumulator Bitwise Operators
 */
/// @{
/// @pre `bit_offset < DIGIT_TYPE_BITS`
ExtendedDigitAccumulator &
operator>>=(ExtendedDigitAccumulator &lhs,
            unsigned int              bit_offset);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_EXTENDED_DIGIT_ACCUMULATOR_HPP
