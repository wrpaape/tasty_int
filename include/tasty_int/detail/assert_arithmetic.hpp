#ifndef TASTY_INT_TASTY_INT_DETAIL_ASSERT_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_ASSERT_ARITHMETIC_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <type_traits> // std::is_arithmetic


// EXTERNAL API
// =============================================================================
namespace tasty_int_detail {

template <typename ArithmeticType>
inline void
assert_arithmetic()
{
    static_assert(std::is_arithmetic<ArithmeticType>::value,
                  "'ArithmeticType' must be an integral or floating-point "
                  "type");
}

} // namespace tasty_int_detail


#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_ASSERT_ARITHMETIC_HPP
