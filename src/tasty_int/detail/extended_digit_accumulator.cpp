#include "tasty_int/detail/extended_digit_accumulator.hpp"

#include <cassert>

#include <limits>


namespace tasty_int {
namespace detail {

bool
operator==(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs)
{
    return std::operator==(lhs, rhs);
}

bool
operator!=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs)
{
    return !(lhs == rhs);
}

bool
operator<(ExtendedDigitAccumulator lhs,
          ExtendedDigitAccumulator rhs)
{
    if (lhs.back() != rhs.back())
    {
        return lhs.back() < rhs.back();
    }

    return lhs.front() < rhs.front();
}

bool
operator>(ExtendedDigitAccumulator lhs,
          ExtendedDigitAccumulator rhs)
{
    return rhs < lhs;
}

bool
operator<=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs)
{
    return !(lhs > rhs);
}

bool
operator>=(ExtendedDigitAccumulator lhs,
           ExtendedDigitAccumulator rhs)
{
    return !(lhs < rhs);
}


ExtendedDigitAccumulator
operator*(IntegralDigitsView lhs,
          digit_type         rhs)
{
    /// @todo: TODO: consider using intrinsic 128 bit multiplication
    digit_accumulator_type lhs_low  = lhs.low_digit();
    digit_accumulator_type lhs_high = lhs.high_digit();

    auto low_product  = lhs_low * rhs;
    auto carry        = low_product >> DIGIT_TYPE_BITS;
    auto high_product = (lhs_high * rhs) + carry;

    auto low_accumulator = (low_product   & DIGIT_TYPE_MAX)
                         | (high_product << DIGIT_TYPE_BITS);
    auto high_accumulator = high_product >> DIGIT_TYPE_BITS;

    return ExtendedDigitAccumulator{{
        low_accumulator, high_accumulator
    }};
}

ExtendedDigitAccumulator
operator*(digit_type         lhs,
          IntegralDigitsView rhs)
{
    return rhs * lhs;
}


ExtendedDigitAccumulator &
operator-=(ExtendedDigitAccumulator &lhs,
           ExtendedDigitAccumulator  rhs)
{
    assert(lhs >= rhs);

    digit_accumulator_type accumulator = ~lhs.front() + rhs.front();
    digit_accumulator_type carry       = (rhs.front() > accumulator);
    lhs.front() = ~accumulator;
    accumulator = ~lhs.back() + rhs.back() + carry;
    lhs.back()  = ~accumulator;

    return lhs;
}

ExtendedDigitAccumulator &
operator-=(ExtendedDigitAccumulator &lhs,
           IntegralDigitsView        rhs)
{
    return lhs -= ExtendedDigitAccumulator{{ rhs.value() }};
}


ExtendedDigitAccumulator &
operator>>=(ExtendedDigitAccumulator &lhs,
            unsigned int              bit_offset)
{
    assert(bit_offset < DIGIT_TYPE_BITS);

    auto overflow_mask  =  (digit_accumulator_type(1) << bit_offset) - 1;
    auto overflow       = lhs.back() & overflow_mask;
    auto overflow_shift = std::numeric_limits<digit_accumulator_type>::digits
                        - bit_offset;

    lhs.front() >>= bit_offset;
    lhs.front()  |= (overflow << overflow_shift);
    lhs.back()  >>= bit_offset;

    return lhs;
}

} // namespace detail
} // namespace tasty_int
