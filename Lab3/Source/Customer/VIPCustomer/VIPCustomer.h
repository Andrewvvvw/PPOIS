#ifndef LAB3_VIPCUSTOMER_H
#define LAB3_VIPCUSTOMER_H

#include "../Customer.h"
#include <vector>
#include <string>

class VIPCustomer : public Customer {
    std::string personalManager;
    double creditLimit;
    std::vector <int> reservedItems;

public:
    VIPCustomer(const std::string& name, int id, const std::string& manager, double limit = 10000.0);
    void increaseCreditLimit(double amount);
    void reserveItem(int itemId);
    void setPersonalManager(const std::string& manager);
};

#endif //LAB3_VIPCUSTOMER_H
