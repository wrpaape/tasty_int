#ifndef TASTY_INT_TASTY_INT_HPP
#define TASTY_INT_TASTY_INT_HPP

#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

/// @todo: TODO: GenerateExportHeader
#include "tasty_int/concepts.hpp"
#include "tasty_int/detail/integer.hpp"
#include "tasty_int/detail/integer_comparison.hpp"
#include "tasty_int/detail/integer_addition.hpp"
#include "tasty_int/detail/integer_subtraction.hpp"
#include "tasty_int/detail/integer_multiplication.hpp"
#include "tasty_int/detail/integer_division.hpp"
#include "tasty_int/detail/integer_input.hpp"
#include "tasty_int/detail/integer_output.hpp"
#include "tasty_int/detail/conversions/integer_from_floating_point.hpp"
#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_unsigned_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"
#include "tasty_int/detail/conversions/signed_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/string_from_integer.hpp"


namespace tasty_int {

class TastyInt;

/**
 * @defgroup TastyIntOperationConcepts TastyInt Operation Concepts
 *
 * The following define concepts for types that are operable with
 * tasty_int::TastyInt.
 */
/// @{
template<typename T>
concept TastyIntOperand = Arithmetic<T>
                       || std::is_same_v<T, TastyInt>;

template<typename LhsType,
         typename RhsType>
concept TastyIntOperation =
    (std::is_same_v<LhsType, TastyInt> && TastyIntOperand<RhsType>)
 || (std::is_same_v<RhsType, TastyInt> && TastyIntOperand<LhsType>);
/// @}


/**
 * The result of an immutable division operation involving a
 * tasty_int::TastyInt (tasty_int::div).
 */
/// @ingroup TastyIntDivisionOperators
template<TastyIntOperand DividendType>
struct TastyIntDivisionResult
{
    DividendType quotient;  ///< the division quotient
    DividendType remainder; ///< the division remainder
}; // struct TastyIntDivisionResult


/**
 * @defgroup TastyIntPrepareOperand tasty_int::prepare_operand
 *
 * Distills tasty_int::TastyIntOperands into types that are operable with
 * tasty_int::detail::Integer.  These are called implicitly on operands
 * before each arithmetic operation.
 */
/// @{
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


/**
 * This class represents an arbitary-precision signed integer.  A
 * tasty_int::TastyInt instance may be intialized from any primitive arithmetic
 * type as well as operate with them and other TastyInt instances through the
 * expected operator overloads.  Its value may also be initialized from or
 * be converted to an ASCII string of numerical digits.
 */
class TastyInt
{
public:
    /**
     * @defgroup TastyIntConstructors TastyInt Constructors
     *
     * @brief Constructor.
     *
     * @details A tasty_int::TastyInt may be constructed with an initial value
     *      from any arithmetic type or with a value denoted by a string of
     *      ASCII tokens.  If no initial value is provided, TastyInt is
     *      default-initialized with a value of zero.
     */
    /// @{
    /**
     * @details Initializes `this` with a value of zero.
     */
    TastyInt()
        : integer({
            .sign   = detail::Sign::ZERO,
            .digits = { 0 }
          })
    {}

    /**
     * @details Initializes `this` from the provided nonnegative floating point
     *      value.  The value stored is truncated toward zero to the effect
     *      that `TastyInt(floating_point) ==
     *      TastyInt(std::trunc(floating_point))`.
     *
     * @param[in] floating_point the initial value
     *
     * @pre `std::isfinite(floating_point) && (floating_point >= 0.0)`
     */
    template<FloatingPoint FloatingPointType>
    TastyInt(FloatingPointType floating_point)
        : integer(
              detail::conversions::integer_from_floating_point(
                  floating_point
              )
          )
    {}

    /**
     * @details Initializes `this` from the provided signed integral value.
     *
     * @param[in] signed_integral the initial value
     */
    template<SignedIntegral SignedIntegralType>
    TastyInt(SignedIntegralType signed_integral)
        : integer(
              detail::conversions::integer_from_signed_integral(
                  signed_integral
              )
          )
    {}

    /**
     * @details Initializes `this` from the provided unsigned integral value.
     *
     * @param[in] unsigned_integral the initial value
     */
    template<UnsignedIntegral UnsignedIntegralType>
    TastyInt(UnsignedIntegralType unsigned_integral)
        : integer(
              detail::conversions::integer_from_unsigned_integral(
                  unsigned_integral
              )
          )
    {}

