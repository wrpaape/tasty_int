#define tasty_int_VERSION_MAJOR @tasty_int_VERSION_MAJOR@
#define tasty_int_VERSION_MINOR @tasty_int_VERSION_MINOR@

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>   // std::vector
#include <string>   // std::string
#include <iostream> // std::[i|o]stream
#include <cstdint>  // UINT_MAX, uintmax_t
#include <climits>  // U[LONG|INT|SHRT]_MAX


// Interface
// =============================================================================
class TastyInt
{
// Friends
// -----------------------------------------------------------------------------
    // arithmetic
    friend TastyInt &operator+(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator-(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator*(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator/(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator<<(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator>>(const TastyInt &lhs, const TastyInt &rhs);
    // comparison
    friend int compare(const TastyInt &lhs, const TastyInt &rhs);
    // IO
    friend std::ostream &operator<<(std::ostream &os, const TastyInt &x);
    friend std::istream &operator>>(std::ostream &is, const TastyInt &x);

// Members
// -----------------------------------------------------------------------------
public:
    // constructors
    TastyInt();
    TastyInt(const TastyInt &other) = default;
    TastyInt &operator=(const TastyInt &other) = default;
    TastyInt(const TastyInt &&other) = default;
    // arithmetic
    TastyInt &operator+=(const TastyInt &other);
    TastyInt &operator-=(const TastyInt &other);
    TastyInt &operator*=(const TastyInt &other);
    TastyInt &operator/=(const TastyInt &other);
    TastyInt &operator<<=(const TastyInt &other);
    TastyInt &operator>>=(const TastyInt &other);
    // comparison
    bool operator==(const TastyInt &other) const;
    bool operator!=(const TastyInt &other) const;
    bool operator<=(const TastyInt &other) const;
    bool operator>=(const TastyInt &other) const;
    bool operator<(const TastyInt &other) const;
    bool operator>(const TastyInt &other) const;

private:
    // types
    //
    // digit_type: unsigned integer, atomic unit of arithmetic
    // acc_type:   large enough to hold the result of
    //             'digit_type_max X digit_type_max'
    typedef uintmax_t acc_type;
#if   (UINTMAX_MAX > ULONG_MAX)
    typedef unsigned long  digit_type;
#elif (UINTMAX_MAX > UINT_MAX)
    typedef unsigned int   digit_type;
#elif (UINTMAX_MAX > USHRT_MAX)
    typedef unsigned short digit_type;
#else
    typedef unsigned char  digit_type; // all integers same size
#endif // if (UINT_MAX == ULONG_MAX)

    // constants
    static const acc_type acc_type_max;
    static const acc_type digit_type_max; // floor(sqrt(acc_type_max))

    // instance data
    std::vector<digit_type> digits;
    bool is_negative;
}
