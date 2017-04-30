#define tasty_int_VERSION_MAJOR @tasty_int_VERSION_MAJOR@
#define tasty_int_VERSION_MINOR @tasty_int_VERSION_MINOR@

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>      // std::vector
#include <string>      // std::string
#include <iostream>    // std::[i|o]stream
#include <cstdint>     // std::uintmax_t
#include <type_traits> // std::conditional


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
    // bitwise
    friend TastyInt &operator&(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator&(const TastyInt &lhs, const TastyInt &rhs);
    // comparison
    friend int compare(const TastyInt &lhs, const TastyInt &rhs);
    // IO
    friend std::ostream &operator<<(std::ostream &os, const TastyInt &x);
    friend std::istream &operator>>(std::ostream &is, const TastyInt &x);

// Members
// -----------------------------------------------------------------------------
public:
    // constructors
    TastyInt();                                // default
    TastyInt(const TastyInt &other);           // copy
    TastyInt(const TastyInt &&other) noexcept; // move
    // destructor
    ~TastyInt() noexcept;
    // assignment
    TastyInt &operator=(const TastyInt &other);           // copy
    TastyInt &operator=(const TastyInt &&other) noexcept; // move
    // swap
    void swap(TastyInt &other) noexcept;
    // arithmetic
    TastyInt &operator+=(const TastyInt &other);
    TastyInt &operator-=(const TastyInt &other);
    TastyInt &operator*=(const TastyInt &other);
    TastyInt &operator/=(const TastyInt &other);
    TastyInt &operator%=(const TastyInt &other);
    TastyInt operator+() const;
    TastyInt operator-() const;
    // bitwise
    TastyInt &operator<<=(const TastyInt &other);
    TastyInt &operator>>=(const TastyInt &other);
    TastyInt &operator&=(const TastyInt &other);
    TastyInt &operator|=(const TastyInt &other);
    TastyInt &operator^=(const TastyInt &other);
    TastyInt operator~() const;
    // conditional
    explicit operator bool() const;
    explicit operator!() const;
    // comparison
    bool operator==(const TastyInt &other) const;
    bool operator!=(const TastyInt &other) const;
    bool operator<=(const TastyInt &other) const;
    bool operator>=(const TastyInt &other) const;
    bool operator<(const TastyInt &other) const;
    bool operator>(const TastyInt &other) const;
    // string operations
    std::string to_string(const unsigned int base = 10) const;

private:
    // types
    //
    // digit_type
    //      unsigned integer, atomic unit of arithmetic
    // acc_type
    //      large enough to hold the result of
    //      digit_type_max * digit_type_max
    //      also
    //      sizeof(digit_type) * 2 >= sizeof(acc_type)
    //      -> 2 digits guaranteed to hold 1 acc
    typedef std::uintmax_t acc_type;
    typedef std::conditional<sizeof(unsigned char)      * 2 >= sizeof(acc_type),
                unsigned char,
            std::conditional<sizeof(unsigned short)     * 2 >= sizeof(acc_type),
                unsigned short,
            std::conditional<sizeof(unsigned int)       * 2 >= sizeof(acc_type),
                unsigned int,
            std::conditional<sizeof(unsigned long)      * 2 >= sizeof(acc_type),
                unsigned long,
            std::conditional<sizeof(unsigned long long) * 2 >= sizeof(acc_type),
                unsigned long,
                // no integer type smaller than acc_type that can express
                // an acc in 2 variables, digit_type_max must be truncated
                // from its native max value
                acc_type
            >::type>::type>::type>::type digit_type;

    // constants
    static const acc_type acc_type_max;
    static const acc_type digit_type_max; // <= floor(sqrt(acc_type_max))

    // instance data
    int sign;                       // -1, 0, 1
    std::vector<digit_type> digits; // ordered least -> most significant
                                    // (digits.front() -> digits.back())
}
