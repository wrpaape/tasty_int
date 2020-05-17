#include "tasty_int/detail/conversions/digits_from_string.hpp"

#include <limits>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/test/base_support_test_common.hpp"
#include "tasty_int/detail/conversions/test/string_conversion_test_common.hpp"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::conversions::digits_from_string;
using base_support_test_common::unsupported_bases;
using string_conversion_test_common::StringViewConversionTestParam;


void
expect_single_digit_equals(digit_type                     value,
                           const std::vector<digit_type> &digits)
{
    EXPECT_EQ(value, digits.at(0));
    EXPECT_EQ(1,     digits.size());
}


class UnsupportedBaseTest : public ::testing::TestWithParam<unsigned int>
{}; // class UnsupportedBaseTest

TEST_P(UnsupportedBaseTest, UnsupportedBaseThrowsInvalidArgument)
{
    unsigned int unsupported_base = GetParam();
    try {
        (void) digits_from_string("123", unsupported_base);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int::detail::conversions::ensure_base_is_supported - invalid"
            " base (" << unsupported_base << "): Base is not within the range "
            "of supported values [2,64].";

        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    UnsupportedBaseTest,
    unsupported_bases()
);


struct InvalidTokenTestParam : public StringViewConversionTestParam
{
    char first_invalid_token;
}; // struct InvalidTokenTestParam

std::ostream &
operator<<(std::ostream                &output,
           const InvalidTokenTestParam &test_param)
{
    return output << "{ base=" << test_param.base << ", tokens=\""
                  << test_param.tokens << "\", first_invalid_token='"
                  << test_param.first_invalid_token << "' }";
}

class InvalidTokenTest : public ::testing::TestWithParam<InvalidTokenTestParam>
{}; // class InvalidTokenTest

TEST_P(InvalidTokenTest, InvalidTokenThrowsInvalidArgument)
{
    unsigned int base               = GetParam().base;
    std::string_view invalid_tokens = GetParam().tokens;
    char first_invalid_token        = GetParam().first_invalid_token;

    try {
        (void) digits_from_string(invalid_tokens, base);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int::detail::conversions::digits_from_string - invalid token"
            " ('" << first_invalid_token << "'): Token is not within the set of"
            " characters for specified base (" << base << ").";

        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    InvalidTokenTest,
    ::testing::ValuesIn(
        std::vector<InvalidTokenTestParam> {
            { {  2, "910101$"     }, '9' },
            { {  8, "076!543210"  }, '!' },
            { { 10, "+1234&56789" }, '+' },
            { { 16, "DEADBEEF*"   }, '*' },
            { { 36, "-123ab c"    }, '-' },
            { { 64, " ABCabc123_" }, ' ' }
        }
    )
);


class CommonBase36TokensTest : public ::testing::TestWithParam<unsigned int>
{}; // class CommonBase36TokensTest

TEST_P(CommonBase36TokensTest, SingleZeroInterprettedAsZero)
{
    auto base   = GetParam();
    auto digits = digits_from_string("0", base);

    expect_single_digit_equals(0, digits);
}

TEST_P(CommonBase36TokensTest, MultipleZerosInterprettedAsZero)
{
    auto base   = GetParam();
    auto digits = digits_from_string("00", base);

    expect_single_digit_equals(0, digits);
}

TEST_P(CommonBase36TokensTest, SingleOneInterprettedAsOne)
{
    auto base   = GetParam();
    auto digits = digits_from_string("1", base);

    expect_single_digit_equals(1, digits);
}

TEST_P(CommonBase36TokensTest, SingleOneWithLeadingZerosInterprettedAsOne)
{
    auto base   = GetParam();
    auto digits = digits_from_string("000000000000000000000000000000001", base);

    expect_single_digit_equals(1, digits);
}


INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    CommonBase36TokensTest,
    ::testing::Range<unsigned int>(2, 36)
);


class CommonBase64TokensTest : public ::testing::TestWithParam<unsigned int>
{}; // class CommonBase64TokensTest

TEST_P(CommonBase64TokensTest, SingleZeroInterprettedAsZero)
{
    auto base   = GetParam();
    auto digits = digits_from_string("A", base);

    expect_single_digit_equals(0, digits);
}

TEST_P(CommonBase64TokensTest, MultipleZerosInterprettedAsZero)
{
    auto base   = GetParam();
    auto digits = digits_from_string("AA", base);

    expect_single_digit_equals(0, digits);
}

TEST_P(CommonBase64TokensTest, SingleOneInterprettedAsOne)
{
    auto base   = GetParam();
    auto digits = digits_from_string("B", base);

    expect_single_digit_equals(1, digits);
}

TEST_P(CommonBase64TokensTest, SingleOneWithLeadingZerosInterprettedAsOne)
{
    auto base   = GetParam();
    auto digits = digits_from_string("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB", base);

    expect_single_digit_equals(1, digits);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    CommonBase64TokensTest,
    ::testing::Range<unsigned int>(36 + 1, 64)
);


const digit_type SINGLE_DIGIT_BASE_10              =  1234567890;
const std::string_view SINGLE_DIGIT_BASE_10_TOKENS = "1234567890";

auto
equivalent_single_digit_tokens_in_all_bases()
{
    static const std::vector<StringViewConversionTestParam> test_parameters = {
        { 2,  "1001001100101100000001011010010" },
        { 3,  "10012001001112202200" },
        { 4,  "1021211200023102" },
        { 5,  "10012022133030" },
        { 6,  "322301024030" },
        { 7,  "42410440203" },
        { 8,  "11145401322" },
        { 9,  "3161045680" },
        { 10, SINGLE_DIGIT_BASE_10_TOKENS },
        { 11, "583977146" },
        { 12, "2a5555016" },
        { 13, "168a0865a" },
        { 14, "b9d6b5aa" },
        { 15, "735b7d60" },
        { 16, "499602d2" },
        { 17, "30288g3a" },
        { 18, "20568ad0" },
        { 19, "174b57c7" },
        { 20, "j5g0jea" },
        { 21, "e8605e3" },
        { 22, "ajc3e26" },
        { 23, "87ifcgi" },
        { 24, "6b1230i" },
        { 25, "51ac8ff" },
        { 26, "3pnfhma" },
        { 27, "3511eki" },
        { 28, "2fkfbqa" },
        { 29, "225ep2g" },
        { 30, "1ko4m30" },
        { 31, "1c3ou0k" },
        { 32, "14pc0mi" },
        { 33, "vi0m56" },
        { 34, "r5spaa" },
        { 35, "nhokia" },
        { 36, "kf12oi" },
        { 37, "RdbBZb" },
        { 38, "PWDBia" },
        { 39, "NaZNbk" },
        { 40, "MCKElK" },
        { 41, "Kakgbn" },
        { 42, "JSfWRY" },
        { 43, "IREhnH" },
        { 44, "HVQqBG" },
        { 45, "GfDDHA" },
        { 46, "FthaIS" },
        { 47, "FSADpr" },
        { 48, "EobMkS" },
        { 49, "ESHgCD" },
        { 50, "DvabHo" },
        { 51, "DdYtMb" },
        { 52, "DMsKyK" },
        { 53, "CyYcVp" },
        { 54, "ClKRKS" },
        { 55, "CYyVhy" },
        { 56, "CNdz3K" },
        { 57, "CC2V2t" },
        { 58, "BzFcBQ" },
        { 59, "Bq0J5d" },
        { 60, "BjPjfe" },
        { 61, "BcKE21" },
        { 62, "BViHfU" },
        { 63, "BPXVnt" },
        { 64, "BJlgLS" }
    };

    return ::testing::ValuesIn(test_parameters);
}

class SingleDigitConsistencyTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{}; // class SingleDigitConsistencyTest

TEST_P(SingleDigitConsistencyTest, TheSameValueInDifferenceBases)
{
    auto [base, tokens] = GetParam();

    expect_single_digit_equals(SINGLE_DIGIT_BASE_10,
                               digits_from_string(tokens, base));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    SingleDigitConsistencyTest,
    equivalent_single_digit_tokens_in_all_bases()
);


const std::string_view MULTI_DIGIT_BASE_10_TOKENS = "11"
                                                    "2222"
                                                    "333333"
                                                    "44444444"
                                                    "5555555555"
                                                    "666666666666"
                                                    "77777777777777"
                                                    "8888888888888888"
                                                    "999999999999999999"
                                                    "00000000000000000000";

auto
equivalent_multi_digit_tokens_in_all_bases()
{
    static const std::vector<StringViewConversionTestParam> test_parameters = {
        {  2, "100110001110100010000001001000000110100001110111010110010011110100001010000011011001011010111000000110110100010010111101101011100101101010111111101101000100110000110000011000111010000010110100010001100001010111110000100001000000111101011010001011000111111010001000011010110111100100000010111010100001100000111111001110000100001001010011100111100000000000000000000" },
        {  3, "1211212100200102012002112100210010002110220002111021020221110202112020000012211110010211212102201100201022102111200112122200110111200210010022100220210121022002221221020012220210011221010222202100201201012102112101011222022002010" },
        {  4, "10301310100021000310032322302132201100123023113000312202113231130231113331220212012003013100112202030022332010020013223101120333101003112330200113110030013321300201022130330000000000" },
        {  5, "1003031423131030313431014032141311344342433211311202424110434401220301122424344000204412210322203232130021031143242133044444444421242114400000000000000000000" },
        {  6, "114132104031400551404452240543204334024525253441343515241453332051435200341400502445420141522422511301121122114440215343205035501513034252520" },
        {  7, "1035411063461310623231402044235663525553022225503465343664124336026214665442206126601146201626163326331302233266105403532526203302" },
        {  8, "4616420110064167262364120331327006642275534552775504606030720264214127604100753213077210326744027241407716041123474000000" },
        {  9, "1755320365075323102426074236843675200184403755381321272450478613450703270823538087836186704833882321635375334868063" },
        { 10, MULTI_DIGIT_BASE_10_TOKENS },
        { 11, "56201a376507a07978818927a039885454aa96057549770380627832305696a74610771707a04644979a66277041590761962a1a0" },
        { 12, "116732914a7a794a87b567915990b2b619a1174a8bb856b9b807b83346385a92b05a16697005b6088a64406147b6372b287140" },
        { 13, "9c3781201a1b7c6737bbc89b2cc82c512376165b987c44781682c345621ba34a28c15a8350aa865115487b3b7b247b3c66" },
        { 14, "168735981c8857a017c3c5003c9711cbd2ad1b3538c6916c76226b5bdb8ba42395c98d8b0884479db891d553aa545972" },
        { 15, "711ab663b3a433b4737a68e71b0928a2a1eb67b04bbd1713158acc21e2bd2e1398827389dae603542552ceabadd50" },
        { 16, "4c744090343bac9e8506cb5c0da25ed72d5fda261831d05a230af84207ad163f4435bc81750c1f9c2129cf00000" },
        { 17, "5f402d8f944faf9e6c34b4ec9gbccg0cb67f1700744da60g1b91600ded6d352cfbf13387g2c309eeb0d8f356e" },
        { 18, "c8f9612da2h36fa9h7b9dcgce48f53g077f833h248446dd72806543ae2224hed1c0005dah3cdf694c09hfgc" },
        { 19, "2528fg9e275e399ebg91292dd6ca3i77797h5f17a2g16bd83g9289b7aa56geab67fidgi99ga354g1g5f4h8" },
        { 20, "bc182f78c8h8j8b8i7hj0ai7hjg5f153add6i43c6248e158g40f845fihi2e7hg4jjjgij5if0000000000" },
        { 21, "453kh1df1f8cha3i7kjfd80d1219k35cjc6b66gdkb72d8kdhjii0aebcdb26ekdi0ba2fhjcdi06ibfjg9" },
        { 22, "216ldb0dga560hdfljdd5cg0hbc77f0d1h1dbb299dle1f5c1jd65j5a4kh50hkg0l4ikhk4legglig8g0" },
        { 23, "16h9301b70je5kck0k3icj28jia4a409h6ihcd01kbjc7hci69jj48e2l686941id262h3b2jlejb0em5" },
        { 24, "10i0lb0742nkjbaem6940j16aiclg9en4gfah1e083le0ee9443j519b542755k84n2hdm2kj1750l80" },
        { 25, "10fgmgg338n593blg8ojeib86aee64jk7af6cmno024lc5hc3dbf25g9hm8foooom7m6o0000000000" },
        { 26, "16db5a5ie2f60010p0on4ldfj51ghc75a678i083d0o9nn0864ooal20j19f9bfghp13noo27p2336" },
        { 27, "1mn9ib52e9l32co2d76pcke605mc3mnbj9j8bdiehicdil389olg82pp65ol4p3qk9jj5bea4q823" },
        { 28, "377p1illqc9ogjl0l2o2fg5kqf9r4oc98pd77fkmdb9iid8mkbb4aifh959lfo4ac5cop3if45og" },
        { 29, "6n7adk502inhdhmho49bsbhcg8klccfj95epm57k2s7cqsagde3n8brjbrl91q06r1rdk68kq6j" },
        { 30, "gi43dmlap54tdsahp6nai5cftj2r7bhn2g5rtsl7tm329s8d14nf10rtnf5bf1qei8i4pkb3a0" },
        { 31, "1fuolroits0hsfk6cahnrhtbo013k6l6bhlqp1qmro0a1nhmja8efe58ghr9o75kcu3gti95st" },
        { 32, "4ot20i0q3nb4ugk3cmn0dk9fdebavr8j1gcegb8hglu220umhcfq46mu82t8c3ue22aef0000" },
        { 33, "h6mectant9vbgirf4jeo04qvf0ehod6rwbsn30ma7unss6ve2v75s1vqjm8djwuaijg94et0" },
        { 34, "227xw29wxscmrgshxdgboi27phq8q2mo6k9jjm5be3two8qq8doo6ltfhl55uwac24fn8v3e" },
        { 35, "984pkk2mffajsp85ybmeckxp615il6sbofqbhan2pn3rh11t4us5ksjqx2hx79s4vj8m92u" },
        { 36, "1a9d43a0za4teoyk4logwwxs9rvwptlk5anc3po52sycabeqh7i7d8das2bmk53z1vimhhc" },
        { 37, "GkQMJPMBTeCUbQSOCKdcQaTLGMTCDjQZEffJFEXWZRhENfMcVgAKWPFEChXcchPbBSWARE" },
        { 38, "BEFaHWbPaRZfAhHJkZhPDicflNcIaieVYfiVjPNOAdOgQENELkQLIIlDRkRlPVJMSiePSI" },
        { 39, "HIBEXTZAeQcKdEWfYVKjbLiAQOcAHXhicgdCQKZWbamDcmbLFCWlWIRkYmjTUPdgeFkCG" },
        { 40, "BLVHlmifLgaRnhfenFNYhfbhmAUZCcmaUmlkckPiDeJNBFnTWfUihHVWOBXKKlUAAAAAA" },
        { 41, "JinYeaAJZHEAoQPYWVCeQMjgZiJKbOFnCEjcQVPCQlZgnPdbcMJjihbOgYPMmVfUiCoB" },
        { 42, "BoOQkOhkTLUQpGPUeZaSMTEXgCoTRICjSMDfYBoXgGBHlKlXgLRMcIpPiCIcZmidZZne" },
        { 43, "RSKpZcHoCaHLWlFnSOedfdVmELEoWbXUUUOqYDWbfVYqfhZYMgVILqXokefEJgCjQqR" },
        { 44, "DkFnLOCSHHbjCVAOSeSaTaXAnmfVeIXZMWKgjaFCOYgDrQEoMboHRPBaGRoPpWeCCIA" },
        { 45, "nAkbZkVeTGmXssqDHslnGXopFDpfpjWQpceBjSmcLUJsCJZKBCWakrkOiffXkrMhGe" },
        { 46, "JQEterQAqpnfhXTfSVOsGfRNsRIeScQVAAgYifUpmlXhJeNrbaHNJkiXbQgHCjIgWc" },
        { 47, "COcBtqcVQVDbagcETscdsZBEiMLHHkdabknssuMQepFkbqXlETcZFaVQaiZXhcrtGg" },
        { 48, "cKnPTsgRMrcPOUcPsDnrYlSAQeSRAakUMNSjikqUtpblsGoCnaETokAqfkrGunFQA" },
        { 49, "HadHtiKHsXWcOgRptlomCQTjZvZbuJfbCsLwneOrUqIiONUNYUYKCRXwHnDmTUOYC" },
        { 50, "CDZREGxQDhusoujGpqxhTEnAenWEQUUWLHvEGDFbmsWiUfxxxxxxxdaAAAAAAAAAA" },
        { 51, "dlFJtrJYuODaOOpbNxBklRqesGJAVwFJXfyrHJOhaygDqGPXllfPbEjYtRAwMkYw" },
        { 52, "ImsVGvrHNFqYfOjDXYSwPbRRGaEPbbQaYKFlsArRhigLwHJlupmDeqLtkRvTXAog" },
        { 53, "ChhRhmvfaOMFWZJlEQwHTaWpZYjhLgIZPefnEFlHpCqmnFwqkgCsyjWSYLISnfOX" },
        { 54, "rsNQJBWMuLoqdrF0sXWUnKObERCsLtNWMRYRK1JahbCaxyaLGAUZIfqQ0GMGjpe" },
        { 55, "OChCvPLvw2dFVXWvFsmbfLgzZDGcCBQYceWvsqnzeKlgMJgTmqXymTob1cBTrjA" },
        { 56, "EhWYZTkCDMknPbLdJ0pLulv1XX2irHrh0VkRVDIrJkPyllCP3v1EQpXoY3nZBaQ" },
        { 57, "BeZGbyvvlpVKennVDacLyg2CtZorPBzjiqvkcmvjvVPLeVvLOfDNiOWJ2YEDVlb" },
        { 58, "ePcqSa4BdOc1W1hK3SrDrry1FSrFSULmh4sZuIx3zpxEHOAnoQfnYUwiRYGNuw" },
        { 59, "KnaTHFVOEOTmXwPWYd0Wc1AHjMMkFg1b40MfQQSmMspBaAbmznCI0ZiCIUzZmW" },
        { 60, "DxlBmjYLpxJCSwzyarW46WJozJYITiqGEO7BfyuePz7Mg40k0ircda7MPwI1UA" },
        { 61, "BYKYaHZeHQRjqUVf6OZKr10yCsnyvqvazpJY8Vgbm0QgxcvLluUZgXDsQo58Bo" },
        { 62, "gGhG6Q0YxbtulanR7nKjtNSsGN78DG3wZf3clLfwHUadMzTpHT1cDnBOeMv88" },
        { 63, "MSbm+gL4tMo9YwQj7H5F1UlVX5FgvKZXJfTtlxoCKDl236ilieGE4Wvs6eJMe" },
        { 64, "Ex0QJA0O6yehQbLXA2iXtctX9omGDHQWiMK+EIHrRY/RDW8gXUMH5whKc8AAA" }
    };

    return ::testing::ValuesIn(test_parameters);
}

class MultiDigitConsistencyTest
    : public ::testing::TestWithParam<StringViewConversionTestParam>
{}; // class MultiDigitConsistencyTest

TEST_P(MultiDigitConsistencyTest, TheSameValueInDifferenceBases)
{
    auto [base, tokens] = GetParam();

    EXPECT_EQ(digits_from_string(MULTI_DIGIT_BASE_10_TOKENS, 10),
              digits_from_string(tokens,                     base));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromStringTest,
    MultiDigitConsistencyTest,
    equivalent_multi_digit_tokens_in_all_bases()
);

} // namespace
