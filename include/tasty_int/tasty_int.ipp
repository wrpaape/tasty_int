#ifndef TASTY_INT_TASTY_INT_IPP
#define TASTY_INT_TASTY_INT_IPP

#include "tasty_int/tasty_int.hpp"

#include "tasty_int/detail/integer_comparison.hpp"
#include "tasty_int/detail/integer_multiplication.hpp"
#include "tasty_int/detail/integer_output.hpp"


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

inline detail::Integer &
prepare_operand(TastyInt &operand)
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


/**
 * @defgroup TastyIntAdditionOperators TastyInt Addition Operators
 *
 * These operators apply addition to tasty_int::detail::TastyInt and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before addition.
 */
/// @{
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator+=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = detail::prepare_operand(lhs);

    lhs_operand += detail::prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
TastyInt
operator+(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) + detail::prepare_operand(rhs);
}
/// @}


/**
 * @defgroup TastyIntSubtractionOperators TastyInt Subtraction Operators
 *
 * These operators apply subtraction to tasty_int::detail::TastyInt and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before subtraction.
 */
/// @{
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator-=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = detail::prepare_operand(lhs);

    lhs_operand -= detail::prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
TastyInt
operator-(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) - detail::prepare_operand(rhs);
}
/// @}


/**
 * @defgroup TastyIntMultiplicationOperators TastyInt Multiplication Operators
 *
 * These operators apply multiplication to tasty_int::detail::TastyInt and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before multiplication.
 */
/// @{
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator*=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = detail::prepare_operand(lhs);

    lhs_operand *= detail::prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
TastyInt
operator*(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) * detail::prepare_operand(rhs);
}
/// @}


/**
 * @brief TastyInt output operator.
 *
 * @details Output is formatted as follows:
 *
 *     [sign][prefix][digits]
 *
 * where
 *
 *     sign   := - if tasty_int is negative, + if tasty_int is nonnegative and
 *               output has been modified with std::showpos, otherwise the empty
 *               string
 *     prefix := 0x or 0 if output has been modified with std::hex or std::oct
 *               respectively, otherwise the empty string
 *     digits := the string representation of the numerical portion of
 *               tasty_int
 *
 *aram[in,out] output the output stream
 *aram[in]     tasty_int an arbitrary-precision integer
 * @return a reference to output
 */
inline std::ostream &
operator<<(std::ostream   &output,
           const TastyInt &tasty_int)
{
    return output << detail::prepare_operand(tasty_int);
}

} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_IPP
