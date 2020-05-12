#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP

#include <cassert>
#include <cmath>

#include <limits>
#include <type_traits>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Extracts the least-significant digit from @p a value.
 *
 * @tparam IntegralType an integral type
 * @param[in] value a non-negative value
 * @return `value % DIGIT_BASE`
 *
 * @pre `value >= 0`
 */
template<typename IntegralType>
digit_type
digit_from_nonnegative_value(IntegralType value)
    requires std::is_integral_v<IntegralType>
{
    constexpr bool DIGIT_TYPE_IS_TRUNCATED =
        (std::numeric_limits<digit_type>::max() > DIGIT_TYPE_MAX);

    constexpr digit_accumulator_type INTEGRAL_TYPE_MAX =
        std::numeric_limits<IntegralType>::max();

    constexpr bool INTEGRAL_TYPE_IS_LARGER_THAN_DIGIT_TYPE_MAX =
        (INTEGRAL_TYPE_MAX > DIGIT_TYPE_MAX);

    constexpr bool TRUNCATE_INTEGRAL_TYPE = DIGIT_TYPE_IS_TRUNCATED
        && INTEGRAL_TYPE_IS_LARGER_THAN_DIGIT_TYPE_MAX;

    assert(value >= IntegralType(0));

    if constexpr (TRUNCATE_INTEGRAL_TYPE)
        return static_cast<digit_type>(value) & DIGIT_TYPE_MAX;
    else
        return static_cast<digit_type>(value);
}

/**
 * @brief Extracts the least-significant digit from @p a value.
 *
 * @tparam FloatingPointType a floating-point type
 * @param[in] value a non-negative value
 * @return `std::fmod(value, DIGIT_BASE)`
 *
 * @pre `value >= 0`
 */
template<typename FloatingPointType>
digit_type
digit_from_nonnegative_value(FloatingPointType value)
    requires std::is_floating_point_v<FloatingPointType>
{
    constexpr FloatingPointType FLOATING_POINT_DIGIT_BASE = DIGIT_BASE;

    assert(value >= FloatingPointType(0));

    return static_cast<digit_type>(std::fmod(value, FLOATING_POINT_DIGIT_BASE));
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_FROM_NONNEGATIVE_VALUE_HPP
