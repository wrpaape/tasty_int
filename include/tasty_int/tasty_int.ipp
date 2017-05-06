// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"                // TastyInt interface
#include "tasty_int/detail/assert_arithmetic.hpp" // tasty_int_detail::assert_arithmetic
#include "tasty_int/detail/get_digit.hpp"         // get_digit
#include "tasty_int/detail/from_number.hpp"       // from_number
#include <limits>                                 // std::numeric_limits
#include <type_traits>                            // std::is_integral


// CONSTANTS
// =============================================================================
static const unsigned int
TastyInt::digit_bit = std::numeric_limits<TastyInt::acc_type>::digits / 2;
static const TastyInt::acc_type
TastyInt::digit_type_max = (1 << TastyInt::digit_bit) - 1;


// CONSTRUCTORS
// =============================================================================
template<typename ArithmeticType>
inline
TastyInt::TastyInt(ArithmeticType value)
{
    tasty_int_detail::assert_arithmetic<ArithmeticType>();

    from_number<
        std::is_integral<ArithmeticType>::value
    >(value);
}



// Inline Implementation
// =============================================================================
template<typename ArithmeticType>
inline ArithmeticType
to_number() const;
{
    tasty_int_detail::assert_arithmetic<ArithmeticType>();

    to_number<
        std::is_integral<ArithmeticType>::value
    >(value);
}
