#ifndef TASTY_INT_TASTY_INT_IPP
#define TASTY_INT_TASTY_INT_IPP

#include "tasty_int/tasty_int.hpp"

#include "tasty_int/detail/integer_comparison.hpp"
#include "tasty_int/detail/integer_multiplication.hpp"
#include "tasty_int/detail/integer_division.hpp"
#include "tasty_int/detail/integer_input.hpp"
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
 * @defgroup TastyIntDivisionOperators TastyInt Division Operators
 *
 * These operators apply division to tasty_int::detail::TastyInt and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before division.
 */
/// @{
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator/=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = detail::prepare_operand(lhs);

    lhs_operand /= detail::prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
TastyInt
operator/(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) / detail::prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator%=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = detail::prepare_operand(lhs);

    lhs_operand %= detail::prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
TastyInt
operator%(const LhsType &lhs,
          const RhsType &rhs)
{
    return detail::prepare_operand(lhs) % detail::prepare_operand(rhs);
}


/**
 * The result of an immutable division operation involving a
 * tasty_int::TastyInt (tasty_int::div).
 */
template<TastyIntOperand DividendType>
struct TastyIntDivisionResult
{
    DividendType quotient;  ///< the division quotient
    DividendType remainder; ///< the division remainder
}; // struct TastyIntDivisionResult

/**
 * @brief Computes the quotient and remainder of an integer division.
 *
 * @details The type of the resulting quotient and remainder matches the type
 *     of @p dividend, @p DividendType.
 *
 * @tparam DividendType the type of the dividend
 * @tparam DivisorType  the type of the divisor
 * @param[in] dividend the dividend
 * @param[in] divisor  the divisor
 * @return the quotient and remainder of `dividend / divisor`
 */
template<TastyIntOperand DividendType, TastyIntOperand DivisorType>
    requires TastyIntOperation<DividendType, DivisorType>
TastyIntDivisionResult<DividendType>
div(const DividendType &dividend,
    const DivisorType  &divisor)
{
    auto integer_division_result =
        detail::div(detail::prepare_operand(dividend),
                    detail::prepare_operand(divisor));

    if constexpr (Arithmetic<DividendType>)
        return {
            .quotient  =
                static_cast<DividendType>(integer_division_result.quotient),
            .remainder =
                static_cast<DividendType>(integer_division_result.remainder)
        };
    else
        return {
            .quotient  = std::move(integer_division_result.quotient),
            .remainder = std::move(integer_division_result.remainder)
        };
}
/// @}


/**
 * @brief Integer input operator.
 *
 * @details Input is a string of ASCII tokens interpretted in the base
 *     according to the input basefield flag:
 *
 *     | input basefield flag | interpretted base         |
 *     | -------------------- | --------------------------|
 *     | <none>               | depends on numeric prefix |
 *     | std::dec             | 10                        |
 *     | std::hex             | 16                        |
 *     | std::oct             | 8                         |
 *
 * @details @p input's failbit will be set if a parse error is encountered.
 *
 * @note For standard streams, the basefield flag is set to `dec` on
 *     initialization.
 *
 * @param[in,out] intput  the input stream
 * @param[out]    tasty_int an arbitrary-precision integer
 * @return a reference to @p input
 */
inline std::istream &
operator>>(std::istream &input,
           TastyInt     &tasty_int)
{
    return input >> detail::prepare_operand(tasty_int);
}


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
 * @param[in,out] output the output stream
 * @param[in]     tasty_int an arbitrary-precision integer
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
