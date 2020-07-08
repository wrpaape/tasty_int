#include "tasty_int_test/combine_types.hpp"

#include "gtest/gtest.h"

#include <tuple>


namespace {

TEST(CombineTypesTest, ZeroTypesTest)
{
    using TestingTypes = tasty_int_test::CombineTypes<>;

    static_assert(std::is_same_v<
        ::testing::Types<std::tuple<>>,
        TestingTypes
    >);
}

TEST(CombineTypesTest, OneTypesTest)
{
    using TestingTypes = tasty_int_test::CombineTypes<::testing::Types<int>>;

    static_assert(std::is_same_v<
        ::testing::Types<std::tuple<int>>,
        TestingTypes
    >);
}

TEST(CombineTypesTest, TwoTypesTest)
{
    using TestingTypes = tasty_int_test::CombineTypes<
        ::testing::Types<int>, ::testing::Types<double, float>
    >;

    static_assert(std::is_same_v<
        ::testing::Types<
            std::tuple<int, double>,
            std::tuple<int, float>
        >,
        TestingTypes
    >);
}

TEST(CombineTypesTest, ThreeTypesTest)
{
    using TestingTypes = tasty_int_test::CombineTypes<
        ::testing::Types<int, char>,
        ::testing::Types<double, long long>,
        ::testing::Types<void *>
    >;

    static_assert(std::is_same_v<
        ::testing::Types<
            std::tuple<int, double, void *>,
            std::tuple<int, long long, void *>,
            std::tuple<char, double, void *>,
            std::tuple<char, long long, void *>
        >,
        TestingTypes
    >);
}

} // namespace
