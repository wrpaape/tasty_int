#include "tasty_int/detail/conversions/code_generator/table_generator.hpp"

#include <cctype>
#include <ctime>

#include <chrono>
#include <ostream>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {
namespace {

std::string
to_uppercase(std::string_view input)
{
    std::string uppercase;
    uppercase.reserve(input.size());
    for (char c : input)
        uppercase.push_back(std::toupper(c));

    return uppercase;
}

} // namespace


TableGenerator::TableGenerator(const TableConfig &table_config)
    : name(table_config.name)
    , uppercase_name(to_uppercase(name))
    , type(table_config.type)
    , type_header(table_config.type_header)
    , description(table_config.description)
    , num_entries(table_config.num_entries)
    , mapper(table_config.mapper)
{}

std::string_view
TableGenerator::get_table_name() const
{
    return name;
}

void
TableGenerator::generate_header(std::ostream &output) const
{
    put_generated_header(output);
    put_open_header_guard(output);
    output << '\n';
    put_include_type_header(output);
    output << "\n\n";
    put_open_namespaces(output);
    output << '\n';
    put_table_declaration(output);
    output << '\n';
    put_close_namespaces(output);
    output << '\n';
    put_close_header_guard(output);
}

void
TableGenerator::generate_source(std::ostream &output) const
{
    put_generated_header(output);
    output << '\n';
    put_include_header(output);
    output << "\n\n";
    put_open_namespaces(output);
    output << '\n';
    put_table_definition(output);
    output << '\n';
    put_close_namespaces(output);
}

void
TableGenerator::put_open_header_guard(std::ostream &output) const
{
    output <<
        "#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODEGEN_"
            << uppercase_name << "_HPP\n"
        "#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODEGEN_"
            << uppercase_name << "_HPP\n";
}

void
TableGenerator::put_include_type_header(std::ostream &output) const
{
    output << "#include " << type_header << '\n';
}

void
TableGenerator::put_table_declaration(std::ostream &output) const
{
    output <<
        "extern const " << type << " " << uppercase_name << ";\n";
}

void
TableGenerator::put_close_header_guard(std::ostream &output) const
{
    output <<
        "#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODEGEN_"
            << uppercase_name << "_HPP\n";
}

void
TableGenerator::put_generated_header(std::ostream &output) const
{
    auto time_now  = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(time_now);

#if HAVE_CTIME_S || HAVE_CTIME_R
    constexpr std::size_t TIMESTAMP_BUFFER_SIZE = 26;
    char timestamp_string[TIMESTAMP_BUFFER_SIZE]{};
#   if HAVE_CTIME_S
    (void) ::ctime_s(timestamp_string, sizeof(timestamp_string), &timestamp);
#   else
    (void) ::ctime_r(&timestamp, timestamp_string);
#   endif // if HAVE_CTIME_S
#else
    const char *timestamp_string = std::ctime(&timestamp);
#endif // if HAVE_CTIME_S || HAVE_CTIME_R

    output <<
        "// " << description << "\n"
        "//\n"
        "// generated on: " << timestamp_string // terminated with \n
     << "// =============================================================================\n";
}

void
TableGenerator::put_include_header(std::ostream &output) const
{
    output << "#include \"tasty_int/detail/conversions/codegen/" << name
           << ".hpp\"\n";
}

void
TableGenerator::put_table_definition(std::ostream &output) const
{
    output << "const " << type << " " << uppercase_name << " = {\n";
    put_table_entries(output);
    output << "};\n";
}

void
TableGenerator::put_table_entries(std::ostream &output) const
{
    for (std::size_t i = 0; i < num_entries; ++i) {
        output << "    /* " << i << " */ ";
        mapper(i, output);
        output << ",\n";
    }
}

void
TableGenerator::put_open_namespaces(std::ostream &output) const
{
    output <<
        "namespace tasty_int {\n"
        "namespace detail {\n"
        "namespace conversions {\n"
        "namespace codegen {\n";
}

void
TableGenerator::put_close_namespaces(std::ostream &output) const
{
    output <<
        "} // namespace codegen\n"
        "} // namespace conversions\n"
        "} // namespace detail\n"
        "} // namespace tasty_int\n";
}

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int
