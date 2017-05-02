// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface
#include <type_traits>             // std::[[true|false]_type]





// TastyInt(ArithmeticType value)
// -----------------------------------------------------------------------------
template <typename UnsignedIntegralType,
          std::bool_constant ExceedsDigitType,
          std::bool_constant NeedMask>
inline void
TastyInt::digits_from_unsigned_integral(const UnsignedIntegralType value)
{

}

template <typename UnsignedIntegralType, std::false_type>
inline void
TastyInt::from_integral(UnsignedIntegralType value)
{
    sign = (value > 0);

    digits_from_unsigned_integral<
        sizeof(UnsignedIntegralType) > sizeof(digit_type),
        sizeof(acc_type) != (sizeof(digit_type) * 2)
    >(value);
}

template <typename SignedIntegralType, std::true_type>
inline void
TastyInt::from_integral(SignedIntegralType value)
{
    if (value < 0) {
        value = -value;
        sign  = -1;

    } else {
        sign = (value > 0);
    }

    digits_from_unsigned_integral<
        sizeof(SignedIntegralType) > sizeof(digit_type),
        sizeof(acc_type) != (sizeof(digit_type) * 2)
    >(
        static_cast<std::make_unsigned<SignedIntegralType>::type>(value)
    );
}


// EXTERNAL API
// =============================================================================
template <typename IntegralType, std::true_type>
inline void
TastyInt::from_number(IntegralType value)
{
    from_integral<std::is_signed<IntegralType>>(value);
}

template <typename FloatingPointType, std::false_type>
inline void
TastyInt::from_number(FloatingPointType value)
{
    from_integral<static_cast<signed_acc_type>>(value);
}
