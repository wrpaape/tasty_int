#ifndef TASTY_INT_TASTY_INT_IPP
#define TASTY_INT_TASTY_INT_IPP

#include "tasty_int/tasty_int.hpp"


namespace tasty_int {
namespace detail {

/**
 * @defgroup TastyIntDetailPrepareOperand tasty_int::detail::prepare_operand
 *
 * Distills tasty_int::TastyIntOperands into types that are operable with
 * tasty_int::detail::Integer.
 */
/// @{
inline const detail::Integer &
prepare_operand(const TastyInt &operand)
{
    return operand.integer;
}

template<FloatingPoint FloatingPointType>
auto
prepare_operand(FloatingPointType operand)
{
    return static_cast<long double>(operand);
}

template<SignedIntegral SignedIntegralType>
auto
prepare_operand(SignedIntegralType operand)
{
    return static_cast<std::intmax_t>(operand);
}

template<UnsignedIntegral UnsignedIntegralType>
auto
prepare_operand(UnsignedIntegralType operand)
{
    return static_cast<std::uintmax_t>(operand);
}
/// @}

} // namespace detail


/**
 * @defgroup TastyIntComparisonOperators TastyInt Comparison Operators
 *
 * These operators compare tasty_int::TastyInt and another arithmetic operand
 * or tasty_int::TastyInt like ordinary ints:
 *     
 *     - positive values are greater than zero
 *     - positive values compare greater as their magnitude increases
 *     - negative values are less than zero
 *     - negative values compare lesser as their magnitude increases
 *
 * with the exception that floating point values are truncated toward zero.
 */
/// @{
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator==(const LhsType &lhs,
           const RhsType &rhs)
{
    return detail::prepare_operand(lhs) == detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator!=(const LhsType &lhs,
           const RhsType &rhs)
{
    return detail::prepare_operand(lhs) != detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator<(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) < detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator>(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) > detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator<=(const LhsType &lhs,
           const RhsType &rhs)
{
    return detail::prepare_operand(lhs) <= detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator>=(const LhsType &lhs,
           const RhsType &rhs)
{
    return detail::prepare_operand(lhs) >= detail::prepare_operand(rhs);
}
/// @}

} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_IPP
