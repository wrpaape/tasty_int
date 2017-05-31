// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"              // TastyInt interface
#include "tasty_int/detail/from_arithmetic.hpp" // from_arithmetic
#include "tasty_int/detail/to_arithmetic.hpp"   // to_arithmetic
#include <limits>                               // std::numeric_limits
#include <type_traits>                          // std::is_arithmetic


// CONSTRUCTORS
// =============================================================================
template<typename ArithmeticType>
inline
TastyInt::TastyInt(ArithmeticType value)
{
    static_assert(std::is_arithmetic<ArithmeticType>::value,
                  "'ArithmeticType' must be an integral or floating-point "
                  "type");

    from_arithmetic(value);
}



// Inline Implementation
// =============================================================================
template<typename ArithmeticType>
inline ArithmeticType
TastyInt::to_number() const
{
    static_assert(std::is_arithmetic<ArithmeticType>::value,
                  "'ArithmeticType' must be an integral or floating-point "
                  "type");

    return to_arithmetic<ArithmeticType>();
}
