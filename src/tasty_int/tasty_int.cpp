#include "tasty_int/tasty_int.hpp"
#include <limits>
#include <type_traits>


// Static Constants
// -----------------------------------------------------------------------------
const TastyInt::acc_type
TastyInt::digit_type_max((1ULL << (sizeof(TastyInt::acc_type) / 2)) - 1ULL);
