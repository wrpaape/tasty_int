// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"          // TastyInt interface
#include "tasty_int/detail/from_number.ipp" // from_number
#include <type_traits>                      // std::[is_arithmetic|is_integral]


// CONSTRUCTORS
// =============================================================================
template<typename ArithmeticType>
inline
TastyInt::TastyInt(ArithmeticType value)
{
    static_assert(std::is_arithmetic<ArithmeticType>::value,
                  "'ArithmeticType' must be an integral or floating-point "
                  "type");

    from_number<std::is_integral<ArithmeticType>::value>(value);
}



// Inline Implementation
// =============================================================================
