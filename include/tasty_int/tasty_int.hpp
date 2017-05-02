#ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
#define TASTY_INT_TASTY_INT_TASTY_INT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>      // std::vector
#include <string>      // std::string
#include <iostream>    // std::[i|o]stream
#include <type_traits> // std::[conditional|make_signed]


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
    template<typename ArithmeticType>
    TastyInt(ArithmeticType value);                          // from number
    // destructor
    // -------------------------------------------------------------------------
    ~TastyInt() noexcept;
    // assignment
    // -------------------------------------------------------------------------
    TastyInt &operator=(const TastyInt &other);           // copy
    TastyInt &operator=(const TastyInt &&other) noexcept; // move
    TastyInt &operator=(const std::string &string);       // from string
    template<typename ArithmeticType>
    TastyInt &operator=(ArithmeticType value);            // from number
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
    template<typename ArithmeticType>
    ArithmeticType to_number() const;


private:
    // types
    //
    // digit_type
    //      unsigned integer, atomic unit of arithmetic
    // acc_type
    //      unsigned integer large enough to hold the result of
    //      digit_type_max * digit_type_max
    //      also
    //      sizeof(digit_type) * 2 >= sizeof(acc_type)
    //      -> 2 digits guaranteed to hold 1 acc
    // signed_acc_type
    //      signed version of acc_type
    typedef unsigned long long acc_type;
    typedef std::make_signed<acc_type>::type signed_acc_type;
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
    static const unsigned int digit_bits;

    // instance data
    int sign;                       // -1, 0, 1
    std::vector<digit_type> digits; // ordered least -> most significant
                                    // (digits.front() -> digits.back())



    // helper templates

    template <typename UnsignedIntegralType>
    static digit_type get_low_digit(const UnsignedIntegralType value);

    template <typename UnsignedIntegralType>
    static digit_type get_high_digit(const UnsignedIntegralType value);

    template <typename UnsignedIntegralType,
              std::bool_constant ExceedsDigitType>
              std::bool_constant NeedMask>
    void digits_from_unsigned_integral(const UnsignedIntegralType value);

    template <typename IntegralType,
              std::bool_constant IsSigned>
    void from_integral(IntegralType value);

    template <typename ArithmeticType,
              std::bool_constant IsIntegral>
    void from_number(ArithmeticType value);

    template<typename ArithmeticType>
    ArithmeticType to_number() const;
};


// Inline Implementation
// =============================================================================
#include "tasty_int/tasty_int.ipp"

#endif // ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