    /**
     * @details Leading whitespace is ignored.  If no @p base is provided or @p
     *     base is zero, the correct base is determined from the leading
     *     non-sign characters of @p tokens.  If @p tokens has a prefix
     *     associated with @p base, then it will be ignored (i.e.  `base=16
     *     tokens=0xdead` is interpretted as `base=16 tokens=dead`).  If no
     *     base-specific prefix is found, @p tokens is interpretted in decimal
     *     form (base 10).
     *
     * @param[in] tokens a string of ASCII tokens representing sign, numerical
     *     digits, and an optional prefix.
     * @param[in] base   the numeric base/radix in which @p tokens is
     *     interpretted
     *
     * @throw std::invalid_argument if @p tokens contains no digits
     * @throw std::invalid_argument if @p base is not either a supported
     *     numeric base or zero.
     * @throw std::invalid_argument if input contains an out-of-bounds token for
     *     the provided (or interpretted) base
     */
    TastyInt(std::string_view tokens,
             unsigned int     base = 0)
        : integer(
              detail::conversions::integer_from_string(
                  tokens, base
              )
          )
    {}
    /// @}

    virtual ~TastyInt() = default;


    /**
     * @defgroup TastyIntToNumber TastyInt::to_number()
     *
     * @brief Retrieve the numerical value of `this`.
     *
     * @return the numerical value of `this`
     */
    /// @{
    /**
     * @details The result is truncated towards zero.  If the result is too
     *     big, a hardware overflow trap may occur.  In the case that a trap
     *     does not occur, an appropriately-signed infinity will be returned.
     */
    template<FloatingPoint FloatingPointType>
    FloatingPointType
    to_number() const
    {
        return static_cast<FloatingPointType>(
            detail::conversions::floating_point_from_integer(integer)
        );
    }

    /**
     * @details The result is produced from the sign and least-significant @p
     *     SignedIntegralType magnitude bits of `this`.
     */
    template<SignedIntegral SignedIntegralType>
    SignedIntegralType
    to_number() const
    {
        return static_cast<SignedIntegralType>(
            detail::conversions::signed_integral_from_integer(integer)
        );
    }

    /**
     * @details The result is produced from least-significant @p
     *     sizeof(UnsignedIntegralType) magnitude bytes of `this`.  If `this`
     *     is negative, the result value wraps according to standard modulo
     *     wrapping behavior.
     */
    template<UnsignedIntegral UnsignedIntegralType>
    UnsignedIntegralType
    to_number() const
    {
        return static_cast<UnsignedIntegralType>(
            detail::conversions::unsigned_integral_from_integer(integer)
        );
    }
    /// @}

    /**
     * @param[in] base the desired base of the output value.
     *
     * @details Supported bases lie in the inclusive range `[2,64]`.  If no base
     *     is provided, the result is presented in decimal form (base 10).
     *     Lowercase tokens are used for the alphabetical digits `a-z` except in
     *     the case of bases `[37,64]`, where capital letters differ in value
     *     from lowercase. Base-specific prefixes are not prepended to the
     *     result.
     *
     * @throw std::invalid_argument if @p base is unsupported
     */
    std::string
    to_string(unsigned int base = 10) const
    {
        return detail::conversions::string_from_integer(integer, base);
    }


    /**
     * @defgroup TastyIntUnaryOperators TastyInt Unary Operators
     *
     * These operators operate on `this` as if it were an ordinary signed
     * integer.  Note that all but post-increment/decrement return a deep copy
     * of `this`.
     */
    /// @{
    TastyInt
    operator+() const
    {
        return *this;
    }

    TastyInt
    operator-() const
    {
        auto copy = *this;

        copy.integer.sign = -copy.integer.sign;

        return copy;
    }

    TastyInt &
    operator++()
    {
        integer += std::uintmax_t(1);

        return *this;
    }

    TastyInt
    operator++(int)
    {
        auto copy = *this;

        ++*this;

        return copy;
    }

    TastyInt &
    operator--()
    {
        integer -= std::uintmax_t(1);

        return *this;
    }

    TastyInt
    operator--(int)
    {
        auto copy = *this;

        --*this;

        return copy;
    }
    /// @}

private:
    /// @ingroup TastyIntPrepareOperand
    friend const detail::Integer &
    prepare_operand(const TastyInt &operand)
    {
        return operand.integer;
    }

    /// @ingroup TastyIntPrepareOperand
    friend detail::Integer &
    prepare_operand(TastyInt &operand)
    {
        return operand.integer;
    }

    /**
     * @defgroup TastyIntAdditionOperators TastyInt Addition Operators
     *
     * These operators apply addition to tasty_int::TastyInt and the supported
     * arithmetic types.  Note that floating point values are effectively
     * truncated toward zero before addition.
     */
    /// @ingroup TastyIntAdditionOperators
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator+(const LhsType &lhs,
              const RhsType &rhs)
    {
        return prepare_operand(lhs) + prepare_operand(rhs);
    }

    /**
     * @defgroup TastyIntSubtractionOperators TastyInt Subtraction Operators
     *
     * These operators apply subtraction to tasty_int::TastyInt and the
     * supported arithmetic types.  Note that floating point values are
     * effectively truncated toward zero before subtraction.
     */
    /// @ingroup TastyIntSubtractionOperators
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator-(const LhsType &lhs,
              const RhsType &rhs)
    {
        return prepare_operand(lhs) - prepare_operand(rhs);
    }

