#include "tasty_int/tasty_int.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/signed_integral_types.hpp"
#include "tasty_int_test/unsigned_arithmetic_types.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

template<tasty_int::Arithmetic>
class TastyIntPrepareArithmeticOperandTest : public ::testing::Test
{}; // class TastyIntPrepareArithmeticOperandTest

TYPED_TEST_SUITE(TastyIntPrepareArithmeticOperandTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntPrepareArithmeticOperandTest, PreservesValue)
{
    for (auto value : tasty_int_test::SampleArithmetic<TypeParam>::VALUES)
        EXPECT_EQ(value, tasty_int::prepare_operand(value));
}


template<tasty_int::UnsignedIntegral>
class TastyIntPrepareUnsignedIntegralOperandTest : public ::testing::Test
{}; // class TastyIntPrepareUnsignedIntegralOperandTest

TYPED_TEST_SUITE(TastyIntPrepareUnsignedIntegralOperandTest,
                 tasty_int_test::UnsignedArithmeticTypes);

TYPED_TEST(TastyIntPrepareUnsignedIntegralOperandTest, PromotesToUintmaxT)
{
    static_assert(std::is_same_v<
        std::uintmax_t, decltype(tasty_int::prepare_operand(TypeParam()))
    >);
}


template<tasty_int::SignedIntegral>
class TastyIntPrepareSignedIntegralOperandTest : public ::testing::Test
{}; // class TastyIntPrepareSignedIntegralOperandTest

TYPED_TEST_SUITE(TastyIntPrepareSignedIntegralOperandTest,
                 tasty_int_test::SignedIntegralTypes);

TYPED_TEST(TastyIntPrepareSignedIntegralOperandTest, PromotesToIntmaxT)
{
    static_assert(std::is_same_v<
        std::intmax_t, decltype(tasty_int::prepare_operand(TypeParam()))
    >);
}


template<tasty_int::FloatingPoint>
class TastyIntPrepareFloatingPointOperandTest : public ::testing::Test
{}; // class TastyIntPrepareFloatingPointOperandTest

TYPED_TEST_SUITE(TastyIntPrepareFloatingPointOperandTest,
                 tasty_int_test::FloatingPointTypes);

TYPED_TEST(TastyIntPrepareFloatingPointOperandTest, PromotesToLongDouble)
{
    static_assert(std::is_same_v<
        long double, decltype(tasty_int::prepare_operand(TypeParam()))
    >);
}

} // namespace
