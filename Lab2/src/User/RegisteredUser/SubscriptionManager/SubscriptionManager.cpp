#include "SubscriptionManager.h"
#include <stdexcept>

SubscriptionManager::SubscriptionManager(RegisteredUser* user, std::unique_ptr<UserWallet> wallet)
        : user(user), wallet(std::move(wallet)), hasPremium(false) {
    if (!user || !this->wallet) {
        throw std::invalid_argument("User and wallet cannot be null");
    }
}

void SubscriptionManager::getPremium() {
    if (hasPremium) {
        throw std::runtime_error("User already has premium");
    }
    wallet->payMonthlyPremium();
    hasPremium = true;
}

void SubscriptionManager::cancelPremium() {
    if (!hasPremium) {
        throw std::runtime_error("User doesn't have premium");
    }
    hasPremium = false;
}

bool SubscriptionManager::checkForPremium() const {
    return this->hasPremium;
}
