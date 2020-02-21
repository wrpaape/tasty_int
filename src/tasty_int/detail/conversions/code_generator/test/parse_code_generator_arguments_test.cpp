#include "tasty_int/detail/conversions/code_generator/parse_code_generator_arguments.hpp"

#include <cstdlib>

#include "gtest/gtest.h"


namespace {
 
using tasty_int::detail::conversions::code_generator::parse_code_generator_arguments;
using tasty_int::detail::conversions::code_generator::CodeGeneratorArguments;


TEST(ParseCodeGeneratorArgumentsTest,
     PrintsUsageWithDefaultProgramIfNoArgumentsSupplied)
{
    int argc     = 0;
    char *argv[] = { nullptr };

    EXPECT_EXIT(
        parse_code_generator_arguments(argc, argv),
        ::testing::ExitedWithCode(EXIT_FAILURE),
        "<code generator> <target name> <path to output directory>"
    );
}

TEST(ParseCodeGeneratorArgumentsTest,
     PrintsUsageWithProvidedProgramIfNoTargetNameSupplied)
{
    int argc       = 1;
    char program[] = "./test_generator";
    char *argv[]   = { program, nullptr };

    EXPECT_EXIT(
        parse_code_generator_arguments(argc, argv),
        ::testing::ExitedWithCode(EXIT_FAILURE),
        "./test_generator <target name> <path to output directory>"
    );
}

TEST(ParseCodeGeneratorArgumentsTest,
     PrintsUsageWithProvidedProgramIfNoOutputDirectorySupplied)
{
    int argc           = 2;
    char program[]     = "./test_generator";
    char target_name[] = "test_target_name";
    char *argv[]       = { program, target_name, nullptr };

    EXPECT_EXIT(
        parse_code_generator_arguments(argc, argv),
        ::testing::ExitedWithCode(EXIT_FAILURE),
        "./test_generator <target name> <path to output directory>"
    );
}

TEST(ParseCodeGeneratorArgumentsTest, ParsesWellFormedCodeGeneratorArguments)
{
    int argc                = 3;
    char program[]          = "./test_generator";
    char target_name[]      = "test_target_name";
    char output_directory[] = "path/to/output_directory";
    char *argv[]            = {
        program, target_name, output_directory, nullptr
    };

    CodeGeneratorArguments parsed_argumets =
        parse_code_generator_arguments(argc, argv);

    EXPECT_EQ("test_target_name",         parsed_argumets.target_name);
    EXPECT_EQ("path/to/output_directory", parsed_argumets.output_directory);
}

} // namespace
