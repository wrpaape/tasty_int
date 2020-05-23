[![Build Status](https://travis-ci.org/wrpaape/tasty_int.png?branch=master)](https://travis-ci.org/wrpaape/tasty_int)
[![Coverage Status](https://coveralls.io/repos/github/wrpaape/tasty_int/badge.png?branch=master)](https://coveralls.io/github/wrpaape/tasty_int?branch=master&service=github)

# TastyInt


## Overview

- [Prerequisites](#prerequisites)
- [Configure](#configure)
- [Build](#build)
- [Usage](#usage)
- [Interface](#interface)
- [Implementation](#implementation)


Simple Big Integer library.


## Prerequisites
### Minimal
- `cmake >= 3.12`
- an adequately C++20-compliant compiler:
    - `gcc >= 8`
    - `clang >= 10`
### Documentation
- `doxygen >= 1.8`
- `graphviz (dot) >= 1.5`
### Coverage Report
- `lcov >= 1.14`

## Configure
```
cd build
cmake [options] ..
```
where suggested `options` are:

#### `-DCMAKE_BUILD_TYPE:STRING=<Debug|Release|Release|RelWithDebInfo|MinSizeRel>`
Select the project build type.  Default is `Debug`.

#### `-DCMAKE_INSTALL_PREFIX:STRING=<destination directory>`
If [`cmake --build . install`](#install) is invoked, this directory is
prepended onto all install directories. This variable defaults to `/usr/local`
on UNIX and `c:/Program Files` on Windows.

#### `-DBUILD_TESTING:BOOL=<ON|OFF>`
Requires `git` and configure-time internet access for cloning [google
test](https://github.com/google/googletest).

#### `-DBUILD_COVERAGE:BOOL=<ON|OFF>`
Enable units tests (see [`[build-]test[-verbose]`](#build-test-verbose)
build targets).
Requires `lcov` and `-DBUILD_TESTING:BOOL=ON`.
Suggest `-DCMAKE_BUILD_TYPE:STRING=Debug` for a coverage report that
corresponds intuitively to the source code.

#### `-DBUILD_BENCHMARKING:BOOL=<ON|OFF>`
Enable development benchmarks (see the [`benchmark`](#benchmark) build target).
Requires `git` and configure-time internet access for cloning [google
benchmark](https://github.com/google/benchmark).


## Build
```
cd build
cmake --build . [build-options] [--target <tasty_int-targets>]
```
where suggested `build-options` are:

#### `--parallel [<jobs>], -j [<jobs>]`
The maximum number of concurrent processes to use when building.  If `<jobs>`
is omitted the native build tool's default number is used.

and `tasty_int-targets` is a space-separated list of the following build targets:

#### `all`
Build all [configured](#configure) targets

#### `clean`
Remove all build artifacts.

#### `install`
Build and install `tasty_int` libraries and headers at `CMAKE_INSTALL_PREFIX`

#### `[build-]test[-verbose]`
Run all unit tests. The `build-` prefix will ensure that tests are first built
and up to date, and the `-verbose` suffix will show individual test output.

#### `coverage`
Generate test coverage report.  This target will build and run all unit tests
and generate an html coverage report at `build/coverage/index.hml`.

#### `benchmark`
Build and run development benchmarks.

#### `docs`
Generate `tasty_int`'s documentation.  The html output can be found at
`docs/Doxygen/html/index.html`.


## Usage
1. Install `TastyInt`.
```
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Release \
      -DBUILD_TESTING:BOOL=ON           \
      -DBUILD_COVERAGE:BOOL=OFF         \
      -DBUILD_BENCHMARKING:BOOL=OFF     \
      ..
cmake --build . --parallel --target build-test
cmake --build . --parallel --target install
```

2. Add `TastyInt` to your C++20 project.
```
project(big_fact)
...
set(CMAKE_CXX_STANDARD 20)
...
find_package(TastyInt REQUIRED)
...
target_link_libraries(big_fact TastyInt::TastyInt)
```

3. Include `TastyInt`.
```
#include <iostream>
#include <string>

#include <tasty_int/tasty_int.hpp>

int
main(int   argc,
     char *argv[])
{
    if (argc != 2) {
        std::cerr << argv[0] << " <N>: calculate N!\n";
        std::exit(1);
    }

    tasty_int::TastyInt fact(1);

    for (auto n = std::stoll(argv[1]); n > 1; --n)
        fact *= n;

    std::cout << fact << '\n';

    return 0;
}
```


## Interface

- [Construction](#construction)
- [Comparison](#comparison)
- [Arithmetic](#arithmetic)
- [Output](#output)


### Construction
```
using tasty_int::TastyInt;
...
TastyInt num; // defaults to 0
...
num = -123;
...
num = 10.0e100;
...
// base is interpretted...
num = TastyInt("010101011010111110000001110011b"); // binary
num = TastyInt("12345678901234567890123456789012345678901234567890"); // decimal
num = TastyInt("0012345670123456701234567012345670123456701234567"); // octal
num = TastyInt("0xFACEFEEDDEADBEEFDECAFBADBABEFACEFEEDDEADBEEF"); // hexidecimal
...
// ...or explicit
TastyInt num("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", 64);
```
See `TastyInt Constructors` section of
[tasty_int.hpp](include/tasty_int/tasty_int.hpp) for more details.


### Comparison
Comparison operations consist of at least one `TastyInt` operand and either
another `TastyInt` or an [arithmetic
type](https://en.cppreference.com/w/cpp/types/is_arithmetic).  Operations
consist of [constrained
](https://en.cppreference.com/w/cpp/language/constraints) overloads for
operators `==`, `!=`, `<`, `>`, `<=`, and `>=`.
```
using tasty_int::TastyInt;
...
auto num = TastyInt(std::numeric_limits<long double>::max());
...
if (std::numeric_limits<int>::max() < num)
    std::cout << "expected\n";
...
if ((num * num) >= num)
    std::cout << "also expected\n";
...
```
See the `TastyInt Comparison Operators` section
of [tasty_int.ipp](include/tasty_int/tasty_int.ipp) for more details.

### Arithmetic
Arithmetic operations consist of at least one `TastyInt` operand and either
another `TastyInt` or an [arithmetic
type](https://en.cppreference.com/w/cpp/types/is_arithmetic).  Operations
consist of [constrained
](https://en.cppreference.com/w/cpp/language/constraints) overloads for
operators `+=`, `-=`, `*=`, `/=`, `%=`, `+`, `-`, `*`, `/`, `%`, `++`
(pre/post), `--` (pre/post), and `div()`, which emulates `std::div()`.
```
using tasty_int::TastyInt;
...
auto num = TastyInt("abc123doremi", 64);
...
num += std::numeric_limits<std::uintmax_t>::max();
...
auto prev = num++;
...
num -= 3.14159;
...
while (--num > 0)
    std::cout << num << " bottles of beer on the wall.\n";
...
num *= TastyInt(std::string(9000, '9'));
...
num /= TastyInt("07777777777777777777777777777777777777777777777777");
...
num %= 42;
...
auto [quotient, remainder] = num.div(13);
...
auto result = 010101010101b + num;
...
result = num - 1.0e111;
...
result = num * num;
...
result = 5.5 / num;
...
result = num % TastyInt("170141183460469231731687303715884105727");
...
auto [quotient, remainder] = tasty_int::div(result, num);
...
```
See the `TastyInt <Addition|Subtraction|Multiplication|Division|Modulo>`
sections of [tasty_int.ipp](include/tasty_int/tasty_int.ipp) for more details.

### Output
`TastyInt` instances may be written to a `std::ostream` or converted to an
ASCII string with the `to_string()` member function.
```
#include <iomanip>
...
using tasty_int::TastyInt;
...
TastyInt num(7777777777777777777777777777777777777777777777777777777777777777);
...
std::cout << "decimal:                   " << num << '\n'
          << "decimal (explicit):        " << std::dec << num << '\n'
          << "decimal (with +):          " << std::showpos << num << '\n'
          << "octal:                     " << std::oct << num << '\n'
          << "hexidecimal:               " << std::hex << num << '\n'
          << "hexidecimal (with prefix): " << std::showbase << num << '\n';
...
if (num > std::numeric_limits<std::uintmax_t>::max())
    throw std::runtime_error("Integer overflow detected: " + num.to_string(64));
```
See documentation of `to_string()` and `operator<<` at their definitions in
[tasty_int.hpp](include/tasty_int/tasty_int.hpp) and
[tasty_int.ipp](include/tasty_int/tasty_int.ipp) respectively for more details.


## Implementation
At the heart of `TastyInt` is a [simple data
structure](tasty_int/include/tasty_int/detail/integer.hpp) which consists of a
dynamic array of (usually-)half-word-base `digits` along with an enumerated
`sign` field to indicate `POSTIVE`, `NEGATIVE`, or `ZERO`.  `digits` are stored
in little-endian order of significance.  For example, the base-10 number

    1,234,567

would be stored in memory as

    [7, 6, 5, 4, 3, 2, 1]

on some imaginary target hardware with a word size that necessitated a base-10
digit.  On the ubiquitous x86-64 architecture, the sequence of `digits`

    [digit1, digit2, ... digitN]

represents the summation of the power series

    32^0*digit1 + 32^1*digit2 + ... 32^(N-1)*digitN

As you can see, the domain of representable values can quickly grow very large with 
the addition of `int`-sized digits to the sequence.
Throw in a flag to indicate `sign` and you have an efficient way to represent
large integers.
