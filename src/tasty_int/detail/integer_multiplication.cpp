#include "tasty_int/detail/integer_multiplication.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/integer_operation.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"
#include "tasty_int/detail/intmax_t_from_uintmax_t.hpp"
#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<IntegerOperand MultiplierType>
Integer &
multiply_in_place(const MultiplierType &multiplier,
                  Integer              &multiplicand)
{
    multiplicand.sign   *= sign_from_integer_operand(multiplier);
    multiplicand.digits *= value_from_integer_operand(multiplier);

    return multiplicand;
}

template<IntegerOperand MultiplierType>
Integer
multiply(const Integer        &multiplicand,
         const MultiplierType &multiplier)
{
    Integer result;
    result.sign   = multiplicand.sign * sign_from_integer_operand(multiplier);
    result.digits = multiplicand.digits 
                  * value_from_integer_operand(multiplier);

    return result;
}

} // namespace


Integer &
operator*=(Integer       &lhs,
           const Integer &rhs)
{
    return multiply_in_place(rhs, lhs);
}

Integer &
operator*=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    return multiply_in_place(rhs, lhs);
}

std::uintmax_t &
operator*=(std::uintmax_t &lhs,
           const Integer  &rhs)
{
    return lhs *= conversions::unsigned_integral_from_integer(rhs);
}

Integer &
operator*=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return multiply_in_place(rhs, lhs);
}

std::intmax_t &
operator*=(std::intmax_t &lhs,
           const Integer &rhs)
{
    auto unsigned_lhs = static_cast<std::uintmax_t>(lhs);

    unsigned_lhs *= rhs;

    lhs = intmax_t_from_uintmax_t(unsigned_lhs);

    return lhs;
}

Integer &
operator*=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return multiply_in_place(rhs, lhs);
}

long double &
operator*=(long double   &lhs,
           const Integer &rhs)
{
    lhs = std::trunc(lhs);

    return lhs *= conversions::floating_point_from_integer(rhs);
}


Integer
operator*(const Integer &lhs,
          const Integer &rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return rhs * lhs;
}

Integer
operator*(const Integer &lhs,
          std::intmax_t  rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(std::intmax_t  lhs,
          const Integer &rhs)
{
    return rhs * lhs;
}

Integer
operator*(const Integer &lhs,
          long double    rhs)
{
    assert(std::isfinite(rhs));

    return multiply(lhs, rhs);
}

Integer
operator*(long double    lhs,
          const Integer &rhs)
{
    return rhs * lhs;
}

} // namespace detail
} // namespace tasty_int
