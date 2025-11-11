#include "Customer.h"

Customer::Customer(const std::string& name, int id, double totalSpent)
        : name(name), id(id), totalSpent(totalSpent) {}

std::string Customer::getName() const {
    return name;
}
int Customer::getId() const {
    return id;
}
double Customer::getTotalSpent() const {
    return totalSpent;
}
void Customer::setTotalSpent(double amount) {
    totalSpent = amount;
}