#ifndef TASTY_INT_TASTY_INT_DETAIL_CONCEPTS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONCEPTS_HPP

#include <type_traits>


namespace tasty_int {
namespace detail {

/**
 * This concept contrains to primitive types that are interpretted as unsigned
 * (i.e. operable with digits).
 */
template<typename T>
concept ArithmeticValue = std::is_unsigned_v<T>
                       || std::is_floating_point_v<T>;

/**
 * This concept contrains to primitive types that are signed.
 */
template<typename T>
concept SignedArithmetic = std::is_signed_v<T>
                        || std::is_floating_point_v<T>;

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONCEPTS_HPP
