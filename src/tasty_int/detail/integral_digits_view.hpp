#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGRAL_DIGITS_VIEW_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGRAL_DIGITS_VIEW_HPP

#include <cstddef>
#include <cstdint>

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
     * @brief Access the integral value.
     *
     * @return the integral value
     */
    std::uintmax_t
    value() const
    {
        return integral_value;
    }

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
     * @brief Access the upper digit of the integral value.
     *
     * @return the upper digit
     */
    digit_type
    high_digit() const
    {
        return digit_from_nonnegative_value(integral_value >> DIGIT_TYPE_BITS);
    }

    /**
     * @brief Access the most-significant (nonzero) digit of the integral value.
     *
     * @return the most-significant nonzero digit
     */
    digit_type
    most_significant_digit() const
    {
        auto most_significant = high_digit();
        if (most_significant == 0)
            most_significant = low_digit();

        return most_significant;
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
