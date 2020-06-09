#ifndef TASTY_INT_TASTY_INT_CONCEPTS_HPP
#define TASTY_INT_TASTY_INT_CONCEPTS_HPP

#include <type_traits>


namespace tasty_int {

/**
 * @defgroup TastyIntConcepts TastyInt Concepts
 *
 * The following define concepts for dispatching primitive types.
 *
 * @todo TODO: replace with std:: <concepts> when avaialable
 */
/// @{
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept SignedIntegral = std::is_integral_v<T>
                      && std::is_signed_v<T>;

template<typename T>
concept UnsignedIntegral = std::is_integral_v<T>
                        && std::is_unsigned_v<T>;
/// @}

} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_CONCEPTS_HPP
