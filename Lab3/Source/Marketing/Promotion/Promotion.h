#ifndef LAB3_PROMOTION_H
#define LAB3_PROMOTION_H
#include <string>
#include <chrono>
#include "../../Order/Discount/Discount.h"

class Promotion {
private:
    int id;
    std::string name;
    std::string description;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    std::string discountCode;
    double discountPercentage;
    double maxDiscountAmount;

public:
    Promotion(int id, const std::string& name, const std::string& description,
              const std::chrono::system_clock::time_point& startDate,
              const std::chrono::system_clock::time_point& endDate,
              const std::string& discountCode,
              double discountPercentage,
              double maxDiscountAmount = 0.0);

    bool isActive() const;
    Discount createDiscount() const;
    bool isExpired() const;
    bool validate() const;
    void extendPromotion(int days);

    int getId() const;
    const std::string& getName() const;
    const std::string& getDiscountCode() const;
};
#endif //LAB3_PROMOTION_H
