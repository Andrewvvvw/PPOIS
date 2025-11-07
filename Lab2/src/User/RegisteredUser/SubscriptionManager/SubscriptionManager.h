#ifndef LAB2_SUBSCRIPTIONMANAGER_H
#define LAB2_SUBSCRIPTIONMANAGER_H

#include "../RegisteredUser.h"
#include "UserWallet/UserWallet.h"
#include <memory>

class RegisteredUser;
class UserWallet;

class SubscriptionManager{
private:
    RegisteredUser* user;
    std::unique_ptr<UserWallet> wallet;
    bool hasPremium;
public:
    SubscriptionManager(RegisteredUser* user, std::unique_ptr<UserWallet> wallet);
    ~SubscriptionManager() = default;


    void getPremium();
    void cancelPremium();
    [[nodiscard]] bool checkForPremium() const;
};

#endif //LAB2_SUBSCRIPTIONMANAGER_H
