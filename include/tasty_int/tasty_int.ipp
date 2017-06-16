// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp"                // TastyInt interface
#include "tasty_int/detail/throw_from_string.hpp" // throw_from_string_*
#include "tasty_int/detail/from_arithmetic.hpp"   // from_arithmetic
#include "tasty_int/detail/to_arithmetic.hpp"     // to_arithmetic
#include <type_traits>                            // std::is_arithmetic
#include <cstring>                                // std::strlen


// CONSTRUCTORS
// =============================================================================
inline
TastyInt::TastyInt(const std::string &string,
                   const unsigned int base)
{
    TastyInt(string.data(),
             string.length(),
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
    static_assert(size > 0,
                  "TastyInt::TastyInt(const char(&string)[0]) -- "
                  "zero-size character array provided, expected "
                  "c-style ('\0'-terminated) string");

    TastyInt(&string[0],
             size - 1,
             base);
}

inline
TastyInt::TastyInt(const char *string,
                   std::size_t length,
                   const unsigned int base)
{
    const char *token_values;
    int sign;

    if (base <= 36u)
        token_values = &base_36_token_values[0];
    else if (base <= max_base)
        token_values = &base_64_token_values[0];
    else
        throw_from_string_max_base_exceeded();

    if (length == 0)
        throw_from_string_no_valid_digits();

    if (*string == '-') {
        if (--length == 0)
            throw_from_string_no_valid_digits();

        ++string;
        sign = -1;

    } else {
        sign = 1;
    }

    digits_from_string(reinterpret_cast<const unsigned char *>(string),
                       length,
                       base,
                       token_values);

    this->sign = ((digits.size() == 1) && (digits[0] == 0)) ? 0 : sign;
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
