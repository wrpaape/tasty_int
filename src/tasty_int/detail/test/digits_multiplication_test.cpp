#include "tasty_int/detail/digits_multiplication.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/conversions/digits_from_string.hpp"


namespace {

using tasty_int::detail::operator*=;
using tasty_int::detail::operator*;
using tasty_int::detail::multiply_digit_base;
using tasty_int::detail::multiply_digit_base_power_in_place;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::IntegralDigitsView;
using tasty_int::detail::conversions::digits_from_string;

TEST(DigitsAndDigitsMultiplicationTest,
     DigitsTimesEqualsDigitsRegerenceReferenceToLhs)
{
    std::vector<digit_type> lhs = { 1, 2, 3 };
    std::vector<digit_type> rhs = { 4, 5, 6 };

    EXPECT_EQ(&lhs, &(lhs *= rhs));
}

template<typename RhsType>
void
test_multiply_in_place(const std::vector<digit_type> &lhs,
                       const RhsType                 &rhs,
                       const std::vector<digit_type> &expected_result)
{
    auto multiplicand = lhs;

    multiplicand *= rhs;

    EXPECT_EQ(expected_result, multiplicand);
}

template<typename LhsType,
         typename RhsType>
void
test_multiply(const LhsType                 &lhs,
              const RhsType                 &rhs,
              const std::vector<digit_type> &expected_result)
{
    auto result = lhs * rhs;

    EXPECT_EQ(expected_result, result);
}

template<typename MultiplierType>
void
test_multiplication(const std::vector<digit_type> &digits,
                    const MultiplierType          &multiplier,
                    const std::vector<digit_type> &expected_result)
{
    test_multiply_in_place(digits, multiplier, expected_result);

    if constexpr (std::is_same_v<MultiplierType, std::vector<digit_type>>)
        test_multiply_in_place(multiplier, digits, expected_result);

    test_multiply(digits, multiplier, expected_result);

    test_multiply(multiplier, digits, expected_result);
}


TEST(DigitsAndDigitsMultiplicationTest, DigitsTimesOneEqualsOriginalValue)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::vector<digit_type> ONE             = { 1 };
    std::vector<digit_type> expected_result = digits;

