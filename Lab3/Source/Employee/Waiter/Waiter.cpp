#include "Waiter.h"

Waiter::Waiter(const std::string& name, double hourlyRate, int yearsOfExperience)
    : Employee(name, "Waiter", hourlyRate), tablesServed(0), totalTips(0.0), currentTable(-1) {
    setYearsOfExperience(yearsOfExperience);
}

void Waiter::assignTable(int tableNumber) {
    currentTable = tableNumber;
    tablesServed++;
}

void Waiter::addOrder(Order* order) {
    if (order) {
        activeOrders.push_back(order);
    }
}

void Waiter::completeOrder(Order* order) {
    auto it = std::find(activeOrders.begin(), activeOrders.end(), order);
    if (it != activeOrders.end()) {
        activeOrders.erase(it);
    }
}

void Waiter::receiveTip(double amount) {
    if (amount > 0) {
        totalTips += amount;
    }
}

std::string Waiter::getRole() const {
    return "Waiter";
}

int Waiter::getCurrentTable() const {
    return currentTable;
}

int Waiter::getTablesServed() const {
    return tablesServed;
}

size_t Waiter::getActiveOrdersCount() const {
    return activeOrders.size();
}

double Waiter::getTotalTips() const {
    return totalTips;
}
