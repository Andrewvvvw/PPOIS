#ifndef LAB2_USERWALLET_H
#define LAB2_USERWALLET_H

#include "../SubscriptionManager.h"
#include "../../RegisteredUser.h"
#include <memory>
constexpr double MONTHLY_PREMIUM_COST = 10;
class Payment;

class UserWallet{
private:
    RegisteredUser* user;
    double balance;

    std::vector <std::shared_ptr<Payment> > payments;

public:
    UserWallet(RegisteredUser* user, double balance);

    void addMoney(double amount);
    void removeMoney(double amount);

    [[nodiscard]] double getBalance() const;
    void setBalance(double balance);

    void payMonthlyPremium();
    std::vector<std::shared_ptr<Payment> > getPayments() const;
};

#endif //LAB2_USERWALLET_H
