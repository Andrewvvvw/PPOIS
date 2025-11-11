#include "Exceptions.h"

Exception::Exception(const std::string message) : message(message) {}
const char *Exception::what() const noexcept {
    return this->message.c_str();
}

ExceptionNegativeCapacity::ExceptionNegativeCapacity(const std::string message) : Exception(message) {}
ExceptionEmptyOrder::ExceptionEmptyOrder(const std::string message) : Exception(message) {}
ExceptionEmptyPhoneNumber::ExceptionEmptyPhoneNumber(const std::string message) : Exception(message) {}
ExceptionNegativeBillTotal::ExceptionNegativeBillTotal(const std::string message) : Exception(message) {}
ExceptionNegativeItemAmount::ExceptionNegativeItemAmount(const std::string message) : Exception(message) {}
ExceptionNegativeStockMinimum::ExceptionNegativeStockMinimum(const std::string message) : Exception(message) {}
ExceptionIncorrectDiscountAmount::ExceptionIncorrectDiscountAmount(const std::string message) : Exception(message) {}
ExceptionNegativeQuantity::ExceptionNegativeQuantity(const std::string message) : Exception(message) {}
ExceptionNegativeServiceCharge::ExceptionNegativeServiceCharge(const std::string message) : Exception(message) {}
ExceptionIncorrectItemPrice::ExceptionIncorrectItemPrice(const std::string message) : Exception(message) {}
ExceptionIncorrectCustomerAmount::ExceptionIncorrectCustomerAmount(const std::string message) : Exception(message) {}
ExceptionEmptyName::ExceptionEmptyName(const std::string message) : Exception(message) {}
