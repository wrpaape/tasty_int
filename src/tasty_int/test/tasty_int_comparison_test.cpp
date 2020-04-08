#include "tasty_int/tasty_int.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/comparison_tests.hpp"


namespace {

using tasty_int::TastyInt;


TEST(TastIntComparisonTest, TastyIntComparesEqualToEqualTastyInt)
{
    TastyInt lhs(12345);
    TastyInt rhs(lhs);

    tasty_int_test::expect_equal(lhs, rhs);
}

TEST(TastIntComparisonTest, LesserTastyIntComparesUnequalToGreaterTastyInt)
{
    TastyInt lesser(-777);
    TastyInt greater(12345);

    tasty_int_test::expect_unequal(lesser, greater);
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntAndArithmeticTypeComparisonTest : public ::testing::Test
{}; // class TastyIntAndArithmeticTypeComparisonTest

TYPED_TEST_SUITE(TastyIntAndArithmeticTypeComparisonTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntAndArithmeticTypeComparisonTest,
           TastyIntComparesEqualToEqualArithmeticValue)
{
    auto arithmetic_value = std::numeric_limits<TypeParam>::max();
    TastyInt tasty_int(arithmetic_value);

    tasty_int_test::expect_equal(arithmetic_value, tasty_int);
}

TYPED_TEST(TastyIntAndArithmeticTypeComparisonTest,
           LesserTastyIntComparesUnequalToGreaterArithmeticValue)
{
    auto lesser_arithmetic_value  = std::numeric_limits<TypeParam>::lowest();
    auto greater_arithmetic_value = std::numeric_limits<TypeParam>::max();
    TastyInt tasty_int(lesser_arithmetic_value);

    tasty_int_test::expect_unequal(tasty_int, greater_arithmetic_value);
}

TYPED_TEST(TastyIntAndArithmeticTypeComparisonTest,
           GreaterTastyIntComparesUnequalToLesserArithmeticValue)
{
    auto lesser_arithmetic_value  = std::numeric_limits<TypeParam>::lowest();
    auto greater_arithmetic_value = std::numeric_limits<TypeParam>::max();
    TastyInt tasty_int(greater_arithmetic_value);

    tasty_int_test::expect_unequal(lesser_arithmetic_value, tasty_int);
}

} // namespace
