#ifndef TASTY_INT_TEST_DETAIL_TESTING_TYPES_HPP
#define TASTY_INT_TEST_DETAIL_TESTING_TYPES_HPP

#include <tuple>
#include <type_traits>

#include "gtest/gtest.h"


namespace tasty_int_test {
namespace detail {

/**
 * @defgroup TestingTypesPredicates ::testing::Types Predicates
 *
 * The following predicates test whether or not a candidate is a template
 * specialization of ::testing::Types.
 */
/// @{
template<typename>
struct IsTestingTypes : public std::false_type
{}; // struct IsTestingTypes

template<typename ...Types>
struct IsTestingTypes<::testing::Types<Types...>> : public std::true_type
{}; // struct IsTestingTypes

template<typename TestingTypes>
constexpr bool is_testing_types = IsTestingTypes<TestingTypes>::value;
/// @}

/**
 * @brief Converts a std::tuple specialization to a ::testing::Types
 *     specialization.
 *
 * @return a ::testing::Types specialization
 */
template<typename ...Types>
constexpr auto
testing_types_from_tuple(std::tuple<Types...>)
{
    return ::testing::Types<Types...>{};
}

/**
 * @brief Converts a ::testing::Types specialization to a std::tuple 
 *     specialization.
 *
 * @return a std::tuple specialization
 */
template<typename ...Types>
constexpr auto
tuple_from_testing_types(::testing::Types<Types...>)
{
    return std::tuple<Types...>{};
}

} // namespace detail
} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_DETAIL_TESTING_TYPES_HPP
