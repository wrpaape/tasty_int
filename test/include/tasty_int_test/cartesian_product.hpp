#ifndef TASTY_INT_TASTY_INT_TEST_CARTESIAN_PRODUCT_HPP
#define TASTY_INT_TASTY_INT_TEST_CARTESIAN_PRODUCT_HPP

#include <tuple>
#include <type_traits>
#include <utility>


namespace tasty_int_test {
namespace detail {

template<typename T>
concept TupleLike = requires (T t)
{
    std::get<0>(t);
    std::tuple_size<T>{};
};

template<typename T>
struct IsTupleLike : public std::integral_constant<bool, TupleLike<T>>
{}; // struct IsTupleLike

template<typename  ...ProductElementTypes,
         TupleLike    NextTupleLikeType>
auto
make_cartesian_product_pairs(
    const std::tuple<ProductElementTypes...> &product_tup,
    const NextTupleLikeType                  &next_tup
)
{
    auto append_to_product_element = [&](auto &next_element)
    {
        return std::tuple_cat(product_tup, std::make_tuple(next_element));
    };

    return std::apply(
        [&](auto &&...next_elements)
        {
            return std::make_tuple(
                append_to_product_element(next_elements)...
            );
        },
        next_tup
    );
}

template<typename  ...ProductTupleTypes,
         TupleLike    NextTupleLikeType>
auto
expand_cartesian_product(
    const std::tuple<ProductTupleTypes...> &product,
    const NextTupleLikeType                &next_tup
)
{
    return std::apply(
        [&](auto &&...product_tups)
        {
            return std::tuple_cat(
                make_cartesian_product_pairs(product_tups, next_tup)...
            );
        },
        product
    );
}

template<typename ...ProductTupleTypes>
auto
make_cartesian_product(std::tuple<ProductTupleTypes...> &&product)
{
    return std::move(product);
}

template<typename ...ProductTupleTypes,
         TupleLike   NextTupleLikeType,
         typename ...RemTupleLikeTypes>
auto
make_cartesian_product(std::tuple<ProductTupleTypes...> &&product,
                       NextTupleLikeType                &&next_tup,
                       RemTupleLikeTypes                &&...rem_tups)
{
    return make_cartesian_product(
        expand_cartesian_product(std::move(product), next_tup),
        std::forward<RemTupleLikeTypes>(rem_tups)...
    );
}

} // namespace detail


/**
 * @brief Yields all combinations of the values described by the sequence of
 *     tuple-like values, @p tups, where each combination is composed by
 *     selecting a single type from each argument.
 *
 * @params[in] tups a list of tuple-like values (support std::get and
 *     std::tuple_size)
 *
 * @return a std::tuple of std::tuples, where each of the inner tuples
 *     represents a single selection of types from @p tups
 */
template<typename ...TupleLikeTypes>
auto
cartesian_product(TupleLikeTypes ...tups)
    requires std::conjunction_v<detail::IsTupleLike<TupleLikeTypes>...>
{
    return detail::make_cartesian_product(
        std::tuple<std::tuple<>>{},
        std::forward<TupleLikeTypes>(tups)...
    );
}

} // namespace tasty_int_test


#endif // ifndef TASTY_INT_TASTY_INT_TEST_CARTESIAN_PRODUCT_HPP
