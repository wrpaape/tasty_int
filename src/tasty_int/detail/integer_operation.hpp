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
 */
inline bool
signs_agree(Sign sign1,
            Sign sign2)
{
    int sign_diff = std::abs(sign1 - sign2);
    return (sign_diff <= 1);
}

/// @todo: TODO
inline Sign
larger_of_agreeing_signs(Sign sign1,
                         Sign sign2)
{
    assert(signs_agree(sign1, sign2));

    return static_cast<Sign>(sign1 | sign2);
}

/// @todo: TODO
inline Sign
sign_from_integer_operand(const Integer &operand)
{
    return operand.sign;
}

/// @todo: TODO
inline Sign
sign_from_integer_operand(std::uintmax_t operand)
{
    return sign_from_unsigned_arithmetic(operand);
}

/// @todo: TODO
template<SignedArithmetic SignedArithmeticValueType>
Sign
sign_from_integer_operand(SignedArithmeticValueType operand)
{
    return sign_from_signed_arithmetic(operand);
}

/// @todo: TODO
inline const std::vector<digit_type> &
value_from_integer_operand(const Integer &operand)
{
    return operand.digits;
}

/// @todo: TODO
inline std::uintmax_t
value_from_integer_operand(std::uintmax_t operand)
{
    return operand;
}

/// @todo: TODO
inline std::uintmax_t
value_from_integer_operand(std::intmax_t operand)
{
    return static_cast<std::uintmax_t>(std::abs(operand));
}

/// @todo: TODO
inline long double
value_from_integer_operand(long double operand)
{
    return std::abs(operand);
}

/// @todo: TODO
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
