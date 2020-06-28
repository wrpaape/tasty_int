/**
 * @file "test_enable_cpp_concepts.cpp"
 * CMake module enable_cpp_concepts will attempt to compile this file with a
 * set of candidate compiler options to determine if the compiler requires any
 * options to enable support for C++20 concepts.
 */

#include <type_traits>


namespace {

template<typename T>
T
square(T value)
    requires std::is_arithmetic_v<T>
{
    return value * value;
}

} // namespace

int
main(int   argc,
     char *argv[])
{
    (void) argv; // unused

    return square(argc);
}