    /**
     * @defgroup TastyIntMultiplicationOperators TastyInt Multiplication Operators
     *
     * These operators apply multiplication to tasty_int::TastyInt and the
     * supported arithmetic types.  Note that floating point values are
     * effectively truncated toward zero before multiplication.
     */
    /// @ingroup TastyIntMultiplicationOperators
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator*(const LhsType &lhs,
              const RhsType &rhs)
    {
        return prepare_operand(lhs) * prepare_operand(rhs);
    }

    /**
     * @defgroup TastyIntDivisionOperators TastyInt Division Operators
     *
     * These operators apply division to tasty_int::TastyInt and the supported
     * arithmetic types.  Note that floating point values are effectively
     * truncated toward zero before division.
     */
    /// @ingroup TastyIntDivisionOperators
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator/(const LhsType &lhs,
              const RhsType &rhs)
    {
        return prepare_operand(lhs) / prepare_operand(rhs);
    }

    /// @ingroup TastyIntDivisionOperators
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator%(const LhsType &lhs,
              const RhsType &rhs)
    {
        return prepare_operand(lhs) % prepare_operand(rhs);
    }

    /**
     * @brief Computes the quotient and remainder of an integer division.
     *
     * @details The type of the resulting quotient and remainder matches the
     *     type of @p dividend, @p DividendType.
     *
     * @tparam DividendType the type of the dividend
     * @tparam DivisorType  the type of the divisor
     * @param[in] dividend the dividend
     * @param[in] divisor  the divisor
     * @return the quotient and remainder of `dividend / divisor`
     */
    /// @ingroup TastyIntDivisionOperators
    template<TastyIntOperand DividendType, TastyIntOperand DivisorType>
        requires TastyIntOperation<DividendType, DivisorType>
    friend TastyIntDivisionResult<DividendType>
    div(const DividendType &dividend,
        const DivisorType  &divisor);

    /**
     * @brief TastyInt input operator.
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
    friend std::istream &
    operator>>(std::istream &input,
               TastyInt     &tasty_int)
    {
        return input >> prepare_operand(tasty_int);
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
     *     sign   := - if tasty_int is negative, + if tasty_int is nonnegative
     *               and output has been modified with std::showpos, otherwise
     *               the empty string
     *     prefix := 0x or 0 if output has been modified with std::hex or
     *               std::oct respectively, otherwise the empty string
     *     digits := the string representation of the numerical portion of
     *               tasty_int
     *
     * @param[in,out] output the output stream
     * @param[in]     tasty_int an arbitrary-precision integer
     * @return a reference to output
     */
    friend std::ostream &
    operator<<(std::ostream   &output,
               const TastyInt &tasty_int)
    {
        return output << prepare_operand(tasty_int);
    }

    TastyInt(detail::Integer &&result)
        : integer(std::move(result))
    {}

    detail::Integer integer;
}; // class TastyInt


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
    return prepare_operand(lhs) == prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator!=(const LhsType &lhs,
           const RhsType &rhs)
{
    return prepare_operand(lhs) != prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator<(const LhsType &lhs,
          const RhsType &rhs)
{
    return prepare_operand(lhs) < prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator>(const LhsType &lhs,
          const RhsType &rhs)
{
    return prepare_operand(lhs) > prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator<=(const LhsType &lhs,
           const RhsType &rhs)
{
    return prepare_operand(lhs) <= prepare_operand(rhs);
}

template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
bool
operator>=(const LhsType &lhs,
           const RhsType &rhs)
{
    return prepare_operand(lhs) >= prepare_operand(rhs);
}
/// @}


/// @ingroup TastyIntAdditionOperators
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator+=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = prepare_operand(lhs);

    lhs_operand += prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

/// @ingroup TastyIntSubtractionOperators
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator-=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = prepare_operand(lhs);

    lhs_operand -= prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

/// @ingroup TastyIntMultiplicationOperators
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator*=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = prepare_operand(lhs);

    lhs_operand *= prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

/// @ingroup TastyIntDivisionOperators
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator/=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = prepare_operand(lhs);

    lhs_operand /= prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

/// @ingroup TastyIntDivisionOperators
template<TastyIntOperand LhsType, TastyIntOperand RhsType>
    requires TastyIntOperation<LhsType, RhsType>
LhsType &
operator%=(LhsType       &lhs,
           const RhsType &rhs)
{
    auto &&lhs_operand = prepare_operand(lhs);

    lhs_operand %= prepare_operand(rhs);

    if constexpr (Arithmetic<LhsType>)
        lhs = static_cast<LhsType>(lhs_operand);

    return lhs;
}

template<TastyIntOperand DividendType, TastyIntOperand DivisorType>
    requires TastyIntOperation<DividendType, DivisorType>
TastyIntDivisionResult<DividendType>
div(const DividendType &dividend,
    const DivisorType  &divisor)
{
    auto integer_division_result =
        detail::div(prepare_operand(dividend),
                    prepare_operand(divisor));

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

} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_HPP
