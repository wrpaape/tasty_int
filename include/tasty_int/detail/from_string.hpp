#ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FROM_STRING_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface


[[ noreturn ]] inline void
TastyInt::throw_from_string_no_valid_digits()
{
    throw("TastyInt::TastyInt(string) -- no valid digits");
}


inline void
TastyInt::digits_from_tokens(const unsigned char *begin,
                             const unsigned char *end,
                             const unsigned int base,
                             const unsigned char *token_values)
{
}


// EXTERNAL API
// =============================================================================
inline void
TastyInt::from_string(const unsigned char *string,
                      std::size_t length,
                      const unsigned int base,
                      const unsigned char *token_values)
{
    if (length == 0)
        throw_from_string_no_valid_digits();

    if (*string == '-') {
        if (--length == 0)
            throw_from_string_no_valid_digits();

        sign = -1;
    }
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FROM_STRING_HPP