    test_multiplication(digits, ONE, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, ZeroTimesZeroEqualsZero)
{
    std::vector<digit_type> ZERO = { 0 };

    test_multiplication(ZERO, ZERO, ZERO);
}

TEST(DigitsAndDigitsMultiplicationTest, OneTimesZeroEqualsZero)
{
    std::vector<digit_type> ONE  = { 1 };
    std::vector<digit_type> ZERO = { 0 };

    test_multiplication(ONE, ZERO, ZERO);
}

TEST(DigitsAndDigitsMultiplicationTest, DigitsTimesZeroEqualsZero)
{
    std::vector<digit_type> digits = { 1, 2, 3 };
    std::vector<digit_type> ZERO   = { 0 };

    test_multiplication(digits, ZERO, ZERO);
}

TEST(DigitsAndDigitsMultiplicationTest, DigitsTimesSingleDigitNoCarry)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::vector<digit_type> single_digit    = { 2 };
    std::vector<digit_type> expected_result = { 2, 4, 6 };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, DigitsTimesSingleDigitCarry)
{
    std::vector<digit_type> digits = { 1, 2, 1 };
    std::vector<digit_type> single_digit = { DIGIT_TYPE_MAX };
    IntegralDigitsView carry1(DIGIT_TYPE_MAX * 2);
    IntegralDigitsView carry2(carry1.high_digit() + DIGIT_TYPE_MAX);
    std::vector<digit_type> expected_result = {
        DIGIT_TYPE_MAX,
        carry1.low_digit(),
        carry2.low_digit(),
        carry2.high_digit()
    };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, MultipleDigitsTimesMultipleDigits)
{
    auto digits1 = digits_from_string(        "123456789012345678901234567890", 10);
    auto digits2 = digits_from_string("99999999999999999999999999999999999999", 10);
    auto expected_result = digits_from_string(
        "12345678901234567890123456788999999999876543210987654321098765432110",
        10
    );

    test_multiplication(digits1, digits2, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, ZeroDigitsTimesManyDigits)
{
    std::vector<digit_type> ZERO = { 0 };

    auto many_digits = digits_from_string(
        "777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777",
        10
    );

    test_multiplication(ZERO, many_digits, ZERO);
}

TEST(DigitsAndDigitsMultiplicationTest, FewDigitsTimesManyDigits)
{
    auto few_digits = digits_from_string("100000000000000000000", 10);
    auto many_digits = digits_from_string(
        "888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888",
        10
    );
    auto expected_result = digits_from_string(
        "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888800000000000000000000",
        10
    );

    test_multiplication(few_digits, many_digits, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, ManyDigitsTimesManyDigits)
{
    auto digits1 = digits_from_string(
        "1357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468135790246813579024681357902468",
        10
    );

    auto digits2 = digits_from_string(
        "9876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210",
        10
    );

    auto expected_result = digits_from_string(
        "13411382402849918760435869928058674798007376260320888504084103938213611902601881341138240149201629216428943441793772396194465044820955285002246406552239728460425481626562699040708284991876030007968123151674864330255291634534309683604309020375518707239060651244056943176420782122843586992804509577332466045538448113334364962211488511308954052639675925414845644556572369657166017485867479800601835785261692359046320113956647099200866218700606772748112692362616470745042167225382268737626032075271383727678016424782889447679797725288130650580828152863284324066848583284736873416278888850408409035918892918679694493376749969488553048963943110097903091529941187205009206525702429433090393821361054469941306955774650846455517099733356911482116211299089673144996772516008457771751723829190260188120534799332204357985235523603725061140892656992141280787019329587482453109626297326050434934113824013562260453371313850538640165574014894609416577266143166507134467528765461840681747692848694920162921507104097349536913774802813325465193527345010572214350179169419930111740484230653897545013374666696135957889093444910857329403280531431547532992276701284139864926905205972539642545238876449322378864412087008389193613033717852522851634374233148349618113326181291181740077103086202508799839730729105921057822786904273498170276471765012559371299747156609823837608967295955695220815049371203452922032540090694473488918569296876769124486168131928465935140831505708881641790368013300984786242293277115448807560666828740978877672589107247108032672695715462068062765686655398516650452046463536424126202764360605188630859010082565750130204559925215254483741005297496048514661799649957399444844861892469398384045431057884392227736424134968440904716323939593580378871552836378374763486959424333608137231852033203034325268288344721627325691642581691112243081306022799350082129056956197817890418273008521676422800152554474813746666961223788644107291059209220325400771154488062027643604693983840318520332016764228000167642280",
        10
    );

    test_multiplication(digits1, digits2, expected_result);
}

TEST(DigitsAndDigitsMultiplicationTest, SparseManyDigitsTimeManyDigits)
{
    std::vector<digit_type> digits1(500);
    digits1.back() = 1;
    std::vector<digit_type> digits2(1000);
    digits2.back() = 1;
    std::vector<digit_type> expected_result(digits1.size() + digits2.size() - 1);
    expected_result.back() = 1;

    test_multiplication(digits1, digits2, expected_result);
}


TEST(DigitsAndIntegralMultiplicationTest, DigitsTimesOneEqualsOriginalValue)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::uintmax_t          ONE             = 1;
    std::vector<digit_type> expected_result = digits;

    test_multiplication(digits, ONE, expected_result);
}

TEST(DigitsAndIntegralMultiplicationTest, ZeroTimesZeroEqualsZero)
{
    std::vector<digit_type> ZERO_DIGITS   = { 0 };
    std::uintmax_t          ZERO_INTEGRAL = 0;

    test_multiplication(ZERO_DIGITS, ZERO_INTEGRAL, ZERO_DIGITS);
}

TEST(DigitsAndIntegralMultiplicationTest, OneTimesZeroEqualsZero)
{
    std::vector<digit_type> ONE           = { 1 };
    std::uintmax_t          ZERO_INTEGRAL = 0;
    std::vector<digit_type> ZERO_DIGITS   = { 0 };

    test_multiplication(ONE, ZERO_INTEGRAL, ZERO_DIGITS);
}

TEST(DigitsAndIntegralMultiplicationTest, DigitsTimesZeroEqualsZero)
{
    std::vector<digit_type> digits = { 1, 2, 3 };
    std::uintmax_t          ZERO_INTEGRAL = 0;
    std::vector<digit_type> ZERO_DIGITS   = { 0 };

    test_multiplication(digits, ZERO_INTEGRAL, ZERO_DIGITS);
}

TEST(DigitsAndIntegralMultiplicationTest, DigitsTimesSingleDigitNoCarry)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::uintmax_t          single_digit    = 2;
    std::vector<digit_type> expected_result = { 2, 4, 6 };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndIntegralMultiplicationTest, DigitsTimesSingleDigitCarry)
{
    std::vector<digit_type> digits = { 1, 2, 1 };
    std::uintmax_t single_digit = DIGIT_TYPE_MAX;
    IntegralDigitsView carry1(DIGIT_TYPE_MAX * 2);
    IntegralDigitsView carry2(carry1.high_digit() + DIGIT_TYPE_MAX);
    std::vector<digit_type> expected_result = {
        DIGIT_TYPE_MAX,
        carry1.low_digit(),
        carry2.low_digit(),
        carry2.high_digit()
    };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndIntegralMultiplicationTest, MultipleDigitsTimesMultipleDigits)
{
    std::vector<digit_type> digits1 = {
        DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };
    auto digits2 = std::numeric_limits<std::uintmax_t>::max();
    std::vector<digit_type> expected_result = {
        1, 0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX
    };

    test_multiplication(digits1, digits2, expected_result);
}


