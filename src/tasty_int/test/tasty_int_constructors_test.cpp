#include "tasty_int/tasty_int.hpp" // TastyInt

#include <limits>                  // std::numeric_limits

#include "gtest/gtest.h"           // TEST macros


/**
 * TODO
 */
template<typename ArithmeticType>
struct TastyIntArtihmeticTypesConstructorTest : public ::testing::Test
{
    static constexpr auto ZERO    = static_cast<ArithmeticType>(0);
    static constexpr auto MINIMUM = std::numeric_limits<ArithmeticType>::min();
    static constexpr auto MAXIMUM = std::numeric_limits<ArithmeticType>::max();

    static constexpr ArithmeticType
    get_middle(ArithmeticType lower_bound,
               ArithmeticType upper_bound)
    {
        // promote to long double to avoid overflow
        auto range = static_cast<long double>(upper_bound)
                   - static_cast<long double>(lower_bound);
        return lower_bound + static_cast<ArithmeticType>(range / 2.0L);
    }

    static constexpr auto MEDIAN         = get_middle(MINIMUM, MAXIMUM);
    static constexpr auto LOWER_QUARTILE = get_middle(MINIMUM, MEDIAN);
    static constexpr auto UPPER_QUARTILE = get_middle(MEDIAN,  MAXIMUM);

    static constexpr auto EPSILON =
        std::numeric_limits<ArithmeticType>::epsilon();
}; // struct TastyIntArtihmeticTypesConstructorTest

/**
 * The list of supported integral types (taken from
 * https://en.cppreference.com/w/cpp/types/is_integral and
 * https://en.cppreference.com/w/cpp/types/is_floating_point).
 */
using TastyIntArithmeticTypes = ::testing::Types<
    // sign-less integral types
    bool,

    // fixed-size char types
#if HAVE_CHAR8_T
    char8_t,
#endif
    char16_t, char32_t, wchar_t,

    // signed integral types
    signed char, signed short int, signed int, signed long int,
    signed long long int,

    // unsigned integral types
    unsigned char, unsigned short int, unsigned int, unsigned long int,
    unsigned long long int,

    // floating point types
    float, double, long double
>;

TYPED_TEST_SUITE(TastyIntArtihmeticTypesConstructorTest,
                 TastyIntArithmeticTypes);

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMinimumValue)
{
    EXPECT_NEAR(TestFixture::MINIMUM,
                TastyInt(TestFixture::MINIMUM).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithLowerQuartileValue)
{
    EXPECT_NEAR(TestFixture::LOWER_QUARTILE,
                TastyInt(TestFixture::LOWER_QUARTILE).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMedianValue)
{
    EXPECT_NEAR(TestFixture::MEDIAN,
                TastyInt(TestFixture::MEDIAN).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithUpperQuartileValue)
{
    EXPECT_NEAR(TestFixture::UPPER_QUARTILE,
                TastyInt(TestFixture::UPPER_QUARTILE).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMaximumValue)
{
    EXPECT_NEAR(TestFixture::MAXIMUM,
                TastyInt(TestFixture::MAXIMUM).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithZero)
{
    EXPECT_NEAR(TestFixture::ZERO,
                TastyInt(TestFixture::ZERO).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TEST(String, DISABLED_sign) // TODO: re-enable
{
    ASSERT_LT(TastyInt("-1").to_number<int>(), 0);

    ASSERT_LT(TastyInt("-9999999999999999999999999999999").to_number<int>(), 0);

    ASSERT_EQ(TastyInt("0").to_number<int>(), 0);

    ASSERT_GT(TastyInt("1").to_number<int>(), 0);

    ASSERT_GT(TastyInt("9999999999999999999999999999999").to_number<int>(), 0);
}
