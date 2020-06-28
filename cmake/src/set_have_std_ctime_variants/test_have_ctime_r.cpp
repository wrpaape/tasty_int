/**
 * @file "test_have_ctime_r.cpp"
 * CMake module set_have_std_ctime_variants will attempt to compile this file
 * to determine if the compiler has support for ctime_r.
 */

#include <ctime>

#include <iostream>


int
main()
{
    constexpr std::size_t TIMESTAMP_BUFFER_SIZE = 26;
    char timestamp_string[TIMESTAMP_BUFFER_SIZE]{};
    std::time_t timestamp{};

    (void) ::ctime_r(&timestamp, timestamp_string);

    std::cout << timestamp_string;

    return 0;
}
