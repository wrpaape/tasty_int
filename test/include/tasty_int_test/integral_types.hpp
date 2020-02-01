#ifndef TASTY_INT_TASTY_INT_TEST_INTEGRAL_TYPES_HPP
#define TASTY_INT_TASTY_INT_TEST_INTEGRAL_TYPES_HPP

#include <type_traits>

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/detail/filter_types.hpp"


namespace tasty_int_test {

using IntegralTypes = detail::FilterTypes<ArithmeticTypes, std::is_integral>;

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_INTEGRAL_TYPES_HPP
