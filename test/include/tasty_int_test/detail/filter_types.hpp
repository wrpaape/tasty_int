#ifndef TASTY_INT_TEST_DETAIL_FILTER_TYPES_HPP
#define TASTY_INT_TEST_DETAIL_FILTER_TYPES_HPP

#include <tuple>
#include <type_traits>
#include <utility>

#include "tasty_int_test/detail/testing_types.hpp"


namespace tasty_int_test {
namespace detail {
namespace filter_types {

template<template <typename> typename Filter>
struct HasFilter : public std::is_convertible<bool, decltype(Filter<void>::value)>
{}; // struct HasFilter

template<template <typename> typename Filter>
constexpr bool is_filter = HasFilter<Filter>::value;

template<template<typename> typename Filter, typename ...NextType>
constexpr auto
collect_types(std::tuple<NextType...> rem_types)
{
    return std::apply([](NextType...)
    {
        return tuple_cat(std::conditional_t<
            Filter<NextType>::value,
            std::tuple<NextType>,
            std::tuple<>
        >()...);
    }, rem_types);
}

template<template<typename> typename Filter, typename ...Types>
constexpr auto
extract_types(::testing::Types<Types...>)
{
	return testing_types_from_tuple(
        collect_types<Filter>(std::tuple<Types...>())
    );
}

} // namespace filter_types


/**
 * @brief Defines a new type `::testing::Types<DesiredTypes...>` by applying @p
 *     Filter to @p TestingTypes.
 *
 * @tparam TestingTypes a variadic list of candidate types captured as
 *     ::testing::Types
 * @tparam Filter       a template that will accept a single type as its
 *     template parameter and provide the field `Filter<Type>::value` to accept
 *     `Type` as a member of the desired types
 *
 * @pre Because ::testing::Types requires at lease one type in its template
 *     parameter list, @p Filter must not filter out all of @p TestingTypes.
 */
template<typename TestingTypes, template<typename> typename Filter>
    requires detail::is_testing_types<TestingTypes>
          && filter_types::is_filter<Filter>
using FilterTypes = decltype(
    filter_types::extract_types<Filter>(TestingTypes())
);

} // namespace detail
} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_DETAIL_FILTER_TYPES_HPP
