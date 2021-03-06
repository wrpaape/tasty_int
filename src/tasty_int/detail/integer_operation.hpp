#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_OPERATION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_OPERATION_HPP

#include <cassert>
#include <cmath>

#include <type_traits>
#include <utility>

#include "tasty_int/concepts.hpp"
#include "tasty_int/detail/integer.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/absolute_value_from_arithmetic.hpp"


namespace tasty_int {
namespace detail {

/**
 * This concept contrains to primitive types that are signed.
 */
template<typename T>
concept SignedArithmetic = std::is_signed_v<T>
                        || std::is_floating_point_v<T>;

/**
 * This concept contrains to primitive types that are interpretted as unsigned
 * (i.e. operable with digits).
 */
template<typename T>
concept ArithmeticValue = std::is_unsigned_v<T>
                       || std::is_floating_point_v<T>;

/**
 * This concept constrains to all types that are operable with digits.
 */
template<typename T>
concept Value = ArithmeticValue<T>
             || std::is_same_v<T, std::vector<digit_type>>;

/**
 * This concept constrains to all types that are operable with
 * tasty_int::detail::Integer.
 */
template<typename T>
concept IntegerOperand = Arithmetic<T>
                      || std::is_same_v<T, Integer>;


/**
 * @brief Check if two signs agree.
 *
 * @param[in] sign1 a sign
 * @param[in] sign2 another sign
 * @return true unless one operand is Sign::POSITIVE and the other
 *     Sign::NEGATIVE
 */
inline bool
signs_agree(Sign sign1,
            Sign sign2)
{
    int sign_diff = std::abs(sign1 - sign2);
    return (sign_diff <= 1);
}


/**
 * @brief Produces the larger of two agreeing signs.
 *
 * @param[in] sign1 a sign
 * @param[in] sign2 another sign
 * @return the nonzero sign if one is present, otherwise Sign::ZERO
 *
 * @pre `signs_agree(sign1, sign2)`
 */
inline Sign
larger_of_agreeing_signs(Sign sign1,
                         Sign sign2)
{
    assert(signs_agree(sign1, sign2));

    return static_cast<Sign>(sign1 | sign2);
}


/**
 * @defgroup SignFromIntegerOperandOverloads sign_from_integer_operand Overloads
 *
 * These functions return the sign of the supplied @p operand.
 *
 * @param[in] operand a tasty_int::detail::Integer-operable operand
 * @return the sign of @p operand.
 */
/// @{
inline Sign
sign_from_integer_operand(const Integer &operand)
{
    return operand.sign;
}

inline Sign
sign_from_integer_operand(std::uintmax_t operand)
{
    return sign_from_unsigned_arithmetic(operand);
}

template<SignedArithmetic SignedArithmeticValueType>
Sign
sign_from_integer_operand(SignedArithmeticValueType operand)
{
    return sign_from_signed_arithmetic(operand);
}
/// @}


/**
 * @defgroup ValueFromIntegerOperandOverloads value_from_integer_operand Overloads
 *
 * These functions return the nonnegative value of the supplied @p operand.
 *
 * @param[in] operand a tasty_int::detail::Integer-operable operand
 * @return the nonnegative value of @p operand.
 */
/// @{
inline const std::vector<digit_type> &
value_from_integer_operand(const Integer &operand)
{
    return operand.digits;
}

template<tasty_int::Arithmetic ArithmeticType>
auto
value_from_integer_operand(ArithmeticType operand)
{
    return absolute_value_from_arithmetic(operand);
}
/// @}


/**
 * @brief Produces the sign and value of the supplied @p operand.
 *
 * @param[in] operand a tasty_int::detail::Integer-operable operand
 * @return a std::pair consisting of the sign of the @p operand in the `first`
 *     field and the value of @p operand in the `second` field.
 */
template<Arithmetic ArithmeticType>
auto
sign_and_value_from_arithmetic(ArithmeticType arithmetic)
{
    return std::make_pair(sign_from_integer_operand(arithmetic),
                          value_from_integer_operand(arithmetic));
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_OPERATION_HPP
