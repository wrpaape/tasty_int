#include "tasty_int/detail/string_from_int.hpp"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/digits_from_string.hpp"
#include "tasty_int/detail/test/string_conversion_test_common.hpp"


namespace {

using tasty_int::detail::Int;
using tasty_int::detail::Sign;
using tasty_int::detail::digit_type;
using tasty_int::detail::digits_from_string;
using tasty_int::detail::string_from_int;
using string_conversion_test_common::StringViewConversionTestParam;


class StringFromZeroTest :
    public ::testing::TestWithParam<std::tuple<unsigned int, char>>
{}; // class StringFromZeroTest

TEST_P(StringFromZeroTest, ZeroInterprettedAsZero)
{
    auto [base, zero_token] = GetParam();
    Int zero = { .sign = Sign::ZERO, .digits = std::vector<digit_type>{ 0 } };

    std::string result = string_from_int(zero, base);

    EXPECT_EQ(std::string(1, zero_token), result);
}

INSTANTIATE_TEST_SUITE_P(
    Bases2Through36StringFromZeroTest,
    StringFromZeroTest,
    ::testing::Combine(
        ::testing::Range<unsigned int>(2, 36),
        ::testing::Values('0')
    )
);

INSTANTIATE_TEST_SUITE_P(
    Bases37Through64StringFromZeroTest,
    StringFromZeroTest,
    ::testing::Combine(
        ::testing::Range<unsigned int>(37, 64),
        ::testing::Values('A')
    )
);

TEST(StringFromIntTest, SingleNegativeTokenTest)
{
    Int negative_one = {
        .sign = Sign::NEGATIVE,
        .digits = std::vector<digit_type>{ 1 }
    };

    std::string result = string_from_int(negative_one, 10);

    EXPECT_EQ("-1", result);
}

class SingleDigitConsistencyTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{
public:
    static const std::string_view        SINGLE_DIGIT_BASE_10_TOKENS;
    static const std::vector<digit_type> INPUT_DIGITS;
    static const std::vector<StringViewConversionTestParam>
        EQUIVALENT_SINGLE_DIGIT_TOKENS_IN_ALL_BASES;
}; // class SingleDigitConsistencyTest

const std::string_view SingleDigitConsistencyTest::SINGLE_DIGIT_BASE_10_TOKENS =
    "24680";

const std::vector<digit_type> SingleDigitConsistencyTest::INPUT_DIGITS =
    digits_from_string(SINGLE_DIGIT_BASE_10_TOKENS,
                       10);

const std::vector<StringViewConversionTestParam>
SingleDigitConsistencyTest::EQUIVALENT_SINGLE_DIGIT_TOKENS_IN_ALL_BASES = {
    {  2, "110000001101000" },
    {  3, "1020212002" },
    {  4, "12001220" },
    {  5, "1242210" },
    {  6, "310132" },
    {  7, "131645" },
    {  8, "60150" },
    {  9, "36762" },
    { 10, SINGLE_DIGIT_BASE_10_TOKENS },
    { 11, "175a7" },
    { 12, "12348" },
    { 13, "b306" },
    { 14, "8dcc" },
    { 15, "74a5" },
    { 16, "6068" },
    { 17, "506d" },
    { 18, "4432" },
    { 19, "3b6i" },
    { 20, "31e0" },
    { 21, "2dk5" },
    { 22, "26li" },
    { 23, "20f1" },
    { 24, "1ik8" },
    { 25, "1ec5" },
    { 26, "1ad6" },
    { 27, "16n2" },
    { 28, "13dc" },
    { 29, "10a1" },
    { 30, "rck" },
    { 31, "pl4" },
    { 32, "o38" },
    { 33, "mlt" },
    { 34, "lbu" },
    { 35, "k55" },
    { 36, "j1k" },
    { 37, "SBB" },
    { 38, "RDS" },
    { 39, "QIg" },
    { 40, "PRA" },
    { 41, "Obn" },
    { 42, "Npa" },
    { 43, "NOp" },
    { 44, "Mgo" },
    { 45, "MIU" },
    { 46, "LeY" },
    { 47, "LIF" },
    { 48, "KiI" },
    { 49, "KNh" },
    { 50, "Jre" },
    { 51, "JYv" },
    { 52, "JGg" },
    { 53, "Ipj" },
    { 54, "IZC" },
    { 55, "IIo" },
    { 56, "Hwo" },
    { 57, "Hh4" },
    { 58, "HTe" },
    { 59, "HFS" },
    { 60, "GzU" },
    { 61, "Gmk" },
    { 62, "GaE" },
    { 63, "GNv" },
    { 64, "GBo" }
};

TEST_P(SingleDigitConsistencyTest, ConversionToAllBasesFromPositiveIntIsConsistent)
{
    auto [base, expected_output] = GetParam();
    Int positive_integer = { .sign = Sign::POSITIVE, .digits = INPUT_DIGITS };

    std::string result = string_from_int(positive_integer, base);

    EXPECT_EQ(expected_output, result);
}

TEST_P(SingleDigitConsistencyTest, ConversionToAllBasesFromNegativeIntIsConsistent)
{
    auto [base, expected_digits] = GetParam();
    Int negative_integer = { .sign = Sign::NEGATIVE, .digits = INPUT_DIGITS };
    std::string expected_output  = "-";
    expected_output             += expected_digits;

    std::string result = string_from_int(negative_integer, base);

    EXPECT_EQ(expected_output, result);
}

INSTANTIATE_TEST_SUITE_P(
    StringFromIntTest,
    SingleDigitConsistencyTest,
    ::testing::ValuesIn(
        SingleDigitConsistencyTest::EQUIVALENT_SINGLE_DIGIT_TOKENS_IN_ALL_BASES
    )
);


class MultiDigitConsistencyTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{
public:
    static const std::string_view        MULTI_DIGIT_BASE_10_TOKENS;
    static const std::vector<digit_type> INPUT_DIGITS;
    static const std::vector<StringViewConversionTestParam>
        EQUIVALENT_MULTI_DIGIT_TOKENS_IN_ALL_BASES;
}; // class MultiDigitConsistencyTest

const std::string_view MultiDigitConsistencyTest::MULTI_DIGIT_BASE_10_TOKENS =
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579"
    "2468013579";

const std::vector<digit_type> MultiDigitConsistencyTest::INPUT_DIGITS =
    digits_from_string(MULTI_DIGIT_BASE_10_TOKENS,
                       10);

const std::vector<StringViewConversionTestParam>
MultiDigitConsistencyTest::EQUIVALENT_MULTI_DIGIT_TOKENS_IN_ALL_BASES = {
    {  2, "1001000001101110001101011110101011010100010011010101011001000101001001011001101000011110100010010110001110000001111001111101001001011000100110100001111100010000111101111001110010000000101010011010011010001110100100011001110100000111111000010010001011001001010101100000001100001111011111000001110001001101000001001011011001000001011" },
    {  3, "11020201020120111020221011122021022101010100120100122000100011201002100021001120010201020102221101122012102111111202011010211112200101200002020101112021210121102211010121211210222110000100112121021111122121100" },
    {  4, "1020031301223311122202122223020221023031003310102301300033033221023010310033202013233032100011103103101310203032200333002101121022230001201323320032021220021123020023" },
    {  5, "11414442034004314342212201223121004432114001440010322242043430412331024333004403202300334330121320243330212312121102440313344224310433302413304" },
    {  6, "34051251100301131004351435451522542543203520533531413503505145152403302322120443542525212413153121420015044544203554310514312443" },
    {  7, "3165022255135535256206004552053265644012125164255531041611105116066354640602055603122124615461341120364605450206445643" },
    {  8, "110156153653242325310511315036422616017175113046417420757162005232321644316407702213112540141737016115011331013" },
    {  9, "136636514227148238333316318010151070231503636387348172444664124480350066345253542733554728400315537448540" },
    { 10, MULTI_DIGIT_BASE_10_TOKENS },
    { 11, "298002624213a1822a83092a4122381478129a93955192562923338442738971897245749144679357719a8958749222" },
    { 12, "1346247a0b63ab25294585202203a1007b382581149868a5a2364711150aa02b4447254386765290a910a69888723" },
    { 13, "1a2652103c671519136ca3b1a6135ac9815c0679200170708818c682394346b9a601002633047b9761a85509c5" },
    { 14, "698d7dd97a57413252bdc47c5c09c2c304361a8dd47cb79d81cdc7015b452c9a83277a30dba9560b30b3523" },
    { 15, "3ec235e560701bb5344046452b7398824b88e18c67815d71c7c831e423695b3bc171360339c540b1ad439" },
    { 16, "48371af56a26ab2292cd0f44b1c0f3e92c4d0f887bce4054d34748ce83f09164ab0187be0e26825b20b" },
    { 17, "90d2b6b2dg4c97d5da5eg638fg2b0e697cab2f59a5f6794b6283cedc2ee7991gc958f16bagegd3951" },
    { 18, "1c4h50g623chf42a52fd4153deac9383aa7feebd18932c71f8bb811577cafdechadb4a826e0cc5f9" },
    { 19, "891e3ec78ib791ed2c83217b489319b7e6b2245a77ch0908e549194f5dhc0he6gfi6eg937399ga" },
    { 20, "356b241bfe8gi9493ac79cb6h2jj7gi3f21a8hdf4565iehcai827jdia727egg9024a47h651dij" },
    { 21, "1e6ie2bkj0k8h1b4f99655i3id94f5k0b7896eecj4h1gf755kd158he5f3a83dijcdkik6i7kk3" },
    { 22, "12ijldg19k7i6362720dbkcdik3if383gbd0732c3c70g8e438h6a5blgi72id4ll3c82ff98hd" },
    { 23, "m6ak7j76g8bf54d5569c6l570j55fc76h9je620jh0fbjfgekl2j4f2l9f4felak75kjkjb34" },
    { 24, "10n4a7di1d7b85bkb29b44fnbeam4niln5ml0jkc8a7in8hj30ieg6lg827fln9i78bifd1j3" },
    { 25, "199oaj0n9jc7a7d754nb909k13ceann47i5eif4kh2f3ji1bh2ni27gbb5ekgiocn5ni2li4" },
    { 26, "25b8ofbe4de92didpn2dio30nb5e3g6c0lon01kb99chn8bk07lf3j50en71daap9hgeij5" },
    { 27, "46j6fd6p4h78a39f9h094j2971f3j6bpah5bddk43meiai26ae7lgbm3gmlqc09eg7dhg9" },
    { 28, "9io9a5qg97hf3n1clelilm3ki4l7l38r3li659npkrn0fpbcqdcbd755kdhbd3gcjqim3" },
    { 29, "pn8q05o4f45dbdsseqq491ib5fojb6l5ihes4daslres98h2jbbd0ilcasbmq8ij2ohg" },
    { 30, "2jpqghrfp4oi5hob6ep9g9ig5ibjaskpi5ltra2msegpq9h4je0m70e8eao74roqrr99" },
    { 31, "95agcslsrlfiho72ls8i0ul5oijqo859q6iuger0ubcrnbkthob6bfmj4m1rreslnp8" },
    { 32, "143e6nld8jam8kipk7k9ce0ufkioj8fh1tssg2kqd3khjk3u28m9ao1guv0s9k2bcgb" },
    { 33, "4t7napfm1r941r7b8rfal21a7f391o959u6ts34farvugu11it88mmjfum79p236bo" },
    { 34, "nt9sgbl169k4afv7oexhm0letpw26ju2aqcuqlexkushfc9ohqdofndbg8cfdjjb1" },
    { 35, "3pm8b435j1j7d3sx60g997e6q4yb40o03vt3l0nvdx2sqgt13vibp25bth59hom3o" },
    { 36, "m58v631964nantbeyhrcncxnjpn3uvtbg3ife84ryhhdg9bjdq0b4tscnyj5ajgr" },
    { 37, "DieXPFOLPQFidiAZAPhNYIhCaDEhAbcOBHATcFbZFGLcQKWGgHYPRkRBgJiHfIDa" },
    { 38, "biWSGAHUIJDLNPRdHbAMWTiPkKEbfIQfUaGgXYDNhGMZeOTdOiOCJLSflRQgCRd" },
    { 39, "FWSSMZhaBALBWGPhYkXJYLZGZiJWeLbmTaZhJGbOhNZSTXhbGYSZOVhMeFfHcVS" },
    { 40, "BGQdDLPRBHBcYnDBVJhlEHKhGSnbceXUhVIPYBObePIjPBcKCnmTKOJVlSMgcTT" },
    { 41, "KMAGBGoPQJYhKnfCokLllfVakhEKkVFkiWhXCMGMPoNQaDDCGHEMVZHHogFIKT" },
    { 42, "CPQjEXaBUDPmODdfGJaTgNZpRIRZoDEUcpBeUGMmEHimGWpGnREfhYLhTKOFKD" },
    { 43, "YJaZWTUfMmnLlGeMZGDhTHCpPAqhoDIcGlSpLFERqbqdKTiQaVcXdfqPVFdYd" },
    { 44, "GENfUqjSgjRgVpbjXaFFaCGfmlYoQqmXMKigqjGEhPEoHMTITjmIgEXSQDoej" },
    { 45, "BaLTPWFPGqRLlqmAdZhWfBnWrsRLKpjYVmDGZBoheReVDOMBHpPeZTCgonRGJ" },
    { 46, "TWIESjsTBjqPUXctdIUtDSNeAfTnoTgBJaUjaqdUlOZUjXUiFbiWipeEIIYb" },
    { 47, "FWUaTCDDdIUfFUoiXYGJnQUZoVXkWirRldblomETWqbpANNgXZqteDmEVYhN" },
    { 48, "BbsHYWnpYvYYnCbREQABvgQaTVLLNuDKjTGOXXZbXaafVrBfnipPuSInueVb" },
    { 49, "WvCQoKoaTsGAhlFXvucJJkuToWENIHkNGtnuGCFpDJPSrnrZIObiFhCGgpf" },
    { 50, "HFhteHIUeXSXdcveNLrEefhJHvpekLJPSHTEwtrxBjtJJRMCwkLXojssFVd" },
    { 51, "CNCBFCfvmtpYREyBEDkACZUdwbOVeEhOLfmRncsivsduQSswpwXIyNybKYS" },
    { 52, "mBkTVnpUkBbylBKbwKqxehCQimfpFzafMKBGvaoiUFNENBpaEhSYwZVRjf" },
    { 53, "MsgTphyUaQULoLdL0wqCtNuTuWGZYgncYuLyHXgOJYfHXPvkNNLkvsdhLz" },
    { 54, "EWzAE0SvUQvklYUfRTtve1pQQwHqwB0EuvrVhzzoa1idSUSXGkDvDCIYjJ" },
    { 55, "BecOlQyQGKvR2oDUvtmemjrmQjNUjTsyNRKmlQIAx0KdMYCLQIQNM1IrLY" },
    { 56, "fJvWlCIjProicvBRqlOdtwcvxpWTEuxGkcolDfEzaFvpwgJGwDptyNunD" },
    { 57, "LgdwyCyqDJ2FS0lJy4VWIItnuOxKGEk1PlTcnQfDmThnZDSPBXLX2aWLw" },
    { 58, "EVXOHbdQYtjpccumHUfTtR3AidkUgswkQKLeMNvreBFWyqxewapVYrxlt" },
    { 59, "Bn5AUll25TzLP4ggMoAylf1wlCOEachalElqddwlBuaIpSc0qBq2ouABB" },
    { 60, "nQBgf7BFKB5lbbOrw7DrHszo14ZdL5cDNZxABFxzVb4YT7O3whOyZ7Tn" },
    { 61, "PyBOjSdk6AF3jj2pgORUFeJHwLNNbFBRVJ6akg0TwNOw1SKS48doGRuA" },
    { 62, "GdC8WS1l2pPoRT57G7VGZoWIAxOEj4fbaL3x6syWjeCNXBD8p2MFpdMn" },
    { 63, "CrBu6jsGsRHQszqaXTMjdP2jSOTXPhcmgG6863zPWDayz5Dkejc9qSpt" },
    { 64, "BINxr1aiarIpLND0SxwPPpLE0PiHvOQFTTR0jOg/CRZKsBh74OJoJbIL" }
};

TEST_P(MultiDigitConsistencyTest, ConversionToAllBasesFromPositiveIntIsConsistent)
{
    auto [base, expected_output] = GetParam();
    Int positive_integer = { .sign = Sign::POSITIVE, .digits = INPUT_DIGITS };

    std::string result = string_from_int(positive_integer, base);

    EXPECT_EQ(expected_output, result);
}

TEST_P(MultiDigitConsistencyTest, ConversionToAllBasesFromNegativeIntIsConsistent)
{
    auto [base, expected_digits] = GetParam();
    Int negative_integer = { .sign = Sign::NEGATIVE, .digits = INPUT_DIGITS };
    std::string expected_output  = "-";
    expected_output             += expected_digits;

    std::string result = string_from_int(negative_integer, base);

    EXPECT_EQ(expected_output, result);
}

INSTANTIATE_TEST_SUITE_P(
    StringFromIntTest,
    MultiDigitConsistencyTest,
    ::testing::ValuesIn(
        MultiDigitConsistencyTest::EQUIVALENT_MULTI_DIGIT_TOKENS_IN_ALL_BASES
    )
);

} // namespace
