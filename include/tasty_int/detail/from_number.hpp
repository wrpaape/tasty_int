#ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_NUMBER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FROM_NUMBER_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"        // TastyInt interface
#include "tasty_int/detail/get_digit.hpp" // get_digit
#include <type_traits>                    // std::[[true|false]_type]
#include <limits>                         // std::numeric_limits





// initialize 'digits'
// -----------------------------------------------------------------------------
template <typename UnsignedIntegralType> // value may be >= digit_type_max
inline void
TastyInt::digits_from_unsigned_integral(const UnsignedIntegralType value,
                                        std::true_type overflow)
{
    digits.reserve(2);
    digits.emplace_back(get_digit(value));

    if (value > digit_type_max)
        digits.emplace_back(get_digit(value >> digit_bit));
}

template <typename UnsignedIntegralType> // value <= digit_type_max
inline void
TastyInt::digits_from_unsigned_integral(const UnsignedIntegralType value,
                                        std::false_type overflow)
{
    digits { value };
}


// initialize 'sign'
// -----------------------------------------------------------------------------
template <typename UnsignedIntegralType> // value is unsigned integral
inline void
TastyInt::from_integral(UnsignedIntegralType value,
                        std::false_type is_signed)
{
    sign = (value > 0);

    digits_from_unsigned_integral<
        std::numeric_limits<UnsignedIntegralType>::max() > digit_type_max
    >(value);
}

template <typename SignedIntegralType> // value is signed integral
inline void
TastyInt::from_integral(SignedIntegralType value,
                        std::true_type is_signed)
{
    if (value < 0) {
        value = -value;
        sign  = -1;

    } else {
        sign = (value > 0);
    }

    digits_from_unsigned_integral<
        std::numeric_limits<SignedIntegralType>::max() > digit_type_max
    >(
        static_cast<
            std::make_unsigned<SignedIntegralType>::type
        >(value)
    );
}


// EXTERNAL API
// =============================================================================
template <typename IntegralType,
          std::true_type> // value is integral
inline void
TastyInt::from_number(IntegralType value)
{
    from_integral<
        std::is_signed<IntegralType>
    >(value);

    from_integral(value, std::is_signed<IntegralType>::value)
}

template <typename FloatingPointType,
          std::false_type>
inline void
TastyInt::from_number(FloatingPointType value,
                      std::false_type) // value is floating-point
{
    from_integral(static_cast<signed_acc_type>(value),
                  bool_constant<true>());
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_NUMBER_HPP
