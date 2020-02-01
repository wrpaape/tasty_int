#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP

#include <cassert>

#include <limits>
#include <type_traits>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Extracts the least-significant digit from @p a value.
 *
 * @param[in] value a non-negative value
 * @return `value % DIGIT_BASE`
 *
 * @pre `value >= 0`
 */
template<typename T>
digit_type
digit_from_nonnegative_value(T value)
    requires std::is_arithmetic_v<T>
{
    constexpr bool DIGIT_TYPE_IS_TRUNCATED =
        (std::numeric_limits<digit_type>::max() > DIGIT_TYPE_MAX);

    constexpr bool ARITHMETIC_TYPE_IS_LARGER_THAN_DIGIT_TYPE_MAX =
        (static_cast<digit_accumulator_type>(std::numeric_limits<T>::max())
         > DIGIT_TYPE_MAX);

    constexpr bool TRUNCATE_ARITHMETIC_TYPE = DIGIT_TYPE_IS_TRUNCATED
        && ARITHMETIC_TYPE_IS_LARGER_THAN_DIGIT_TYPE_MAX;

    assert(value >= T(0));

    if constexpr (TRUNCATE_ARITHMETIC_TYPE) {
        return static_cast<digit_type>(value) & DIGIT_TYPE_MAX;
    } else {
        return static_cast<digit_type>(value);
    }
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP
