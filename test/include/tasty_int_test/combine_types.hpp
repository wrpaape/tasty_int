#ifndef TASTY_INT_TEST_COMBINE_TYPES
#define TASTY_INT_TEST_COMBINE_TYPES

#include <type_traits>

#include "tasty_int_test/cartesian_product.hpp"
#include "tasty_int_test/detail/testing_types.hpp"


namespace tasty_int_test {
namespace detail {

template<typename ...TestingTypes>
auto
combine_types(TestingTypes ...testing_types)
{
    auto product = cartesian_product(
        tuple_from_testing_types(testing_types)...
    );

    return testing_types_from_tuple(product);
}

} // namespace detail


/**
 * @brief Yields all combinations of testing types described by the sequence of
 *     testing type lists, @p TestingTypes, where each combination is a
 *     std::tuple composed by selecting a single type from each testing type
 *     list.
 *
 * @tparam TestingTypes a variadic list of types captured as ::testing::Types
 */
template<typename ...TestingTypes>
    requires std::conjunction_v<detail::IsTestingTypes<TestingTypes>...>
using CombineTypes = decltype(detail::combine_types(TestingTypes{}...));

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_COMBINE_TYPES
