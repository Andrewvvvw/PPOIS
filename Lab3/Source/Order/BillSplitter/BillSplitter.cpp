#include "BillSplitter.h"
#include <stdexcept>
#include "../../Exceptions/Exceptions.h"

BillSplitter::BillSplitter(double total, double service, int people)
    : totalBill(total), serviceCharge(service), numberOfPeople(people) {
    if (totalBill < 0)
        throw ExceptionNegativeBillTotal("Bill total can't be negative");
    else 
        if (serviceCharge < 0)
            throw ExceptionNegativeServiceCharge("Service charge can't be negative");
        else
            if (numberOfPeople <= 0)
                throw ExceptionIncorrectCustomerAmount("Number of people must be positive");

}

void BillSplitter::splitBill(const std::vector<Customer*>& customers) {
    individualBills.clear();
    if (customers.empty()) return;

    double equalShare = calculateEqualShare();
    for (const auto& customer : customers) {
        individualBills[customer] = equalShare;
    }

    distributeRemainder(totalBill - (equalShare * customers.size()));
}

void BillSplitter::addItem(const Customer* customer, double amount) {
    if (amount < 0) {
        throw ExceptionNegativeItemAmount("Amount cannot be negative");
    }
    individualBills[customer] += amount;
    totalBill += amount;
}

void BillSplitter::applyServiceCharge() {
    if (serviceCharge <= 0) return;

    double chargePerPerson = (totalBill * serviceCharge) / numberOfPeople;
    for (auto& [customer, amount] : individualBills) {
        amount += chargePerPerson;
    }
}

double BillSplitter::getCustomerShare(const Customer* customer) const {
    auto it = individualBills.find(customer);
    if (it != individualBills.end()) {
        return it->second;
    }
    return 0.0;
}

double BillSplitter::calculateEqualShare() const {
    return numberOfPeople > 0 ? totalBill / numberOfPeople : 0.0;
}

void BillSplitter::distributeRemainder(double remainder) {
    if (remainder == 0.0 || individualBills.empty()) return;

    double perPerson = remainder / individualBills.size();
    for (auto& [customer, amount] : individualBills) {
        amount += perPerson;
    }
}