TEST(DigitsAndFloatingPointMultiplicationTest, DigitsTimesOneEqualsOriginalValue)
{
    std::vector<digit_type> digits = { 1, 2, 3 };
    long double          ONE       = 1.0;
    std::vector<digit_type> expected_result = digits;

    test_multiplication(digits, ONE, expected_result);
}

TEST(DigitsAndFloatingPointMultiplicationTest, ZeroTimesZeroEqualsZero)
{
    std::vector<digit_type> ZERO_DIGITS = { 0 };
    long double ZERO_FLOATING_POINT     = 0.0;

    test_multiplication(ZERO_DIGITS, ZERO_FLOATING_POINT, ZERO_DIGITS);
}

TEST(DigitsAndFloatingPointMultiplicationTest, OneTimesZeroEqualsZero)
{
    std::vector<digit_type> ONE         = { 1 };
    long double ZERO_FLOATING_POINT     = 0.0;
    std::vector<digit_type> ZERO_DIGITS = { 0 };

    test_multiplication(ONE, ZERO_FLOATING_POINT, ZERO_DIGITS);
}

TEST(DigitsAndFloatingPointMultiplicationTest, DigitsTimesZeroEqualsZero)
{
    std::vector<digit_type> digits      = { 1, 2, 3 };
    long double ZERO_FLOATING_POINT     = 0.0;
    std::vector<digit_type> ZERO_DIGITS = { 0 };

    test_multiplication(digits, ZERO_FLOATING_POINT, ZERO_DIGITS);
}

TEST(DigitsAndFloatingPointMultiplicationTest, DigitsTimesSingleDigitNoCarry)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    long double single_digit                = 2.0;
    std::vector<digit_type> expected_result = { 2, 4, 6 };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndFloatingPointMultiplicationTest, DigitsTimesSingleDigitCarry)
{
    std::vector<digit_type> digits = { 1, 2, 1 };
    long double single_digit = DIGIT_TYPE_MAX;
    IntegralDigitsView carry1(DIGIT_TYPE_MAX * 2);
    IntegralDigitsView carry2(carry1.high_digit() + DIGIT_TYPE_MAX);
    std::vector<digit_type> expected_result = {
        DIGIT_TYPE_MAX,
        carry1.low_digit(),
        carry2.low_digit(),
        carry2.high_digit()
    };

    test_multiplication(digits, single_digit, expected_result);
}

TEST(DigitsAndFloatingPointMultiplicationTest, MultipleDigitsTimesMultipleDigits)
{
    std::vector<digit_type> digits1 = {
        DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };
    auto digits2 = std::pow(DIGIT_BASE, 10.0L);
    std::vector<digit_type> expected_result(12);
    expected_result[expected_result.size() - 2] = DIGIT_TYPE_MAX;
    expected_result.back()                      = DIGIT_TYPE_MAX;

    test_multiplication(digits1, digits2, expected_result);
}


TEST(MultiplyDigitBaseTest, SingleDigit)
{
    std::vector<digit_type> multiplicand    = { 1 };
    std::vector<digit_type> expected_result = { 0, 1 };

    auto result = multiply_digit_base(multiplicand);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyDigitBaseTest, MutlipleDigits)
{
    std::vector<digit_type> multiplicand    = { 1, 2, 3, 4 };
    std::vector<digit_type> expected_result = { 0, 1, 2, 3, 4 };

    auto result = multiply_digit_base(multiplicand);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyDigitBasePowerInPlaceTest, ZeroWithZeroExponent)
{
    std::vector<digit_type> multiplicand = { 0 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(ZERO, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerInPlaceTest, ZeroWithNonzeroExponent)
{
    std::vector<digit_type> multiplicand = { 0 };
    std::vector<digit_type>::size_type exponent = 7;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(exponent, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerInPlaceTest, NonzeroWithZeroExponent)
{
    std::vector<digit_type> multiplicand = { 1, 2, 3 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(ZERO, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerInPlaceTest, NonzeroWithNonzeroExponent)
{
    std::vector<digit_type> multiplicand = { 1, 2, 3 };
    std::vector<digit_type>::size_type exponent = 5;
    std::vector<digit_type> expected_result = { 0, 0, 0, 0, 0, 1, 2, 3 };

    multiply_digit_base_power_in_place(exponent, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyPowersTest, NonzeroWithNonzeroExponent)
{
    SUCCEED(); // TODO
}

} // namespace
