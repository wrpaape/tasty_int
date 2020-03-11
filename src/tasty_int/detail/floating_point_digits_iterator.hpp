#ifndef TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_DIGITS_ITERATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_DIGITS_ITERATOR_HPP

#include <cassert>
#include <cmath>
#include <cstddef>

#include <iterator>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace tasty_int {
namespace detail {

/**
 * This class provides InputIterator access to the digits of a
 * nonnegative floating point value in little-endian order.
 */
class FloatingPointDigitsIterator
{
public:
    /// @{
    /// Required for STL-compliance.
    using iterator_category = std::input_iterator_tag;
    using value_type        = tasty_int::detail::digit_type;
    using reference         = value_type;
    using pointer           = value_type *;
    using difference_type   = std::ptrdiff_t;
    /// @}

    /**
     * @brief Constructor.
     *
     * @param[in] value the floating point value
     *
     * @pre @p value is nonnegative
     */
    FloatingPointDigitsIterator(long double value)
        : rem_value(value)
    {
        assert(value >= 0.0L);
    }

    /**
     * @brief Dereference operator.
     *
     * @return the next digit
     */
    digit_type
    operator*() const
    {
        return digit_from_nonnegative_value(rem_value);
    }

    /**
     * @brief Pre-increment operator.
     *
     * @details Advance to the next digit.
     *
     * @return a reference to `*this`
     */
    FloatingPointDigitsIterator &
    operator++()
    {
        constexpr long double LONG_DOUBLE_DIGIT_BASE = DIGIT_BASE;

        rem_value /= LONG_DOUBLE_DIGIT_BASE;

        return *this;
    }

    /**
     * @brief Post-increment operator.
     *
     * @details Save the original value, then advance to the next digit.
     *
     * @return an copy of the original value of `*this`
     */
    FloatingPointDigitsIterator
    operator++(int)
    {
        FloatingPointDigitsIterator prev(rem_value);

        ++*this;

        return prev;
    }

    /**
     * @brief Access the remaining floating point value.
     *
     * @details FloatingPointDigitsIterator traverses its digits by repeatedly
     *     dividing the input value by DIGIT_BASE and returning the remainder.
     *     This accessor exposes the remaining value.
     *
     * @return the remaining value.
     */
    long double
    remaining_value() const
    {
        return rem_value;
    }

private:
    long double rem_value;
}; // class FloatingPointDigitsIterator


/**
 * @brief Equality operator.
 *
 * @param[in] lhs the left-hand side of the operator
 * @param[in] rhs the right-hand side of the operator
 * @return true if @p lhs and @p rhs will generate the same sequence of digits
 */
inline bool
operator==(FloatingPointDigitsIterator lhs,
           FloatingPointDigitsIterator rhs)
{
    return std::floor(lhs.remaining_value())
        == std::floor(rhs.remaining_value());
}

/**
 * @brief Inequality operator.
 *
 * @param[in] lhs the left-hand side of the operator
 * @param[in] rhs the right-hand side of the operator
 * @return true if @p lhs and @p rhs will *not* generate the same sequence of
 *     digits
 */
inline bool
operator!=(FloatingPointDigitsIterator lhs,
           FloatingPointDigitsIterator rhs)
{
    return !(lhs == rhs);
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_DIGITS_ITERATOR_HPP
