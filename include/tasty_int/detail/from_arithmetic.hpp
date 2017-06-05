#ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FROM_ARITHMETIC_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"        // TastyInt interface
#include "tasty_int/detail/get_digit.hpp" // get_digit
#include <type_traits>                    // std::make_unsigned



// initialize 'digits'
// -----------------------------------------------------------------------------
template <typename T>
inline TastyInt::enable_if_exceeds_digit<T> // value may be > digit_type_max
TastyInt::digits_from_unsigned_integral(const T value)
{
    digits.reserve(2);
    digits.emplace_back(get_digit(value));

    if (value > digit_type_max)
        digits.emplace_back(get_digit(value >> digit_bit));
}

template <typename T>
inline TastyInt::enable_if_within_digit<T> // value <= digit_type_max
TastyInt::digits_from_unsigned_integral(const T value)
{
    digits.emplace_back(value);
}


// initialize 'sign'
// -----------------------------------------------------------------------------
template <typename T>
inline TastyInt::enable_if_signed<T> // value is signed integral
TastyInt::from_integral(T value)
{
    if (value < 0) {
        value = -value;
        sign  = -1;

    } else {
        sign = (value > 0);
    }

    digits_from_unsigned_integral(
        static_cast<typename std::make_unsigned<T>::type>(value)
    );
}

template <typename T>
inline TastyInt::enable_if_unsigned<T> // value is unsigned integral
TastyInt::from_integral(T value)
{
    sign = (value > 0);

    digits_from_unsigned_integral(value);
}


// EXTERNAL API
// =============================================================================
template <typename T>
inline TastyInt::enable_if_integral<T> // value is integral
TastyInt::from_arithmetic(T value)
{
    from_integral(value);
}

template <typename T>
inline TastyInt::enable_if_floating_point<T> // value is floating-point
TastyInt::from_arithmetic(T value)
{
    from_integral(static_cast<signed_acc_type>(value));
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_ARITHMETIC_HPP
