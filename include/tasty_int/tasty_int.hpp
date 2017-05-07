#ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
#define TASTY_INT_TASTY_INT_TASTY_INT_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <vector>      // std::vector
#include <string>      // std::string
#include <iostream>    // std::[i|o]stream
#include <type_traits> // std::[conditional|make_signed|bool_constant]


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
    explicit operator!() const;

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
    static const unsigned int digit_bit;
    // digit_type_max
    //      max value of digit_type where
    //      digit_type_max == (2 ^ N) - 1
    //                     == 1 << digit_bit - 1
    //                     <= floor(sqrt(native max value of acc_type))
    //                     <= native max value of digit_type
    static const acc_type digit_type_max;

    // alias declarations
    // -------------------------------------------------------------------------
    // C++17 type tag, operator() yields std::[true|false]_type
    template <bool E>
    using bool_constant = std::integral_constant<bool, E>;
    // arithmetic type 'T' can exceed max value held in digit_type ?
    template <typename T>
    using exceeds_digit = bool_constant<
        std::numeric_limits<T>::max() > digit_type_max
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
    template <typename UnsignedIntegralType>
    static UnsignedIntegralType mask_value(const UnsignedIntegralType value,
                                           std::true_type needs_mask);
    template <typename UnsignedIntegralType>
    static UnsignedIntegralType mask_value(const UnsignedIntegralType value,
                                           std::false_type needs_mask);
    template <typename UnsignedIntegralType>
    static digit_type get_digit(const UnsignedIntegralType value);

    // instance data
    // -------------------------------------------------------------------------
    int sign;                       // -1, 0, 1
    std::vector<digit_type> digits; // ordered least -> most significant
                                    // (digits.front() -> digits.back())

    // instance methods
    // -------------------------------------------------------------------------
    // from_number
    template <typename UnsignedIntegralType>
    void digits_from_unsigned_integral(const UnsignedIntegralType value,
                                       std::true_type overflow);
    template <typename UnsignedIntegralType>
    void digits_from_unsigned_integral(const UnsignedIntegralType value,
                                       std::false_type overflow);
    template <typename IntegralType>
    void from_integral(IntegralType value, std::true_type is_signed);
    template <typename IntegralType>
    void from_integral(IntegralType value, std::false_type is_signed);
    template <typename ArithmeticType,
              std::bool_constant IsIntegral>
    void from_number(ArithmeticType value, std::true_type is_integral);
    template <typename ArithmeticType,
              std::bool_constant IsIntegral>
    void from_number(ArithmeticType value, std::false_type is_integral);
    // to_number
    template<typename ArithmeticType>
    ArithmeticType to_number() const;
    template<typename ArithmeticType>
    ArithmeticType to_number() const;
};


// Inline Implementation
// =============================================================================
#include "tasty_int/tasty_int.ipp"

#endif // ifndef TASTY_INT_TASTY_INT_TASTY_INT_HPP
