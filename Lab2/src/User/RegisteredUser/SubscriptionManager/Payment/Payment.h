#ifndef LAB2_PAYMENT_H
#define LAB2_PAYMENT_H

#include "string"
#include "../UserWallet/UserWallet.h"

class Payment{
private:
    double amount;
    std::string description;
public:
    Payment(double amount, std::string description);

};

#endif //LAB2_PAYMENT_H
