#ifndef TASTY_INT_TASTY_INT_DETAIL_ABSOLUTE_VALUE_FROM_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_ABSOLUTE_VALUE_FROM_ARITHMETIC_HPP

#include <cmath>

#include <type_traits>

#include "tasty_int/concepts.hpp"


namespace tasty_int {
namespace detail {

/**
 * @defgroup AbsoluteValueFromArithmeticOverloads absolute_value_from_arithmetic Overloads
 *
 * These functions return the absolute value of the supplied @p value.
 *
 * @param[in] value an arithmetic value
 * @return the absolute value of @p operand.
 */
/// @{
template<tasty_int::UnsignedIntegral UnsignedIntegralType>
UnsignedIntegralType
absolute_value_from_arithmetic(UnsignedIntegralType value)
{
    return value;
}

template<tasty_int::SignedIntegral SignedIntegralType>
auto
absolute_value_from_arithmetic(SignedIntegralType value)
{
    using UnsignedIntegralType = std::make_unsigned_t<SignedIntegralType>;

    // avoid potential overflow of
    // std::abs(std::numeric_limits<SignedIntegralType>::lowest())
    auto absolute_value = static_cast<UnsignedIntegralType>(value);
    if (value < SignedIntegralType(0))
        absolute_value = -absolute_value;

    return absolute_value;
}

template<tasty_int::FloatingPoint FloatingPointType>
FloatingPointType
absolute_value_from_arithmetic(FloatingPointType value)
{
    return std::abs(value);
}
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_ABSOLUTE_VALUE_FROM_ARITHMETIC_HPP
