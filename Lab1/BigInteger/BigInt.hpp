/**
 * @author Andrewvvvw
 */
#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>

class BigInteger {
private:
    std::string digits;
    bool isNegative;

    static std::string trimSpaces(const std::string& rawString);
    static std::string addStrings(const std::string& firstString, const std::string& secondString);
    static std::string subtractStrings(const std::string& minuend , const std::string& subtrahend);
    static std::string multiplyStrings(const std::string firstMultiplier, const std::string secondMultiplier);
    static bool absLess(const std::string& firstString, const std::string& secondString);
    static std::string divideStrings(const std::string &dividend, const std::string &divisor);
    static void digitsCheck(const std::string &rawDigits);
    void setNegativity(std::string &rawDigits);
public:
    BigInteger();
    explicit BigInteger(int);
    explicit BigInteger(const std::string &);
    BigInteger(const BigInteger &);

    explicit operator int() const;

    BigInteger operator+(const BigInteger& other) const;
    BigInteger& operator+=(const BigInteger& other);
    BigInteger operator-(const BigInteger& other) const;
    BigInteger& operator-=(const BigInteger& other);
    BigInteger operator*(const BigInteger& other) const;
    BigInteger& operator*=(const BigInteger& other);
    BigInteger operator/(const BigInteger& other) const;
    BigInteger& operator/=(const BigInteger& other);

    BigInteger operator+(int value) const;
    BigInteger& operator+=(int value);
    BigInteger operator-(int value) const;
    BigInteger& operator-=(int value);
    BigInteger operator*(int value) const;
    BigInteger& operator*=(int value);
    BigInteger operator/(int value) const;
    BigInteger& operator/=(int value);

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;

    bool operator<(const int value) const;
    bool operator>(const int value) const;
    bool operator<=(const int value) const;
    bool operator>=(const int value) const;
    bool operator==(const int value) const;
    bool operator!=(const int value) const;

    friend std::istream& operator>>(std::istream& in, BigInteger& number);
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);
};

#endif
