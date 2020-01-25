/**
 * @file "test_std_filesystem_library.cpp"
 * CMake module std_filesystem_library will attempt to compile this file with a
 * set of candidate compiler options to determine if the linker requires
 * additional libraries to support the C++17 std::filesystem library.
 */

#include <filesystem>


namespace {

bool
exists(const char *path)
{
    return path
        && std::filesystem::exists(std::filesystem::path(path));
}

} // namespace

int
main(int argc,
     char *argv[])
{
    (void) argc; // unused
    return argv
        && static_cast<int>(exists(argv[0]));
}
