#include "BigInt.hpp"
#include "UnitTest++.h"

SUITE(ConstructorsTesting) {
    TEST(ConstructorFromInt_Positive) {
        BigInteger number1(123);
        CHECK(number1 == 123);
    }

    TEST(ConstructorFromInt_Negative) {
        BigInteger number1(-42);
        CHECK(number1 == -42);
    }

    TEST(ConstructorFromString_Valid) {
        BigInteger number1("   +00123 ");
        CHECK(number1 == 123);
    }

    TEST(ConstructorFromString_Negative) {
        BigInteger number1(" -00099");
        CHECK(number1 == -99);
    }

    TEST(ConstructorFromString_Empty) {
        CHECK_THROW(BigInteger("   "), std::invalid_argument);
    }

    TEST(ConstructorFromString_InvalidChars) {
        CHECK_THROW(BigInteger("12a34"), std::invalid_argument);
    }

    TEST(ConstructorFromString_NoDigitsAfterSign) {
        CHECK_THROW(BigInteger("+"), std::invalid_argument);
        CHECK_THROW(BigInteger("-"), std::invalid_argument);
    }

    TEST(CopyConstructor) {
        BigInteger number1("123");
        BigInteger number2(number1);
        CHECK(number1 == number2);
    }
}

SUITE(OperatorIntTesting) {
    TEST (OperatorInt_Small) {
        BigInteger number1("12345");
        CHECK_EQUAL(12345, (int) number1);
    }

    TEST (OperatorInt_Truncate1) {
        BigInteger number1("123456789012345");
        CHECK_EQUAL(1234567890, (int) number1);
    }

    TEST (OperatorInt_Negative) {
        BigInteger number1("-99");
        CHECK_EQUAL(-99, (int) number1);
    }

    TEST(OperatorInt_Truncate2){
        BigInteger number1("99999999999999999999999999");
        int convertedNumber = (int)number1;
        CHECK_EQUAL(2147483647, convertedNumber);
    }
}

SUITE(BigIntSumTesting) {

    TEST (SumNegative) {
        BigInteger number1("-50"), number2("-50");
        CHECK_EQUAL(-100, int(number1 + number2));
    }

    TEST (SumDifferentSigns) {
        BigInteger number1("100"), number2("-40");
        CHECK_EQUAL(60, int(number1 + number2));
    }

    TEST(SumPositive){
        BigInteger number1("1231"), number2("1010");
        CHECK_EQUAL(BigInteger(2241), number1 + number2);
    }

    TEST(BigIntSumWithAssignment){
        BigInteger number1("123456789"), number2("111");
        number1 += number2;
        CHECK_EQUAL(BigInteger("123456900"), number1);
    }
}

SUITE(IntSumTesting) {
    TEST(IntSumTest){
        BigInteger number1(1000);
        CHECK_EQUAL(BigInteger(1001), number1 + 1);
    }
    TEST(IntSumWithAssignmentTest){
        BigInteger number1("1231");
        int number2 = 1010;
        number1 += number2;
        CHECK_EQUAL(BigInteger(2241), number1);
    }
}

SUITE(BigIntSubtractionTesting){
    TEST(Subtraction) {
        BigInteger number1("200"), number2("50");
        CHECK_EQUAL(150, int(number1 - number2));
    }
    
    TEST(Subtraction_NegativeResult) {
        BigInteger number1("50"), number2("200");
        CHECK_EQUAL(-150, int(number1 - number2));
    }

    TEST(SubtractionToZero){
        BigInteger number1("1000000000000000000000"), number2("1000000000000000000000");
        CHECK_EQUAL(BigInteger(0), number1 - number2);
    }

    TEST(SubtractionWithAssignment){
        BigInteger number1("1000000000000000000000"), number2("1000000000000000000000");
        number1 -= number2;
        CHECK_EQUAL(BigInteger(0), number1);
    }
}

