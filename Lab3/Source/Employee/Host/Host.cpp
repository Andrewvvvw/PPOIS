#include "Host.h"

Host::Host(const std::string& name, double hourlyRate, int maxTables)
    : Employee(name, "Host", hourlyRate), maxTables(maxTables > 0 ? maxTables : 1) {}

std::string Host::getRole() const {
    return "Host";
}

void Host::assignTable(int tableNumber) {
    if (assignedTables.size() < static_cast<size_t>(maxTables) &&
        !isTableAssigned(tableNumber)) {
        assignedTables.push_back(tableNumber);
    }
}

void Host::freeTable(int tableNumber) {
    auto it = std::find(assignedTables.begin(), assignedTables.end(), tableNumber);
    if (it != assignedTables.end()) {
        assignedTables.erase(it);
    }
}

bool Host::isTableAssigned(int tableNumber) const {
    return std::find(assignedTables.begin(), assignedTables.end(), tableNumber) != assignedTables.end();
}

int Host::getAssignedTablesCount() const {
    return static_cast<int>(assignedTables.size());
}
