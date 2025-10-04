#include "BigInt.hpp"

/**
 * @brief Function trims spaces from then beginning and the ending of a string
 * @param rawString
 * @return String without spaces at the beginning and at the end
 */
std::string BigInteger::trimSpaces(const std::string& rawString)
{
    const std::string space=" \n";
    std::string::size_type firstSymbol = rawString.find_first_not_of(space);
    if(firstSymbol == std::string::npos) return "";
    std::string::size_type lastSymbol = rawString.find_last_not_of(space);
    return rawString.substr(firstSymbol, lastSymbol - firstSymbol + 1);
}

/**
 * @param firstString
 * @param secondString
 * @return String that represents a sum of firstString and secondString
 */
std::string BigInteger::addStrings(const std::string& firstString, const std::string& secondString) {
    std::string resultString;
    long long index1 = firstString.size() - 1, index2 = secondString.size() - 1;
    int memory = 0;
    while(index1 >= 0 || index2 >= 0 || memory){
        int digit1 = (index1 >= 0) ? firstString[index1--] - '0' : 0;
        int digit2 = (index2 >= 0) ? secondString[index2--] - '0' : 0;
        int sum = digit1 + digit2 + memory;
        memory = sum / 10;
        resultString.push_back(sum % 10 + '0');
    }
    std::reverse(resultString.begin(), resultString.end());
    return resultString;
}

/**
 *
 * @param firstString
 * @param secondString
 * @return True if first number is less than second
 */
bool BigInteger::absLess(const std::string &firstString, const std::string &secondString) {
    if(firstString.size() != secondString.size())
        return firstString.size() < secondString.size();
    return firstString < secondString;
}

/**
 *
 * @param minuend
 * @param subtrahend
 * @return minuend - subtrahend
 */
std::string BigInteger::subtractStrings(const std::string &minuend, const std::string &subtrahend) {
    std::string difference;
    long long index1 = minuend.size() - 1;
    long long index2 = subtrahend.size() - 1;
    int borrow = 0;
    while (index1 >= 0) {
        int digit1 = minuend[index1] - borrow - '0';
        int digit2 = (index2 >= 0 ? subtrahend[index2] - '0' : 0);
        digit1 < digit2 ? digit1 += 10, borrow = 1 : borrow = 0;
        difference.push_back((digit1 - digit2) + '0');
        index1--;
        index2--;
    }
    while (difference.size() > 1 && difference.back() == '0') {
        difference.pop_back();
    }
    std::reverse(difference.begin(), difference.end());
    return difference;
}

/**
 *
 * @param multiplier1
 * @param multiplier2
 * @return String that represents a multiplication of multiplier1 and multiplier2
 */
std::string BigInteger::multiplyStrings(std::string num1, std::string num2) {
    if (num1 == "0" || num2 == "0") return "0";
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int answerLength = num1.size() + num2.size();
    std::string answer(answerLength, '0');
    for (int place2 = 0; place2 < num2.size(); place2++) {
        int digit2 = num2[place2] - '0';
        for (int place1 = 0; place1 < num1.size(); place1++) {
            int digit1 = num1[place1] - '0';
            int numZeros = place1 + place2;
            int carry = answer[numZeros] - '0';
            int multiplication = digit1 * digit2 + carry;
            answer[numZeros] = multiplication % 10 + '0';
            answer[numZeros + 1] += (char)multiplication / 10;
        }
    }
    if (answer.back() == '0') answer.pop_back();
    reverse(answer.begin(), answer.end());
    return answer;
}

/**
 *
 * @param dividend
 * @param divisor
 * @return String that represents a division of dividend by divisor
 */
std::string BigInteger::divideStrings(const std::string &dividend, const std::string &divisor) {
    if (absLess(dividend, divisor))
        return "0";

    std::string quotient, remainder;
    for (char c : dividend) {
        remainder.push_back(c);
        remainder.erase(0, remainder.find_first_not_of('0'));
        if (remainder.empty()) remainder = "0";
        int q = 0;
        while (!absLess(remainder, divisor)) {
            remainder = subtractStrings(remainder, divisor);
            q++;
        }
        quotient.push_back('0' + q);
    }
    quotient.erase(0, quotient.find_first_not_of('0'));
    if (quotient.empty()) quotient = "0";
    return quotient;
}

/**
 * @brief Function checks for empty string and character content only
 * @param rawString
 * @return None
 */
void BigInteger::digitsCheck(const std::string &rawDigits) {
    if (rawDigits.empty())
        throw std::invalid_argument("No digits found");

    for(char rawDigit : rawDigits) {
        if(!isdigit(rawDigit))
            throw std::invalid_argument("Invalid characters (only digits allowed)");
    }
}

/**
 * @brief Function sets isNegative for a BigInteger
 * @param rawDigits
 */
void BigInteger::setNegativity(std::string &rawDigits) {
    this->isNegative = false;
    std::size_t pos = 0;
    if(rawDigits[pos] == '-' || rawDigits[pos] == '+') {
        isNegative = (rawDigits[pos] == '-');
        pos = 1;
    }
    rawDigits = rawDigits.substr(pos);
}