SUITE(IntSubtractionTesting) {
    TEST(IntSubtraction) {
        BigInteger number1("1000000000000000000000");
        CHECK_EQUAL(BigInteger("1000000000000000000000"), number1 - 0);
        CHECK_EQUAL(BigInteger( "999999999999999991234"), number1 - 8766);

    }
    TEST(IntSubtractionWithAssignment) {
        BigInteger number1("1000000000000000000000");
        number1 -= 0;
        CHECK_EQUAL(BigInteger("1000000000000000000000"), number1);
        number1 -= 8766;
        CHECK_EQUAL(BigInteger( "999999999999999991234"), number1);
    }
}

SUITE(BigIntMultiplicationTesting) {
    TEST (Multiplication) {
        BigInteger number1("12"), number2("-3");
        CHECK_EQUAL(-36, int(number1 * number2));
        number1 = BigInteger("1230000000000000000"), number2 = BigInteger("456000");
        CHECK_EQUAL(BigInteger("560880000000000000000000"), number1 * number2);
    }

    TEST (MultiplicationByZero) {
        BigInteger number1("9999"), number2("0");
        CHECK_EQUAL(0, int(number1 * number2));
    }

    TEST(BigIntMultiplicationWithAssignment) {
        BigInteger number1("1230000000000000000"), number2("456000");
        number1 *= number2;
        CHECK_EQUAL(BigInteger("560880000000000000000000"), number1);
        number1 *= BigInteger(0);
        CHECK_EQUAL(0, (int)number1);
    }
}

SUITE(IntMultiplicationTesting) {
    TEST(IntMultiplication) {
        BigInteger number1("1230000000000000000");
        int number2 = 456000;
        CHECK_EQUAL(BigInteger("560880000000000000000000"), number1 * number2);
    }

    TEST(IntMultiplyWithAssignment) {
        BigInteger number1("1230000000000000000");
        int number2 = 456000;
        number1 *= number2;
        CHECK_EQUAL(BigInteger("560880000000000000000000"), number1);
    }

    TEST(IntMultiplicationByZero) {
        BigInteger number1("1230000000000000000");
        CHECK_EQUAL(0, int(number1 * 0));
    }
}

SUITE(BigIntDivisionTesting) {
    TEST(Division) {
        BigInteger number1("100"), number2("25");
        CHECK_EQUAL(4, int(number1 / number2));
        BigInteger dividend("1000000000000"), divisor("1000000000000");
        CHECK_EQUAL(BigInteger(1), dividend / divisor);
        divisor *= -1;
        CHECK_EQUAL(BigInteger(-1), dividend / divisor);
    }

    TEST(DivisionByZero) {
        BigInteger dividend("1000000000000"), divisor(0);
        CHECK_THROW(dividend / divisor, std::invalid_argument);
    }

    TEST(DivisionWithAssignment) {
        BigInteger dividend("1000000000000"), divisor("-1000000000000");
        dividend /= divisor;
        CHECK_EQUAL(BigInteger(-1), dividend);
    }

    TEST(DivisionByZeroWithAssignment) {
        BigInteger dividend("1000000000000"), divisor("0");
        CHECK_THROW(dividend /= divisor, std::invalid_argument);
    }
}

SUITE(IntDivisionTesting) {
    TEST(DivisionByInt) {
        BigInteger dividend("100000000000");
        int divisor =       -1000000000;
        CHECK_EQUAL(BigInteger(-100), dividend / divisor);
    }
    TEST(DivisionByZero) {
        BigInteger dividend("100000000000");
        int divisor = 0;
        CHECK_THROW(dividend / divisor, std::invalid_argument);
    }
    TEST(DivisionByIntWithAssignment) {
        BigInteger dividend("100000000000");
        int divisor =       -1000000000;
        dividend /= divisor;
        CHECK_EQUAL(BigInteger(-100), dividend);
    }
    TEST(DivisionByZeroWithAssignment) {
        BigInteger dividend("100000000000");
        int divisor = 0;
        CHECK_THROW(dividend /= divisor, std::invalid_argument);
    }
}

