#include "LoyaltyProgram.h"

const double LoyaltyProgram::POINTS_PER_CURRENCY = 0.1;
const double LoyaltyProgram::SILVER_THRESHOLD = 1000.0;
const double LoyaltyProgram::GOLD_THRESHOLD = 5000.0;
const double LoyaltyProgram::SILVER_DISCOUNT = 0.05;
const double LoyaltyProgram::GOLD_DISCOUNT = 0.1;

LoyaltyProgram::LoyaltyProgram() = default;

void LoyaltyProgram::addPoints(int customerId, double amountSpent) {
    if (amountSpent > 0) {
        customerPoints[customerId] += amountSpent * POINTS_PER_CURRENCY;
    }
}

bool LoyaltyProgram::redeemPoints(int customerId, double pointsToRedeem) {
    if (customerPoints[customerId] >= pointsToRedeem && pointsToRedeem > 0) {
        customerPoints[customerId] -= pointsToRedeem;
        return true;
    }
    return false;
}

double LoyaltyProgram::getAvailablePoints(int customerId) const {
    auto it = customerPoints.find(customerId);
    return it != customerPoints.end() ? it->second : 0.0;
}

LoyaltyProgram::Tier LoyaltyProgram::determineTier(double totalSpent) const {
    if (totalSpent >= GOLD_THRESHOLD) {
        return Tier::GOLD;
    } else if (totalSpent >= SILVER_THRESHOLD) {
        return Tier::SILVER;
    }
    return Tier::REGULAR;
}

double LoyaltyProgram::calculateDiscount(int customerId) const {
    auto it = customerPoints.find(customerId);
    if (it == customerPoints.end()) return 0.0;

    double totalSpent = it->second / POINTS_PER_CURRENCY;
    Tier tier = determineTier(totalSpent);

    switch (tier) {
        case Tier::SILVER: return SILVER_DISCOUNT;
        case Tier::GOLD: return GOLD_DISCOUNT;
        default: return 0.0;
    }
}

std::string LoyaltyProgram::getTierName(int customerId) const {
    auto it = customerPoints.find(customerId);
    if (it == customerPoints.end()) return "Regular";

    double totalSpent = it->second / POINTS_PER_CURRENCY;
    Tier tier = determineTier(totalSpent);

    switch (tier) {
        case Tier::SILVER: return "Silver";
        case Tier::GOLD: return "Gold";
        default: return "Regular";
    }
}

void LoyaltyProgram::updateCustomerSpending(int customerId, double amount) {
    if (amount > 0) {
        customerPoints[customerId] += amount * POINTS_PER_CURRENCY;
    }
}
