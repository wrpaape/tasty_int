#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGRAL_DIGITS_VIEW_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGRAL_DIGITS_VIEW_HPP

#include <cstdint>
#include <cstddef>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace tasty_int {
namespace detail {

/**
 * This class provides common access to an integral value as a pair of digits.
 */
class IntegralDigitsView
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] value the integral value
     */
    IntegralDigitsView(std::uintmax_t value)
        : integral_value(value)
    {}

    /**
     * @brief Access the least-significant digit of the integral value.
     *
     * @return the least-significant digit
     */
    digit_type
    low_digit() const
    {
        return digit_from_nonnegative_value(integral_value);
    }

    /**
     * @brief Access the most-significant digit of the integral value.
     *
     * @return the most-significant digit
     */
    digit_type
    high_digit() const
    {
        return digit_from_nonnegative_value(integral_value >> DIGIT_TYPE_BITS);
    }

    /**
     * @brief Query the number of digits required to represent the integral
     *     value.
     *
     * @return the number of digits required to represent the integral value
     */
    std::size_t
    digits_size() const
    {
        return 1 + (integral_value > DIGIT_TYPE_MAX);
    }

private:
    std::uintmax_t integral_value;
}; // class IntegralDigitsView

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGRAL_DIGITS_VIEW_HPP
