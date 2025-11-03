#include "RegisteredUser.h"
#include <algorithm>
#include <string>

RegisteredUser::RegisteredUser(const std::string& id, const std::string& username,
                               const std::string& email, const std::string& password)
        : User(id, username), email(email) {
    setPassword(password);
}

void RegisteredUser::setPassword(const std::string& newPassword) {
    password = newPassword;
}

bool RegisteredUser::verifyPassword(const std::string& inputPassword) const {
    return this->password == inputPassword;
}

bool RegisteredUser::getIsPremium() const {
    return this->subscriptionManager.checkForPremium();
}

void RegisteredUser::setPremium(bool premium) {
    premium ? this->subscriptionManager.getPremium() : this->subscriptionManager.cancelPremium();
}
