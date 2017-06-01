#ifndef TASTY_INT_TASTY_INT_DETAIL_TO_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TO_ARITHMETIC_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"        // TastyInt interface
#include <type_traits>                    // std::make_unsigned


// process 'digits'
// -----------------------------------------------------------------------------
template <typename T>
inline TastyInt::enable_if_exceeds_digit<T, T> // may return up to 2 digits
TastyInt::digits_to_unsigned_integral() const
{
    T value = static_cast<T>(digits[0]);

    if (digits.size() > 1) {
        const T upper = static_cast<T>(digits[1]);

        value += (upper << digit_bit);
    }

    return value;
}

template <typename T>
inline TastyInt::enable_if_within_digit<T, T> // return lower digit
TastyInt::digits_to_unsigned_integral() const
{
    return static_cast<T>(digits[0]);
}


// process 'sign'
// -----------------------------------------------------------------------------
template <typename T>
inline TastyInt::enable_if_signed<T, T> // return signed integral
TastyInt::to_integral() const
{
    T value = static_cast<T> (
        digits_to_unsigned_integral<typename std::make_unsigned<T>::type>()
    );

    if (sign < 0)
        value = -value;

    return value;
}

template <typename T>
inline TastyInt::enable_if_unsigned<T, T> // return unsigned integral
TastyInt::to_integral() const
{
    return digits_to_unsigned_integral<T>();
}


// EXTERNAL API
// =============================================================================
template <typename T>
inline TastyInt::enable_if_integral<T, T> // return integral
TastyInt::to_arithmetic() const
{
    return to_integral<T>();
}

template <typename T>
inline TastyInt::enable_if_floating_point<T, T> // return floating-point
TastyInt::to_arithmetic() const
{
    static_cast<T>(
        to_integral<signed_acc_type>()
    );
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TO_ARITHMETIC_HPP
