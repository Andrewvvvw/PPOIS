#ifndef LAB3_DISCOUNT_H
#define LAB3_DISCOUNT_H
#include <string>

class Discount {
private:
    std::string code;
    double amount;
    bool isPercentage;
    double maxDiscountAmount;

public:
    Discount(const std::string& code, double amount, bool isPercentage = true, double maxAmount = 0.0);

    std::string getCode() const;
    double getAmount() const;
    bool getIsPercentage() const;
    double getMaxDiscountAmount() const;

    void setMaxDiscountAmount(double maxAmount);
    double applyDiscount(double total) const;
    bool isValid() const;
    std::string getDescription() const;
};
#endif //LAB3_DISCOUNT_H
