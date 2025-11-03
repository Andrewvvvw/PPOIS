#ifndef LAB2_SUBSCRIPTIONMANAGER_H
#define LAB2_SUBSCRIPTIONMANAGER_H

#include "../RegisteredUser.h"
#include "UserWallet/UserWallet.h"

class SubscriptionManager{
private:
    RegisteredUser* user;
    UserWallet* userWallet;
    bool hasPremium;
public:
    SubscriptionManager(RegisteredUser* user, UserWallet* userWallet);

    void getPremium();
    void cancelPremium();
    [[nodiscard]] bool checkForPremium() const;
};

#endif //LAB2_SUBSCRIPTIONMANAGER_H
