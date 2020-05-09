#include "tasty_int/detail/order_by_size.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::order_by_size;
using tasty_int::detail::digit_type;


TEST(OrderBySizeTest, SmallerLhsAndLargerRhs)
{
    std::vector<digit_type> lhs = { 0 };
    std::vector<digit_type> rhs = { 0, 1 };

    auto &&[smaller, larger] = order_by_size(lhs, rhs);

    EXPECT_EQ(&lhs, &smaller);
    EXPECT_EQ(&rhs, &larger);
}

TEST(OrderBySizeTest, LargerLhsAndSmallerRhs)
{
    std::vector<digit_type> lhs = { 0, 1 };
    std::vector<digit_type> rhs = { 0 };

    auto &&[smaller, larger] = order_by_size(lhs, rhs);

    EXPECT_EQ(&lhs, &larger);
    EXPECT_EQ(&rhs, &smaller);
}

} // namespace
