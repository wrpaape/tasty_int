#include "tasty_int/tasty_int.hpp"
#include <limits>
#include <type_traits>


// Static Constants
// -----------------------------------------------------------------------------
unsigned int TastyInt::global_default_base = 10;
// TastyInt::digit_type_max((1ULL << (sizeof(TastyInt::acc_type) / 2)) - 1ULL);

#define X 0xff
const unsigned char __gmp_digit_value_tab[] =
{
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, X, X, X, X, X, X,
  X,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
  25,26,27,28,29,30,31,32,33,34,35,X, X, X, X, X,
  X,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
  25,26,27,28,29,30,31,32,33,34,35,X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, X, X, X, X, X, X,
  X,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,
  25,26,27,28,29,30,31,32,33,34,35,X, X, X, X, X,
  X,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,
  51,52,53,54,55,56,57,58,59,60,61,X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
  X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X
};


const unsigned char base_64_token_values[] = {
    ['A'] =  0, ['Q'] = 16, ['g'] = 32, ['w'] = 48,
    ['B'] =  1, ['R'] = 17, ['h'] = 33, ['x'] = 49,
    ['C'] =  2, ['S'] = 18, ['i'] = 34, ['y'] = 50,
    ['D'] =  3, ['T'] = 19, ['j'] = 35, ['z'] = 51,
    ['E'] =  4, ['U'] = 20, ['k'] = 36, ['0'] = 52,
    ['F'] =  5, ['V'] = 21, ['l'] = 37, ['1'] = 53,
    ['G'] =  6, ['W'] = 22, ['m'] = 38, ['2'] = 54,
    ['H'] =  7, ['X'] = 23, ['n'] = 39, ['3'] = 55,
    ['I'] =  8, ['Y'] = 24, ['o'] = 40, ['4'] = 56,
    ['J'] =  9, ['Z'] = 25, ['p'] = 41, ['5'] = 57,
    ['K'] = 10, ['a'] = 26, ['q'] = 42, ['6'] = 58,
    ['L'] = 11, ['b'] = 27, ['r'] = 43, ['7'] = 59,
    ['M'] = 12, ['c'] = 28, ['s'] = 44, ['8'] = 60,
    ['N'] = 13, ['d'] = 29, ['t'] = 45, ['9'] = 61,
    ['O'] = 14, ['e'] = 30, ['u'] = 46, ['+'] = 62,
    ['P'] = 15, ['f'] = 31, ['v'] = 47, ['/'] = 63
};
