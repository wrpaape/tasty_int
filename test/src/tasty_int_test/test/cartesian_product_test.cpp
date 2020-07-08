#include "tasty_int_test/cartesian_product.hpp"

#include <array>
#include <string>
#include <tuple>
#include <utility>

#include "gtest/gtest.h"


namespace {

TEST(CartesianProductTest, ZeroTuplesTest)
{
    auto product = tasty_int_test::cartesian_product();

    EXPECT_EQ(1, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<>, std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(), std::get<0>(product));
}

TEST(CartesianProductTest, OneTupleTest)
{
    auto tuple1 = std::make_tuple(1.0F, 2U, 3LL);

    auto product = tasty_int_test::cartesian_product(tuple1);

    EXPECT_EQ(3, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float>, std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int>, std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U), std::get<1>(product));

    static_assert(std::is_same_v<
        std::tuple<long long>, std::tuple_element_t<2, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(3LL), std::get<2>(product));
}

TEST(CartesianProductTest, TwoTuplesTest)
{
    auto tuple1 = std::make_tuple(1.0F, 2U, 3LL);
    auto tuple2 = std::make_tuple(4.0L, 5,  6.0);

    auto product = tasty_int_test::cartesian_product(tuple1, tuple2);

    EXPECT_EQ(9, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float, long double>,
        std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 4.0L), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<float, int>,
        std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 5), std::get<1>(product));

    static_assert(std::is_same_v<
        std::tuple<float, double>,
        std::tuple_element_t<2, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 6.0), std::get<2>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, long double>,
        std::tuple_element_t<3, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 4.0L), std::get<3>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, int>,
        std::tuple_element_t<4, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 5), std::get<4>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, double>,
        std::tuple_element_t<5, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 6.0), std::get<5>(product));

    static_assert(std::is_same_v<
        std::tuple<long long, long double>,
        std::tuple_element_t<6, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(3LL, 4.0L), std::get<6>(product));

    static_assert(std::is_same_v<
        std::tuple<long long, int>,
        std::tuple_element_t<7, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(3LL, 5), std::get<7>(product));

    static_assert(std::is_same_v<
        std::tuple<long long, double>,
        std::tuple_element_t<8, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(3LL, 6.0), std::get<8>(product));
}

TEST(CartesianProductTest, ThreeTuplesTest)
{
    auto tuple1 = std::make_tuple(1.0F, 2U);
    auto tuple2 = std::make_tuple(3LL);
    auto tuple3 = std::make_tuple(4.0L, std::string("5"));

    auto product = tasty_int_test::cartesian_product(tuple1, tuple2, tuple3);

    EXPECT_EQ(4, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float, long long, long double>,
        std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3LL, 4.0L), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<float, long long, std::string>,
        std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3LL, std::string("5")),
              std::get<1>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, long long, long double>,
        std::tuple_element_t<2, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 3LL, 4.0L), std::get<2>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, long long, std::string>,
        std::tuple_element_t<3, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 3LL, std::string("5")), std::get<3>(product));
}

TEST(CartesianProductTest, ArrayTest)
{
    auto array1 = std::array{ 1.0F };
    auto array2 = std::array{ 2U, 3U };
    auto array3 = std::array{ 4.0L };

    auto product = tasty_int_test::cartesian_product(array1, array2, array3);

    EXPECT_EQ(2, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float, unsigned int, long double>,
        std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 2U, 4.0L), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<float, unsigned int, long double>,
        std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3U, 4.0L), std::get<1>(product));
}

TEST(CartesianProductTest, PairTest)
{
    auto pair1 = std::pair{ 1.0F, 2U };
    auto pair2 = std::pair{ 3.0L, 4LL };

    auto product = tasty_int_test::cartesian_product(pair1, pair2);

    EXPECT_EQ(4, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float, long double>,
        std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3.0L), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<float, long long>,
        std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 4LL), std::get<1>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, long double>,
        std::tuple_element_t<2, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 3.0L), std::get<2>(product));

    static_assert(std::is_same_v<
        std::tuple<unsigned int, long long>,
        std::tuple_element_t<3, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(2U, 4LL), std::get<3>(product));
}

TEST(CartesianProductTest, MixedTupleLikesTest)
{
    auto tuple1  = std::tuple{ 1.0F };
    auto pair2   = std::pair{ 2U, 3.0L };
    auto array3  = std::array{ 4LL, 5LL };

    auto product = tasty_int_test::cartesian_product(tuple1, pair2, array3);

    EXPECT_EQ(4, std::tuple_size_v<decltype(product)>);

    static_assert(std::is_same_v<
        std::tuple<float, unsigned int, long long>,
        std::tuple_element_t<0, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 2U, 4LL), std::get<0>(product));

    static_assert(std::is_same_v<
        std::tuple<float, unsigned int, long long>,
        std::tuple_element_t<1, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 2U, 5LL), std::get<1>(product));

    static_assert(std::is_same_v<
        std::tuple<float, long double, long long>,
        std::tuple_element_t<2, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3.0L, 4LL), std::get<2>(product));

    static_assert(std::is_same_v<
        std::tuple<float, long double, long long>,
        std::tuple_element_t<3, decltype(product)>
    >);
    EXPECT_EQ(std::make_tuple(1.0F, 3.0L, 5LL), std::get<3>(product));
}

} // namespace
