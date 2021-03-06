/**
 * @file generate_digits_per_token_table.cpp
 * This program generates the source code for a lookup table used for
 * converting a string of tokens to an array of digits.
 */
#include <cmath>

#include <limits>
#include <ostream>

#include "tasty_int/detail/digit_type.hpp"
#include "tasty_int/detail/conversions/code_generator/parse_code_generator_arguments.hpp"
#include "tasty_int/detail/conversions/code_generator/generate_table_files.hpp"


namespace {

float
calculate_digits_per_token_base(std::size_t base)
{
    constexpr float LOG2_DIGIT_BASE = tasty_int::detail::DIGIT_TYPE_BITS;

    return std::log2(static_cast<float>(base)) / LOG2_DIGIT_BASE;
}

template<typename T>
constexpr auto
print_precision()
{
    // The value of std::numeric_limits<T>::max_digits10 is the number of
    // base-10 digits that are necessary to uniquely represent all distinct
    // values of the type T, such as necessary for
    // serialization/deserialization to text.
    // (https://en.cppreference.com/w/cpp/types/numeric_limits/max_digits10)
    return std::numeric_limits<T>::max_digits10;
}

void
print_digits_per_token_base(float         digits_per_token_base,
                            std::ostream &output)
{
    auto original_precision = output.precision();
    auto original_flags     = output.flags();

    output.precision(print_precision<decltype(digits_per_token_base)>());
    output.flags(original_flags | std::ios_base::showpoint);

    output << digits_per_token_base << 'f';

    output.flags(original_flags);
    output.precision(original_precision);
}

void
print_entry(std::size_t   entry,
            std::ostream &output)
{
    float digits_per_token_base = 0.0; // default for invalid entries

    if (entry >= 2)
        digits_per_token_base = calculate_digits_per_token_base(entry);

    print_digits_per_token_base(digits_per_token_base, output);
}

} // namespace


int
main(int   argc,
     char *argv[])
{
    using tasty_int::detail::conversions::code_generator::parse_code_generator_arguments;
    using tasty_int::detail::conversions::code_generator::TableGenerator;
    using tasty_int::detail::conversions::code_generator::generate_table_files;

    auto args = parse_code_generator_arguments(argc, argv);

    TableGenerator digits_per_token_table_generator({
        .name        = args.target_name,
        .type        = "std::array<float, 65>",
        .type_header = "<array>",
        .description = "This table helps determine the number of elements "
                       "required to convert a string of tokens to an array of "
                       "digits.",
        .num_entries = 65,
        .mapper      = print_entry
    });

    generate_table_files(digits_per_token_table_generator,
                         args.output_directory);

    return 0;
}
