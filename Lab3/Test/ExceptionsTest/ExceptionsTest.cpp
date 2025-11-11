#include "UnitTest++.h"
#include "../../Source/Exceptions/Exceptions.h"

TEST(ExceptionBaseClass) {
    Exception baseException("Test base exception");
    CHECK_EQUAL("Test base exception", std::string(baseException.what()));
}

TEST(ExceptionNegativeItemAmount) {
    ExceptionNegativeItemAmount exception("Negative item amount");
    CHECK_EQUAL("Negative item amount", std::string(exception.what()));
}

TEST(ExceptionNegativeBillTotal) {
    ExceptionNegativeBillTotal exception("Negative bill total");
    CHECK_EQUAL("Negative bill total", std::string(exception.what()));
}

TEST(ExceptionNegativeServiceCharge) {
    ExceptionNegativeServiceCharge exception("Negative service charge");
    CHECK_EQUAL("Negative service charge", std::string(exception.what()));
}

TEST(ExceptionIncorrectCustomerAmount) {
    ExceptionIncorrectCustomerAmount exception("Incorrect customer amount");
    CHECK_EQUAL("Incorrect customer amount", std::string(exception.what()));
}

TEST(ExceptionNegativeQuantity) {
    ExceptionNegativeQuantity exception("Negative quantity");
    CHECK_EQUAL("Negative quantity", std::string(exception.what()));
}

TEST(ExceptionNegativeStockMinimum) {
    ExceptionNegativeStockMinimum exception("Negative stock minimum");
    CHECK_EQUAL("Negative stock minimum", std::string(exception.what()));
}

TEST(ExceptionNegativeCapacity) {
    ExceptionNegativeCapacity exception("Negative capacity");
    CHECK_EQUAL("Negative capacity", std::string(exception.what()));
}

TEST(ExceptionEmptyOrder) {
    ExceptionEmptyOrder exception("Empty order");
    CHECK_EQUAL("Empty order", std::string(exception.what()));
}

TEST(ExceptionEmptyPhoneNumber) {
    ExceptionEmptyPhoneNumber exception("Empty phone number");
    CHECK_EQUAL("Empty phone number", std::string(exception.what()));
}

TEST(ExceptionEmptyName) {
    ExceptionEmptyName exception("Empty name");
    CHECK_EQUAL("Empty name", std::string(exception.what()));
}

TEST(ExceptionIncorrectDiscountAmount) {
    ExceptionIncorrectDiscountAmount exception("Incorrect discount amount");
    CHECK_EQUAL("Incorrect discount amount", std::string(exception.what()));
}

TEST(ExceptionIncorrectItemPrice) {
    ExceptionIncorrectItemPrice exception("Incorrect item price");
    CHECK_EQUAL("Incorrect item price", std::string(exception.what()));
}
