#ifndef LAB3_BILLSPLITTER_H
#define LAB3_BILLSPLITTER_H

#include <vector>
#include <map>
#include "../../Customer/Customer.h"

class BillSplitter {
    std::map<const Customer*, double> individualBills;
    double totalBill;
    double serviceCharge;
    int numberOfPeople;

public:
    BillSplitter(double total, double service = 0.0, int people = 1);

    void splitBill(const std::vector<Customer*>& customers);
    void addItem(const Customer* customer, double amount);
    void applyServiceCharge();
    double getCustomerShare(const Customer* customer) const;

private:
    double calculateEqualShare() const;
    void distributeRemainder(double amount);
};

#endif //LAB3_BILLSPLITTER_H
