#include "UserWallet.h"
#include "../../../../Exceptions/Exceptions.h"
#include "../Payment/Payment.h"
#include <memory>
UserWallet::UserWallet(RegisteredUser* user, double balance) {
    this->user = user;
    this->balance = balance;
}

void UserWallet::addMoney(double amount) {
    balance += amount;
}

void UserWallet::removeMoney(double amount) {
    balance -= amount;
}

void UserWallet::payMonthlyPremium() {
    if(balance < MONTHLY_PREMIUM_COST)
        throw ExceptionNotEnoughMoney("Not enough money");

    Payment payment(MONTHLY_PREMIUM_COST, "monthly payment");
    removeMoney(MONTHLY_PREMIUM_COST);
    this->payments.push_back(std::make_shared<Payment>(payment));
}

std::vector<std::shared_ptr<Payment>> UserWallet::getPayments() const {
    return payments;
}

double UserWallet::getBalance() const {
    return balance;
}

void UserWallet::setBalance(double balance) {
    this->balance = balance;
}
