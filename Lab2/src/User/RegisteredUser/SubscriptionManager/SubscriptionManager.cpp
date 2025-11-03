#include "SubscriptionManager.h"

SubscriptionManager::SubscriptionManager(RegisteredUser *user, UserWallet *userWallet) {
    this->user = user;
    this->userWallet = userWallet;
    hasPremium = false;
}

void SubscriptionManager::getPremium() {
    if (hasPremium) {
        throw std::runtime_error("User already has premium");
    }
    userWallet->payMonthlyPremium();
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
