#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_GET_DIGIT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_GET_DIGIT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface


// EXTERNAL API
// =============================================================================
template <typename T>
inline TastyInt::enable_if_exceeds_digit<T, TastyInt::digit_type>
TastyInt::get_digit(const T value)
{
    return static_cast<digit_type>(
        value & static_cast<T>(DIGIT_TYPE_MAX) // mask 'digit_bit' bits
    );
}

template <typename T>
inline TastyInt::enable_if_within_digit<T, TastyInt::digit_type>
TastyInt::get_digit(const T value)
{
    return static_cast<digit_type>(value);
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_GET_DIGIT_HPP
