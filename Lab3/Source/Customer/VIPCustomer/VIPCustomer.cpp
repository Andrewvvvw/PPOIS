#include "VIPCustomer.h"

VIPCustomer::VIPCustomer(const std::string& name, int id, const std::string& manager, double limit)
    : Customer(name, id), personalManager(manager), creditLimit(limit) {}

void VIPCustomer::increaseCreditLimit(double amount) {
    if (amount > 0) {
        creditLimit += amount;
    }
}

void VIPCustomer::reserveItem(int itemId) {
    if (std::find(reservedItems.begin(), reservedItems.end(), itemId) == reservedItems.end()) {
        reservedItems.push_back(itemId);
    }
}

void VIPCustomer::setPersonalManager(const std::string& manager) {
    personalManager = manager;
}

