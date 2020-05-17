/**
 * @file "llvm_cov_gcov.cpp"
 * CMake Module CodeCoverage will compile this file in the case that the llvm
 * toolchain is detected.  The resulting executable will do nothing more than
 * forward its input `argv` to the `llvm-cov` executable with the `gcov`
 * command prepended.  This is a workaround to lcov's requirement that a
 * `--gcov-tool` be specified with a single argument.
 */

#include <cstring>

#include <memory>

#ifndef TASTY_INT_LLVM_COV_PATH
#   error "Require path to llvm-cov!"
#endif // ifndef TASTY_INT_LLVM_COV_PATH
#ifndef TASTY_INT_EXECV_HEADER
#   error "Require path to header required for execv!"
#endif // ifndef TASTY_INT_EXECV_HEADER

#include TASTY_INT_EXECV_HEADER


namespace {

std::unique_ptr<char *[]>
make_child_argv(int   argc,
                char *argv[])
{
    std::size_t size_argv       = argc + 1;      // args + NULL-terminator
    std::size_t size_child_argv = size_argv + 1; // + "gcov"
    auto child_argv             = std::make_unique<char *[]>(size_child_argv);

    static char LLVM_COV_ARG[] = TASTY_INT_LLVM_COV_PATH;
    static char GCOV_ARG[]     = "gcov";
    child_argv[0] = LLVM_COV_ARG;
    child_argv[1] = GCOV_ARG;
    (void) std::memcpy(&child_argv[2],
                       &argv[1],
                       size_argv - 1); // exclude argv[0]

    return child_argv;
}

} // namespace


int
main(int   argc,
     char *argv[])
{
    auto child_argv = make_child_argv(argc, argv);

    return execv(TASTY_INT_LLVM_COV_PATH, child_argv.get());
}
