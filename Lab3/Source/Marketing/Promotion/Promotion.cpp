#include "Promotion.h"
#include <chrono>

Promotion::Promotion(int id, const std::string& name, const std::string& description,
                     const std::chrono::system_clock::time_point& startDate,
                     const std::chrono::system_clock::time_point& endDate,
                     const std::string& discountCode,
                     double discountPercentage,
                     double maxDiscountAmount)
        : id(id), name(name), description(description),
          startDate(startDate), endDate(endDate),
          discountCode(discountCode),
          discountPercentage(discountPercentage),
          maxDiscountAmount(maxDiscountAmount) {}

bool Promotion::isActive() const {
    auto now = std::chrono::system_clock::now();
    return now >= startDate && now <= endDate;
}

Discount Promotion::createDiscount() const {
    return Discount(discountCode, discountPercentage, true, maxDiscountAmount);
}

bool Promotion::isExpired() const {
    return std::chrono::system_clock::now() > endDate;
}

bool Promotion::validate() const {
    return !name.empty() &&
           !discountCode.empty() &&
           discountPercentage > 0 &&
           discountPercentage <= 100 &&
           startDate < endDate;
}

void Promotion::extendPromotion(int days) {
    endDate += std::chrono::hours(24 * days);
}

int Promotion::getId() const {
    return id;
}

const std::string& Promotion::getName() const {
    return name;
}

const std::string& Promotion::getDiscountCode() const {
    return discountCode;
}
