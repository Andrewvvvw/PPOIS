#ifndef LAB3_LOYALTYPROGRAM_H
#define LAB3_LOYALTYPROGRAM_H

#include "../../Customer/Customer.h"
#include <map>
#include <string>

class LoyaltyProgram {
private:
    static const double POINTS_PER_CURRENCY;
    static const double SILVER_THRESHOLD;
    static const double GOLD_THRESHOLD;
    static const double SILVER_DISCOUNT;
    static const double GOLD_DISCOUNT;

    std::map <int, double> customerPoints;

    enum class Tier { REGULAR, SILVER, GOLD };

    Tier determineTier(double totalSpent) const;

public:
    LoyaltyProgram();

    void addPoints(int customerId, double amountSpent);
    bool redeemPoints(int customerId, double pointsToRedeem);
    double getAvailablePoints(int customerId) const;
    double calculateDiscount(int customerId) const;
    std::string getTierName(int customerId) const;

    void updateCustomerSpending(int customerId, double amount);
};

#endif //LAB3_LOYALTYPROGRAM_H
