#include "BigInt.hpp"

/**
 * @brief Default constructor
 */
BigInteger::BigInteger() : digits("0"), isNegative(false) {}
/**
 * @brief Constructor from int type
 * @param value
 */
BigInteger::BigInteger(int value){
    value < 0 ? isNegative = true, value *= -1 : isNegative = false;
    digits = std::to_string(value);
}
/**
 * @brief Constructor from std::string type
 * @param value
 */
BigInteger::BigInteger(const std::string &value) {
    std::string rawDigits = trimSpaces(value);
    if (rawDigits.empty()) {
        throw std::invalid_argument("Empty input string");
    }

    this->setNegativity(rawDigits);
    digitsCheck(rawDigits);

    std::size_t firstDigit = rawDigits.find_first_not_of('0');
    if (firstDigit == std::string::npos) {
        digits = "0";
        isNegative = false;
    }
    else {
        digits = rawDigits.substr(firstDigit);
        if (digits == "0") isNegative = false;
    }
}

/**
 * @brief Copy constructor
 * @param other
 */
BigInteger::BigInteger(const BigInteger &other) :
    isNegative(other.isNegative),
    digits(other.digits) {}

/**
 * @brief
 * @return Number of int type
 */
BigInteger::operator int() const {
    std::string digitsToInt = digits;
    if(digitsToInt.size() > 10)
        digitsToInt = digitsToInt.substr(0, 10);

    unsigned long long value = 0;
    for (char curChar : digitsToInt) {
        value = value * 10 + (curChar - '0');
    }
    if(value > INT_MAX) value = INT_MAX;
    return isNegative ? -static_cast<int>(value) : static_cast<int>(value);
}

std::istream& operator>>(std::istream& in, BigInteger& number ) {
    std::string input;
    in >> input;
    number = BigInteger(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& number) {
    if(number.isNegative && number.digits != "0")
        out << '-';
    out << number.digits;
    return out;
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
    BigInteger result;
    if(this->isNegative == other.isNegative){
        result.digits = addStrings(this->digits, other.digits);
        result.isNegative = this->isNegative;
    }
    else{
        if(absLess(this->digits, other.digits)){    // |this| < |other|
            result.digits = subtractStrings(other.digits, this->digits);
            result.isNegative = other.isNegative;
        }
        else{   // |this| >= |other|
            result.digits = subtractStrings(this->digits, other.digits);
            result.isNegative = this->isNegative;
        }
        if(result.digits == "0")
            result.isNegative = false;
    }
    return result;
}

BigInteger BigInteger::operator+(const int value) const {
    return BigInteger(value) + *this;
}

BigInteger& BigInteger::operator+=(const BigInteger &other) {
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator+=(const int value) {
    *this = *this + BigInteger(value);
    return *this;
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
    BigInteger result;
    if(this->isNegative == other.isNegative){
        if(absLess(this->digits, other.digits)){    // |this| < |other|
            result.digits = subtractStrings(other.digits, this->digits);
            result.isNegative = !this->isNegative;
        }
        else{   // |this| >= |other|
            result.digits = subtractStrings(this->digits, other.digits);
            result.isNegative = this->isNegative;
        }
        if(result.digits == "0")
            result.isNegative = false;
    }
    else{
        result.digits = addStrings(this->digits, other.digits);
        result.isNegative = this->isNegative;
    }
    return result;
}

BigInteger BigInteger::operator-(const int value) const {
    return *this - BigInteger(value);
}

BigInteger& BigInteger::operator-=(const BigInteger &other) {
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator-=(const int value) {
    *this = *this - BigInteger(value);
    return *this;
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
    BigInteger result;
    result.digits = multiplyStrings(this->digits, other.digits);
    result.isNegative = !this->isNegative == other.isNegative;
    return result;
}

BigInteger& BigInteger::operator*=(const BigInteger &other) {
    *this = *this * other;
    return *this;
}

BigInteger BigInteger::operator*(int multiplier) const {
    return *this * BigInteger(multiplier);
}

BigInteger& BigInteger::operator*=(int multiplier) {
    *this = *this * BigInteger(multiplier);
    return *this;
}

BigInteger BigInteger::operator/(const BigInteger &other) const {
    if (other.digits == "0")
        throw std::invalid_argument("Division by zero");
    BigInteger result;
    result.digits = divideStrings(this->digits, other.digits);
    result.isNegative = ( (this->isNegative != other.isNegative) && result.digits != "0");
    return result;
}

BigInteger& BigInteger::operator/=(const BigInteger &other) {
    *this = *this / other;
    return *this;
}

BigInteger BigInteger::operator/(const int divisor) const {
    return *this / BigInteger(divisor);
}

BigInteger& BigInteger::operator/=(const int divisor) {
    if(divisor == 0)
        throw std::invalid_argument("Division by zero");
    *this = *this / BigInteger(divisor);
    return *this;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger NumberBeforeIncrement = *this;
    *this += 1;
    return NumberBeforeIncrement;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger numberBeforeDecrement = *this;
    *this -= 1;
    return numberBeforeDecrement;
}

bool BigInteger::operator>(const BigInteger &other) const {
    if(this->isNegative == other.isNegative) {
        if(this->isNegative)
            return absLess(this->digits, other.digits);
        else
            return !absLess(this->digits, other.digits);
    }
    else
        return !this->isNegative;
}

bool BigInteger::operator>=(const BigInteger &other) const {
    return (*this > other || *this == other);
}

bool BigInteger::operator<(const BigInteger &other) const {
    if(this->isNegative == other.isNegative) {
        if(this->isNegative)
            return !absLess(this->digits, other.digits);
        else
            return absLess(this->digits, other.digits);
    }
    else
        return this->isNegative;
}

bool BigInteger::operator<=(const BigInteger &other) const {
    return (*this < other || *this == other);
}

bool BigInteger::operator==(const BigInteger &other) const {
    return (this->digits == other.digits && this->isNegative == other.isNegative);
}

bool BigInteger::operator!=(const BigInteger &other) const {
    return (this->digits != other.digits || this->isNegative != other.isNegative);
}

bool BigInteger::operator>(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return *this > convertedComparable;
}

bool BigInteger::operator>=(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return (*this > convertedComparable || *this == convertedComparable);
}

bool BigInteger::operator<(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return *this < convertedComparable;
}

bool BigInteger::operator<=(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return (*this < convertedComparable || *this == convertedComparable);
}

bool BigInteger::operator==(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return *this == convertedComparable;
}

bool BigInteger::operator!=(const int comparable) const {
    BigInteger convertedComparable(comparable);
    return *this != convertedComparable;
}