#include "Table.h"

Table::Table(int id, int capacity, const std::string& location)
        : tableId(id), capacity(capacity), location(location), isOccupied(false) {}

bool Table::canAccommodate(int people) const {
    return !isOccupied && people <= capacity;
}

void Table::occupy() {
    isOccupied = true;
}

void Table::vacate() {
    isOccupied = false;
}

bool Table::isAvailable() const {
    return !isOccupied;
}

bool Table::isSuitableForGroup(int people) const {
    return !isOccupied && (capacity - people) >= -1 && (capacity - people) <= 2;
}