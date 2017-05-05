#ifndef TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface
#include <type_traits>             // std::[[true|false]_type]
#include <limits>                  // std::numeric_limits


// retrieve a digit_type from 
// -----------------------------------------------------------------------------
template <typename UnsignedIntegralType,
          std::false_type> // don't need to mask out digit from value
static inline UnsignedIntegralType
TastyInt::mask_digit(const UnsignedIntegralType value)
{
    return value;
}

template <typename UnsignedIntegralType,
          std::true_type> // retrieve the bottom 'digit_bit' bits from value
static inline UnsignedIntegralType
TastyInt::mask_digit(const UnsignedIntegralType value)
{
    return value & static_cast<UnsignedIntegralType>(digit_type_max);
}


// EXTERNAL API
// =============================================================================
template <typename UnsignedIntegralType>
static inline TastyInt::digit_type
TastyInt::get_digit(const UnsignedIntegralType value)
{
    return static_cast<digit_type>(
        mask_digit<
            std::numeric_limits<UnsignedIntegralType>::max() > digit_type_max
        >(value)
    );
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_GET_DIGIT_HPP
