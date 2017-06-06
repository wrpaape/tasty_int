#ifndef TASTY_INT_TASTY_INT_DETAIL_THROW_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_THROW_FROM_STRING_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "tasty_int/tasty_int.hpp" // TastyInt interface
#include <stdexcept>               // std::invalid_argument


// EXTERNAL API
// =============================================================================
[[ noreturn ]] inline void
TastyInt::throw_from_string_no_valid_digits()
{
    throw("TastyInt::TastyInt(string) -- no valid digits");
}

[[ noreturn ]] inline void
TastyInt::throw_from_string_invalid_digits()
{
    throw("TastyInt::TastyInt(string) -- invalid digit(s)");
}

[[ noreturn ]] inline void
TastyInt::throw_from_string_max_base_exceeded()
{
    throw std::invalid_argument(
        "TastyInt::TastyInt(string) -- "
        "input 'base' exceeds TastyInt::max_base (64)"
    );
}

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_THROW_FROM_STRING_HPP
