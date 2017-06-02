#include "tasty_int/tasty_int.hpp"
#include "token_values.h"
#include <limits>
#include <type_traits>


// Static Constants
// -----------------------------------------------------------------------------
unsigned int TastyInt::global_default_base = 10;
// TastyInt::digit_type_max((1ULL << (sizeof(TastyInt::acc_type) / 2)) - 1ULL);
