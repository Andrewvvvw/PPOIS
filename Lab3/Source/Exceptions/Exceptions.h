#ifndef LAB3_EXCEPTIONS_H
#define LAB3_EXCEPTIONS_H
#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string message;
public:
    [[nodiscard]] const char* what() const noexcept override;
    explicit Exception(std::string message);
};

class ExceptionNegativeItemAmount : public Exception {
public:
    explicit ExceptionNegativeItemAmount(std::string message);
};

class ExceptionNegativeBillTotal : public Exception {
public:
    explicit ExceptionNegativeBillTotal(std::string message);
};

class ExceptionNegativeServiceCharge : public Exception {
public:
    explicit ExceptionNegativeServiceCharge(std::string message);
};

class ExceptionIncorrectCustomerAmount : public Exception {
public:
    explicit ExceptionIncorrectCustomerAmount(std::string message);
};

class ExceptionNegativeQuantity : public Exception {
public:
    explicit ExceptionNegativeQuantity(std::string message);
};

class ExceptionNegativeStockMinimum : public Exception {
public:
    explicit ExceptionNegativeStockMinimum(std::string message);
};

class ExceptionNegativeCapacity : public Exception {
public:
    explicit ExceptionNegativeCapacity(std::string message);
};

class ExceptionEmptyOrder : public Exception {
public:
    explicit ExceptionEmptyOrder(std::string message);
};

class ExceptionEmptyPhoneNumber : public Exception {
public:
    explicit ExceptionEmptyPhoneNumber(std::string message);
};

class ExceptionEmptyName : public Exception {
public:
    explicit ExceptionEmptyName(std::string message);
};

class ExceptionIncorrectDiscountAmount : public Exception {
public:
    explicit ExceptionIncorrectDiscountAmount(std::string message);
};

class ExceptionIncorrectItemPrice : public Exception {
public:
    explicit ExceptionIncorrectItemPrice(std::string message);
};
#endif //LAB3_EXCEPTIONS_H
