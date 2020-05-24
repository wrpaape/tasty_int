#ifndef TASTY_INT_TASTY_INT_HPP
#define TASTY_INT_TASTY_INT_HPP

#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include "tasty_int/detail/integer.hpp"
#include "tasty_int/detail/flip_sign.hpp"
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

namespace detail {

const detail::Integer &
prepare_operand(const TastyInt &operand);

detail::Integer &
prepare_operand(TastyInt &operand);

} // namespace detail


/**
 * @defgroup TastyIntConcepts TastyInt Concepts
 *
 * The following define concepts for primitive types that are operable with
 * tasty_int::TastyInt.
 *
 * @todo TODO: replace with std:: <concepts> when avaialable
 */
/// @{
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept SignedIntegral = std::is_integral_v<T>
                      && std::is_signed_v<T>;

template<typename T>
concept UnsignedIntegral = std::is_integral_v<T>
                        && std::is_unsigned_v<T>;

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

        copy.integer.sign = detail::flip_sign(copy.integer.sign);

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
    friend const detail::Integer &
    detail::prepare_operand(const TastyInt &operand);
    friend detail::Integer &
    detail::prepare_operand(TastyInt &operand);

    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator+(const LhsType &lhs,
              const RhsType &rhs);
    template<TastyIntOperand LhsType, TastyIntOperand RhsType>
        requires TastyIntOperation<LhsType, RhsType>
    friend TastyInt
    operator-(const LhsType &lhs,
              const RhsType &rhs);

    TastyInt(detail::Integer&& result)
        : integer(std::move(result))
    {}

    detail::Integer integer;
}; // class TastyInt

} // namespace tasty_int


#include "tasty_int/tasty_int.ipp"

#endif // ifndef TASTY_INT_TASTY_INT_HPP
