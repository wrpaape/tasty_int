#ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
#define TASTY_INT_TASTY_INT_TASTY_INT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>      // std::vector
#include <string>      // std::string
#include <iostream>    // std::[i|o]stream
#include <limits>      // std::numeric_limits
#include <type_traits> // std::[enable_if
                       //       |conditional
                       //       |make_signed
                       //       |is_[un]signed
                       //       |is_integral
                       //       |is_floating_point]


// Interface
// =============================================================================
class TastyInt
{
// Friends
// -----------------------------------------------------------------------------
    // arithmetic
    friend TastyInt operator+(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator-(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator*(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator/(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator%(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator<<(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator>>(const TastyInt &lhs, const TastyInt &rhs);
    // bitwise
    friend TastyInt operator&(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator|(const TastyInt &lhs, const TastyInt &rhs);
    friend TastyInt operator^(const TastyInt &lhs, const TastyInt &rhs);
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
    static unsigned int global_default_base; // mutable, initialized to 10

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
    // -------------------------------------------------------------------------
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
    // -------------------------------------------------------------------------
    TastyInt &operator<<=(const TastyInt &other);
    TastyInt &operator>>=(const TastyInt &other);
    TastyInt &operator&=(const TastyInt &other);
    TastyInt &operator|=(const TastyInt &other);
    TastyInt &operator^=(const TastyInt &other);
    TastyInt operator~() const;

    // conditional
    // -------------------------------------------------------------------------
    explicit operator bool() const;
    bool operator!() const;

    // comparison
    // -------------------------------------------------------------------------
    bool operator==(const TastyInt &other) const;
    bool operator!=(const TastyInt &other) const;
    bool operator<=(const TastyInt &other) const;
    bool operator>=(const TastyInt &other) const;
    bool operator<(const TastyInt &other) const;
    bool operator>(const TastyInt &other) const;

    // conversion
    // -------------------------------------------------------------------------
    std::string to_string(const unsigned int base = global_default_base) const;
    template<typename ArithmeticType>
    ArithmeticType to_number() const;


private:
    // types
    // -------------------------------------------------------------------------
    // acc_type
    //      unsigned integer large enough to hold the result of
    //      digit_type_max * digit_type_max
    //      also
    //      sizeof(digit_type) * 2 >= sizeof(acc_type)
    //      -> 2 digits guaranteed to hold 1 acc
    typedef unsigned long acc_type;
    // signed_acc_type
    //      signed version of acc_type
    typedef std::make_signed<acc_type>::type signed_acc_type;
    // digit_type
    //      unsigned integer, atomic unit of arithmetic
    typedef std::conditional<(sizeof(unsigned char)  * 2) >= sizeof(acc_type),
                unsigned char,
            std::conditional<(sizeof(unsigned short) * 2) >= sizeof(acc_type),
                unsigned short,
            std::conditional<(sizeof(unsigned int)   * 2) >= sizeof(acc_type),
                unsigned int,
                // no integer type smaller than acc_type that can express an
                // acc in 2 instances
                // digit_type = acc_type, and digit_type_max must be truncated
                // from its native max value (acc_type_max)
                acc_type
    >::type>::type>::type digit_type;

    // static data
    // -------------------------------------------------------------------------
    // digit_bit
    //      half the bit-size of acc_type
    static const unsigned int
    digit_bit = std::numeric_limits<acc_type>::digits / 2;
    // digit_type_max
    //      max value of digit_type where
    //      digit_type_max == (2 ^ N) - 1
    //                     == 1 << digit_bit - 1
    //                     <= floor(sqrt(native max value of acc_type))
    //                     <= native max value of digit_type
    static const acc_type digit_type_max = (1UL << digit_bit) - 1;

    // alias declarations
    // -------------------------------------------------------------------------
    // C++17 type tag, {} or operator() yields std::[true|false]_type
    template <bool E>
    using bool_constant = std::integral_constant<bool, E>;
    // arithmetic type 'T' can exceed max value held in digit_type ?
    template <typename T>
    using exceeds_digit = bool_constant<
        (std::numeric_limits<T>::max() > digit_type_max)
    >;
    // C++14 SFINAE mechanism for [en|dis]abling functions with return type 'R'
    // according to constexpr bool 'E'
    template <bool E, typename R = void>
    using enable_if_t = typename std::enable_if<E, R>::type;
    // arithmetic type 'T' is integral?
    template <typename T, typename R = void>
    using enable_if_integral = enable_if_t<std::is_integral<T>::value, R>;
    template <typename T, typename R = void>
    using enable_if_floating_point
    = enable_if_t<std::is_floating_point<T>::value, R>;
    // arithmetic type 'T' is signed?
    template <typename T, typename R = void>
    using enable_if_signed = enable_if_t<std::is_signed<T>::value, R>;
    template <typename T, typename R = void>
    using enable_if_unsigned = enable_if_t<std::is_unsigned<T>::value, R>;
    // arithmetic type 'T' may exceed digit_type_max?
    template <typename T, typename R = void>
    using enable_if_exceeds_digit = enable_if_t<exceeds_digit<T>::value, R>;
    template <typename T, typename R = void>
    using enable_if_within_digit = enable_if_t<!exceeds_digit<T>::value, R>;

    // static methods
    // -------------------------------------------------------------------------
    // get_digit
    template <typename T>
    static enable_if_exceeds_digit<T, digit_type> get_digit(const T value);
    template <typename T>
    static enable_if_within_digit<T, digit_type> get_digit(const T value);

    // instance data
    // -------------------------------------------------------------------------
    int sign;                       // -1, 0, 1
    std::vector<digit_type> digits; // ordered least -> most significant
                                    // (digits.front() -> digits.back())

    // instance methods
    // -------------------------------------------------------------------------
    // init from number
    template <typename T>
    enable_if_exceeds_digit<T> digits_from_unsigned_integral(const T value);
    template <typename T>
    enable_if_within_digit<T> digits_from_unsigned_integral(const T value);
    template <typename T>
    enable_if_signed<T> from_integral(T value);
    template <typename T>
    enable_if_unsigned<T> from_integral(T value);
    template <typename T>
    enable_if_integral<T> from_arithmetic(T value);
    template <typename T>
    enable_if_floating_point<T> from_arithmetic(T value);
    // cast to number
    template <typename T>
    enable_if_exceeds_digit<T, T> digits_to_unsigned_integral();
    template <typename T>
    enable_if_within_digit<T, T> digits_to_unsigned_integral();
    template <typename T>
    enable_if_signed<T, T> to_integral();
    template <typename T>
    enable_if_unsigned<T, T> to_integral();
    template <typename T>
    enable_if_integral<T, T> to_arithmetic(T value);
    template <typename T>
    enable_if_floating_point<T, T> to_arithmetic(T value);
};


// Inline Implementation
// =============================================================================
#include "tasty_int/tasty_int.ipp"

#endif // ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
