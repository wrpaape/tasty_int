#ifndef TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface
#include <type_traits>             // std::[[true|false]_type]


// retrieve a digit_type from 
// -----------------------------------------------------------------------------
template <typename UnsignedIntegralType> // mask 'digit_bit' bits from value
static inline UnsignedIntegralType
TastyInt::mask_value(const UnsignedIntegralType value)
                     std::true_type needs_mask)
{
    return value & static_cast<UnsignedIntegralType>(digit_type_max);
}

template <typename UnsignedIntegralType>
static inline UnsignedIntegralType
TastyInt::mask_value(const UnsignedIntegralType value,
                     std::false_type needs_mask) // don't need mask
{
    return value;
}


// EXTERNAL API
// =============================================================================
template <typename UnsignedIntegralType>
static inline TastyInt::digit_type
TastyInt::get_digit(const UnsignedIntegralType value)
{
    return static_cast<digit_type>(
        mask_value(value,
                   exceeds_digit<UnsignedIntegralType>())
    );
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP
