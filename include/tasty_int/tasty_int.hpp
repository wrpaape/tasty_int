#define tasty_int_VERSION_MAJOR @tasty_int_VERSION_MAJOR@
#define tasty_int_VERSION_MINOR @tasty_int_VERSION_MINOR@

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>      // std::vector
#include <string>      // std::string
#include <iostream>    // std::[i|o]stream
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
    friend TastyInt &operator%(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator<<(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator>>(const TastyInt &lhs, const TastyInt &rhs);
    // bitwise
    friend TastyInt &operator&(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator|(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt &operator^(const TastyInt &lhs, const TastyInt &rhs);
    // comparison
    friend int compare(const TastyInt &lhs, const TastyInt &rhs);
    // IO
    friend std::ostream &operator<<(std::ostream &os, const TastyInt &x);
    friend std::istream &operator>>(std::ostream &is, const TastyInt &x);

// Members
// -----------------------------------------------------------------------------
public:
    // data
    // -------------------------------------------------------------------------
    static unsigned int global_default_base = 10;
    // constructors
    // -------------------------------------------------------------------------
    TastyInt();                                              // default
    TastyInt(const TastyInt &other);                         // copy
    TastyInt(const TastyInt &&other) noexcept;               // move
    TastyInt(const std::string &string,
             const unsigned int base = global_default_base); // from string
    template<typename IntegralType>
    TastyInt(const IntegralType &value);                     // from integral
    // destructor
    // -------------------------------------------------------------------------
    ~TastyInt() noexcept;
    // assignment
    // -------------------------------------------------------------------------
    TastyInt &operator=(const TastyInt &other);           // copy
    TastyInt &operator=(const TastyInt &&other) noexcept; // move
    TastyInt &operator=(const std::string &string);       // from string
    template<typename IntegralType>
    TastyInt &operator=(const IntegralType &value);       // from integral
    // swap
    // -------------------------------------------------------------------------
    void swap(TastyInt &other) noexcept;
    // arithmetic
    TastyInt &operator+=(const TastyInt &other);
    TastyInt &operator-=(const TastyInt &other);
    TastyInt &operator*=(const TastyInt &other);
    TastyInt &operator/=(const TastyInt &other);
    TastyInt &operator%=(const TastyInt &other);
    TastyInt &operator++();
    TastyInt &operator--();
    TastyInt operator++(int);
    TastyInt operator--(int);
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
    // conversion
    std::string to_string(const unsigned int base = global_default_base) const;
    template<typename IntegralType>
    IntegralType to_integral() const;


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
    typedef unsigned long long acc_type;
    typedef std::conditional<(sizeof(unsigned char)  * 2) >= sizeof(acc_type),
                unsigned char,
            std::conditional<(sizeof(unsigned short) * 2) >= sizeof(acc_type),
                unsigned short,
            std::conditional<(sizeof(unsigned int)   * 2) >= sizeof(acc_type),
                unsigned int,
            std::conditional<(sizeof(unsigned long)  * 2) >= sizeof(acc_type),
                unsigned long,
                // no integer type smaller than acc_type that can express an
                // acc in 2 instances
                // digit_type = acc_type, and digit_type_max must be truncated
                // from its native max value (acc_type_max)
                acc_type
            >::type>::type>::type>::type digit_type;

    // constants
    //
    // digit_type_max
    //      max value of digit_type where
    //      digit_type_max == (2 ^ N) - 1
    //                     <= floor(sqrt(native max value of acc_type))
    //                     <= native max value of digit_type
    static const acc_type digit_type_max;

    // instance data
    int sign;                       // -1, 0, 1
    std::vector<digit_type> digits; // ordered least -> most significant
                                    // (digits.front() -> digits.back())

    // helper templates
    template <typename IntegralType,
             std::bool_constant IsSigned,
             std::bool_constant ExceedsDigitType,
             std::bool_constant NeedMask>
    void from_int(const IntegralType &value);

    template<typename IntegralType>
    IntegralType to_int() const;
}
