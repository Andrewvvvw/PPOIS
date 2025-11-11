#include "Discount.h"
#include "../../Exceptions/Exceptions.h"

Discount::Discount(const std::string& code, double amount, bool isPercentage, double maxAmount)
        : code(code), isPercentage(isPercentage), maxDiscountAmount(maxAmount) {
            if(amount <= 0) 
                throw ExceptionIncorrectDiscountAmount("Discount amount needs to be positive");
            else
                if(amount >= 100 && isPercentage)
                    throw ExceptionIncorrectDiscountAmount("Discount amount needs to be less than 100");
                else
                    this->amount = amount;
        }

std::string Discount::getCode() const {
    return code;
}

double Discount::getAmount() const {
    return amount;
}

bool Discount::getIsPercentage() const {
    return isPercentage;
}

double Discount::getMaxDiscountAmount() const {
    return maxDiscountAmount;
}

void Discount::setMaxDiscountAmount(double maxAmount) {
    maxDiscountAmount = maxAmount;
}

double Discount::applyDiscount(double total) const {
    if (!isValid()) return total;

    if (isPercentage) {
        double discountAmount = total * (amount / 100.0);
        if (maxDiscountAmount > 0 && discountAmount > maxDiscountAmount) {
            return total - maxDiscountAmount;
        }
        return total - discountAmount;
    } else {
        return (total > amount) ? (total - amount) : 0.0;
    }
}

bool Discount::isValid() const {
    return amount > 0 && (maxDiscountAmount >= 0) &&
           (!isPercentage || (isPercentage && amount <= 100));
}

std::string Discount::getDescription() const {
    if (isPercentage) {
        return std::to_string(static_cast<int>(amount)) + "% off" +
               (maxDiscountAmount > 0 ? " (max " + std::to_string(maxDiscountAmount) + ")" : "");
    } else {
        return "$" + std::to_string(amount) + " off";
    }
}