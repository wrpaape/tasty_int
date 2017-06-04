// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"              // TastyInt interface
#include "tasty_int/detail/from_arithmetic.hpp" // from_arithmetic
#include "tasty_int/detail/to_arithmetic.hpp"   // to_arithmetic
#include <type_traits>                          // std::is_arithmetic
#include <stdexcept>                            // std::invalid_argument
#include <cstring>                              // std::strlen


// CONSTRUCTORS
// =============================================================================
inline
TastyInt::TastyInt(const std::string &string,
                   const unsigned int base)
{
    TastyInt(string.data(),
             string.size(),
             base);
}


inline
TastyInt::TastyInt(const char *string,
                   const unsigned int base)
{
    TastyInt(string,
             std::strlen(string),
             base);
}

template<std::size_t size>
inline
TastyInt::TastyInt(const char (&string)[size],
                   const unsigned int base)
{
    TastyInt(string,
             size - (size > 0),
             base);
}

inline
TastyInt::TastyInt(const char *string,
                   const std::size_t length,
                   const unsigned int base)
{
    const unsigned char *token_values;

    if (base <= 36) {
        token_values = &base_36_token_values[0];
    else if (base <= max_base)
        token_values = &base_64_token_values[0];
    else
        throw std::invalid_argument(
            "TastyInt::TastyInt(string, base) -- "
            "input 'base' exceeds TastyInt::max_base (64)"
        );

    // const unsigned char *const
    // tokens = reinterpret_cast<const unsigned char *>(string.data());

    // from_string()
}


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
