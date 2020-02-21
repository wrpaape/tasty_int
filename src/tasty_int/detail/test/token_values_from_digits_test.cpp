#include "tasty_int/detail/token_values_from_digits.hpp"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/base_36_token_from_value.hpp"
#include "tasty_int/detail/base_64_token_from_value.hpp"
#include "tasty_int/detail/digits_from_string.hpp"
#include "tasty_int/detail/test/string_conversion_test_common.hpp"


namespace {

using tasty_int::detail::base_36_token_from_value;
using tasty_int::detail::base_64_token_from_value;
using tasty_int::detail::digit_type;
using tasty_int::detail::digits_from_string;
using tasty_int::detail::token_values_from_digits;
using string_conversion_test_common::StringViewConversionTestParam;


std::string tokens_from_token_values(const std::string &token_values,
                                     unsigned int       base)
{
    auto token_from_value = (base <= 36)
                          ? base_36_token_from_value
                          : base_64_token_from_value;

    std::string tokens(token_values.size(), '\0');
    auto token_cursor = tokens.end();
    for (char value : token_values)
        *--token_cursor = token_from_value(value);

    return tokens;
}


class ZeroTest : public ::testing::TestWithParam<unsigned int>
{}; // class ZeroTest

TEST_P(ZeroTest, ZeroInterprettedAsZero)
{
    unsigned int base = GetParam();
    std::string token_values;

    token_values_from_digits(std::vector<digit_type>{ 0 }, base,
                             token_values);

    EXPECT_EQ(std::string{ '\0' }, token_values);
}

INSTANTIATE_TEST_SUITE_P(
    StringFromDigitsTest,
    ZeroTest,
    ::testing::Range<unsigned int>(2, 64)
);


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
    "987654321";

const std::vector<digit_type> SingleDigitConsistencyTest::INPUT_DIGITS =
    digits_from_string(SINGLE_DIGIT_BASE_10_TOKENS,
                       10);

const std::vector<StringViewConversionTestParam>
SingleDigitConsistencyTest::EQUIVALENT_SINGLE_DIGIT_TOKENS_IN_ALL_BASES = {
    {  2, "111010110111100110100010110001" },
    {  3, "2112211110001000200" },
    {  4, "322313212202301" },
    {  5, "4010314414241" },
    {  6, "242000505413" },
    {  7, "33321631443" },
    {  8, "7267464261" },
    {  9, "2484401020" },
    { 10, SINGLE_DIGIT_BASE_10_TOKENS },
    { 11, "467561345" },
    { 12, "23691b269" },
    { 13, "129806a54" },
    { 14, "95256493" },
    { 15, "5ba934b6" },
    { 16, "3ade68b1" },
    { 17, "26fa3d00" },
    { 18, "1b0c6fe9" },
    { 19, "11igbha7" },
    { 20, "f8cgfg1" },
    { 21, "bah8ck3" },
    { 22, "8fe2k25" },
    { 23, "6fa7j95" },
    { 24, "540klf9" },
    { 25, "4139lml" },
    { 26, "353792h" },
    { 27, "2emc10i" },
    { 28, "21anf4h" },
    { 29, "1j4bppg" },
    { 30, "1aj9nkl" },
    { 31, "13fdo0p" },
    { 32, "tdsq5h" },
    { 33, "p7quur" },
    { 34, "lp2k8h" },
    { 35, "is5nev" },
    { 36, "gc0uy9" },
    { 37, "OIkQGB" },
    { 38, "MRZJFH" },
    { 39, "KkjiOe" },
    { 40, "JZgDmB" },
    { 41, "IVVJeg" },
    { 42, "HXQifD" },
    { 43, "GemJoG" },
    { 44, "FrWQBF" },
    { 45, "FPmUXk" },
    { 46, "EkanQF" },
    { 47, "EOSohi" },
    { 48, "DqCdTh" },
    { 49, "DYPtLf" },
    { 50, "DIBLkV" },
    { 51, "CryaAA" },
    { 52, "CfEIoR" },
    { 53, "CTJBcK" },
    { 54, "CIINot" },
    { 55, "B0zRQQ" },
    { 56, "BsX0sR" },
    { 57, "BkgGJt" },
    { 58, "BdP5Mt" },
    { 59, "BWd3Ks" },
    { 60, "BQMcZV" },
    { 61, "BKUQHb" },
    { 62, "BE0GAZ" },
    { 63, "+r3Gt" },
    { 64, "63mix" }
};

TEST_P(SingleDigitConsistencyTest, ConversionToAllBasesIsConsistent)
{
    auto [base, expected_output] = GetParam();

    std::string token_values;
    token_values_from_digits(INPUT_DIGITS, base,
                             token_values);

    EXPECT_EQ(expected_output, tokens_from_token_values(token_values, base));
}

INSTANTIATE_TEST_SUITE_P(
    StringFromDigitsTest,
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
    "9876543210"
    "9876543210"
    "9876543210"
    "9876543210"
    "9876543210"
    "9876543210"
    "9876543210"
    "9876543210";

const std::vector<digit_type> MultiDigitConsistencyTest::INPUT_DIGITS =
    digits_from_string(MULTI_DIGIT_BASE_10_TOKENS,
                       10);

const std::vector<StringViewConversionTestParam>
MultiDigitConsistencyTest::EQUIVALENT_MULTI_DIGIT_TOKENS_IN_ALL_BASES = {
    {  2, "11010101001111010001110101100101000100110010001100110110011110101111111100000101011010011010000110000110110111011100111100101111110100100000111111000101110111110110101110101000001101011001100111110111101101010100011110011001111101011101010001110001100111111011101010" },
    {  3, "200121022001110022221021211120020121001001020212010201121220110111212021100122222002210212210012000100202102011002200221002121211002200201212222010122212100022120012100" },
    {  4, "3111033101311211010302030312132233330011122122012012313130330233310200333011313312232220031121213313231110132121331131101301213323222" },
    {  5, "2011201101422042432410001134103343403310304312011204242302431141001120244111224411132102112133030204142011343340320" },
    {  6, "4111014440101235414535413035255153503330415305302334252142031455500422552031025120104452031433043354230" },
    {  7, "34101304441546504334333203055664265251241441354055311456561634614030664611460655456310556154123" },
    {  8, "32517216545046214663657740532320606673474576440770567665650153147675524363175352161477352" },
    {  9, "617261408837746217031225121556414767318862725705010672132627077732621788118770276170" },
    { 10, MULTI_DIGIT_BASE_10_TOKENS },
    { 11, "7071a04208a05785832937a657a8a60522a8806a17859a7094001086911370952958096095774" },
    { 12, "14470683b014a6225404a2358195791b237a095949924635593201a3507534bab2408382976" },
    { 13, "804a40885153a7136c3ba661c4a106415325a44b405c111725bcc4c133a6b31a76c93bb4" },
    { 14, "823927bbb06b3b3099a3315ca32ba2333d7107179cb4056a044a07894193313d00b04a" },
    { 15, "10ac49b6dd34a05b3630a59c98647c23d52ddb70c9c1ed21bc03db3dc00b9c18b1790" },
    { 16, "354f475944c8cd9ebfc15a6861b773cbf483f177daea0d667ded51e67d751c67eea" },
    { 17, "10a7ad20eed64ab93ed1f23g97985eg5074921faega777c0gc659ac1d34gb4f000" },
    { 18, "83270e3fbaah34632a25c40aada8e060f4e4d51g0eda73270873e8h744gc54h0" },
    { 19, "52g8h4hii506cc861bc783ebhe9ii9348b086bahc20he27536690e1e63h4cd7" },
    { 20, "45d62h1i58f1ae2jdbicj1gg8ecif5a55b1i8e25a4827heca35bebfgg87i0a" },
    { 21, "4c6a50j7bh887a906b6104d4923c9ijbdh0652952ai7i04chb12343k9dih3" },
    { 22, "643hb06340eib52akj4kdddjl9d705fgh98aj59kbl217jgcefb8890ffi94" },
    { 23, "a7h52c2ghcmgb2he00bmagh10mhlj74g3f952lk5im5lj3mi4b8636ea8f6" },
    { 24, "l09ef6n4d323ib421gkmkld8m5b5jb3n53fj9hnecbd5amg044j332i89i" },
    { 25, "217159c4ehl018l3jj3g34ga6ammfeg95172o67el6h5b78ffalm18nj3a" },
    { 26, "5i74eka8ln36f4n6g99mbm8gb183i1670ic7kellm7em4fdldndda8fp4" },
    { 27, "ig81c8p7mf6g116n3jgocdn79hq2lnl509kb42ip2gm2ijnq3hn98f59" },
    { 28, "2edd03fogg9epjig4reddka2dprb1ggheenr9c2nr1apkia5kpm8maga" },
    { 29, "ah7ij9l0gjoqdohh8d3236bok7fdem5sanr928plnqne43j49o3onb8" },
    { 30, "1ksiihi6o5r09cl36lani4dm8ptmasdhgqaqc10p49sd58jso4sogr0" },
    { 31, "8tq2gp8seg25ibe50jssuoq5u0sg468smngrno79gapdkagfr79r5c" },
    { 32, "1l9t3lih68pmfbvgaqd1gresubui1v2tuqt86mcvfda7j7qt8scvna" },
    { 33, "ap4fgtuulnrwi6j0h47bri4p1nhnkpe12s10b5a73wt12fplpld2f" },
    { 34, "29g8vv5eevgwrjphqfbipxg3ssr4ua1lv2jjtw07fga76og6op8h0" },
    { 35, "hnanlduk1ar3wvbpebxi9urtvyv9wurxqywe1dmrc401br5ecgaa" },
    { 36, "476as11fyaxy93wzbn3l4bix2lqwacjtz0qhw36h814tcjrirnqi" },
    { 37, "BBPPLLdZaUbXRdLZUcNHRDiUVPIVaIDcVKadecXSfjLDPSiNPUQk" },
    { 38, "KEdTTUWBXjjLlZJWHUiUBkZNbQcNEiMRGKaAeOAAPZfDkiVKDGa" },
    { 39, "CddSBIjkXlSJINMPcUFJOmMGmiAcaWYaELFmSQMkZEaMTZeXcde" },
    { 40, "fGXgAbgCAOeFYabChdnknLKDUdKWFfhZdiOAjLPEQJXDcAUnUK" },
    { 41, "JMBnliBTXCSiafcLWLTEQHOXejlZDLUKNeNmgfXSbmChBePPVS" },
    { 42, "CjjdlCNgFGDEZPpTEWXkIabKfZcFchTHTfppdYIgAYMOHIUEdY" },
    { 43, "mfcYkPgqCNiXDpMScBRgWLFgkhYdJnKIgULdUBpARmlHeSMTO" },
    { 44, "MlQDMPFkCCrOojIDamhpFmTIoJneTfSqnDKDKAHmccaLfKKEa" },
    { 45, "EQbeYAgiNmlWnHJCHINAHTNIiFnBSbbSDEknYsDEIpIqnRlXA" },
    { 46, "BXtIELbpHhAKUCEZteBoAChGAjnDQPHYZOFSPotWUHKmNmeqG" },
    { 47, "ZWBJsRLsniiSKGtZXKJJWoQhMsQYWdERANHMPLWUOnBJiOPg" },
    { 48, "JWWhhcRuIhgfaHaUBYFNlfGWPJKYqDIsaABXenkASrIQgOEq" },
    { 49, "DdBVgdnvEYfYOVowevTJdgKnFmIhvrtiLDGurLqvnpWFpMdR" },
    { 50, "BTYxxOFVPJUHAwtePqKtIlxlqBpoerZCrWpxLBRtDFBeMROK" },
    { 51, "bwWGMHewZomJiNiYtthMESaBJymNPUVKNtuyWNMMiPWPiAA" },
    { 52, "LWvcgXpIMiLkBmBtfacrUivqzmAvfTAjhdVleXnSimfbDze" },
    { 53, "EoYRPkJEbrOSGtRixEVhiSSRhCjhwdjMYVpZcbyHuWSMHRD" },
    { 54, "CAukbjGagOLmo1kbobdwJhMBSavWhLVjbzCayyYvxLlmKdk" },
    { 55, "vlEijgm2RfbvzW2qhZWH0xpnWztTxV121HQN0kTLKpEJ2P" },
    { 56, "VKlsmasLfQUcoAvFdARUpWzD2WpSbArnnPyrScNcWgCskK" },
    { 57, "Jfkij3EU2TPZ4PJoZMTrijUTbtXOa3AwShrRpdewvAZcwt" },
    { 58, "EVWEHN1kFO5iAc0FMcdTUgovqrbvN3C2XbnfZcqkXXuixI" },
    { 59, "CBZYqrm4C2pauie362KBzG25JBSzlFuEUwmkqie0v6bmej" },
    { 60, "5AjdGFw33TNwGgQgeNvXwkoSxrjrzn3yEkx5WwsaYSENe" },
    { 61, "bhalkGXT0rQ3gMHuKP8N2bUoB1exf7LUr7qUMzF4LqtlY" },
    { 62, "NdJCkn6CycukcSVBZOOXSKVKFIJUTaxHRDzQfgkFrFGxM" },
    { 63, "GptdHNP58KNtfe+vxUbU6AtG1V8C9sIHikN4HuZxl9Lat" },
    { 64, "DVPR1lEyM2ev8FaaGG3c8v0g/F32uoNZn3tUeZ9dRxn7q" }
};

TEST_P(MultiDigitConsistencyTest, ConversionToAllBasesIsConsistent)
{
    auto [base, expected_output] = GetParam();

    std::string token_values;
    token_values_from_digits(INPUT_DIGITS, base,
                             token_values);

    EXPECT_EQ(expected_output, tokens_from_token_values(token_values, base));
}

INSTANTIATE_TEST_SUITE_P(
    StringFromDigitsTest,
    MultiDigitConsistencyTest,
    ::testing::ValuesIn(
        MultiDigitConsistencyTest::EQUIVALENT_MULTI_DIGIT_TOKENS_IN_ALL_BASES
    )
);

} // namespace
