/**
 * @file "test_intrinsic_count_leading_zero_bits.cpp"
 * This file will be used by the set_intrinsic_count_leading_zero_bits CMake
 * module to check for the existence of an intrinsic "count leading zero bits"
 * function which is compatible with `std::uintmax_t`.  A suitable function
 * will produce a successful compile and a return value of `0`.
 */

#include <cstdint>

#include <type_traits>

#ifdef INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
#   include INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
#endif // ifdef INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER

#define INTRINSIC_OPERAND_TYPE  \
        INTRINSIC_OPERAND_TYPE1 \
        INTRINSIC_OPERAND_TYPE2 \
        INTRINSIC_OPERAND_TYPE3


int
main(int   argc,
     char *argv[])
{
    (void) argv; // unused

    (void) INTRINSIC_COUNT_LEADING_ZERO_BITS(std::uintmax_t(argc)); // unused

    return !std::is_same_v<std::uintmax_t, INTRINSIC_OPERAND_TYPE>;
}
