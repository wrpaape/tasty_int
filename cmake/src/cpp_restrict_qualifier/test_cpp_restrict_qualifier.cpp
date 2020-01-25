/**
 * @file "test_cpp_restrict_qualifier.cpp"
 * CMake module cpp_restrict_qualifier will attempt to compile this file with
 * -DCPP_RESTRICT_QUALIFIER=<QUALIFIER> to determine C++ compiler support for
 *  the 'restrict' keyword.
 */

namespace {

int
set_and_add(int *CPP_RESTRICT_QUALIFIER ptr1,
            int *CPP_RESTRICT_QUALIFIER ptr2)
{
    *ptr1 += *ptr2;
    return *ptr1 + *ptr2;
}

} // namespace

int
main(int argc,
     char *argv[])
{
    static int zero = 0;

    return set_and_add(&argc,
                       &zero);
}