SUITE(IncrementDecrementTesting) {
    TEST(PreIncrementTest) {
        BigInteger number1("1000000000000000000000");
        CHECK_EQUAL(BigInteger("1000000000000000000001"), ++number1);
        CHECK_EQUAL(BigInteger("1000000000000000000001"), number1);
    }
    TEST(PostIncrementTest){
        BigInteger number1("1000000000000000000000");
        CHECK_EQUAL(BigInteger("1000000000000000000000"), number1++);
        CHECK_EQUAL(BigInteger("1000000000000000000001"), number1);
    }
    TEST(PreDecrementTest){
        BigInteger number1("123456789987654321");
        CHECK_EQUAL(BigInteger("123456789987654320"), --number1);
    }
    TEST(PostDecrementTest){
        BigInteger number1("123456789987654321");
        CHECK_EQUAL(BigInteger("123456789987654321"), number1--);
        CHECK_EQUAL(BigInteger("123456789987654320"), number1);
    }
}

SUITE(BigIntComparisonTesting) {
    TEST(GreaterThan_LessThan_Comparison) {
        BigInteger number1("123456789987654321"), number2("123456789999999999");
        CHECK_EQUAL(true, number2 > number1);
        CHECK_EQUAL(false, number2 < number1);
        number2 *= -1;
        CHECK_EQUAL(false, number2 > number1);
        CHECK_EQUAL(true, number2 < number1);
        number1 *= -1;
        CHECK_EQUAL(false, number2 > number1);
        CHECK_EQUAL(true, number2 < number1);
        number2 *= -1;
        CHECK_EQUAL(true, number2 > number1);
        CHECK_EQUAL(false, number2 < number1);
    }
    TEST(GreaterThanOrEqual_LessThanOrEqual_Comparison) {
        BigInteger number1("123456789987654321"), number2("123456789987654321");
        CHECK_EQUAL(true, number2 >= number1);
        CHECK_EQUAL(true, number2 <= number1);
        number2 *= -1;
        CHECK_EQUAL(false, number2 >= number1);
        CHECK_EQUAL(true, number2 <= number1);
        number1 *= -1;
        CHECK_EQUAL(true, number2 >= number1);
        number2 *= -1;
        CHECK_EQUAL(false, number2 <= number1);
    }
    TEST(Equality) {
        BigInteger number1("123456789987654321"), number2("123456789987654321");
        CHECK_EQUAL(true, number2 == number1);
        BigInteger number3("111111789987654321");
        CHECK_EQUAL(false, number3 == number1);
        number2 *= -1;
        CHECK_EQUAL(false, number2 == number1);
        number1 *= -1;
        CHECK_EQUAL(true, number2 == number1);

        CHECK_EQUAL(false, number2 != number1);
        CHECK_EQUAL(true, number3 != number1);
    }
}

SUITE(BigIntToIntComparisonTesting) {
    TEST (ComparisonPositive) {
        BigInteger number1("123");
        int number2 = 456;
        CHECK(number1 < number2);
        CHECK(!(number1 > number2));
        CHECK(number1 <= number2);
        CHECK(!(number1 >= number2));
        CHECK(number1 != number2);
        CHECK(!(number1 == number2));
    }

    TEST (ComparisonToNegative) {
        BigInteger number1("42");
        CHECK(!(number1 == -42));
        CHECK(number1 != 43);
        CHECK(number1 > -10);
        CHECK(number1 >= -42);
        CHECK(!(number1 < -100));
        CHECK(!(number1 <= -42));
    }
}

SUITE(StreamOperatorsTesting) {
    TEST (StreamOutput_Positive) {
        BigInteger number1("123");
        std::ostringstream oss;
        oss << number1;
        CHECK_EQUAL("123", oss.str());
    }

    TEST (StreamOutput_Negative) {
        BigInteger number1("-123");
        std::ostringstream oss;
        oss << number1;
        CHECK_EQUAL("-123", oss.str());
    }

    TEST (StreamInput) {
        std::istringstream iss("456");
        BigInteger number1;
        iss >> number1;
        CHECK(number1 == 456);
    }
}

int main()
{
    return UnitTest::RunAllTests();
}