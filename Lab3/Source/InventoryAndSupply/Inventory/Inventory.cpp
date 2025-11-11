#include "Inventory.h"
#include <ctime>
#include <algorithm>
#include "../../Exceptions/Exceptions.h"

Inventory::Inventory(const std::string& location, int maxCapacity, const std::string& manager)
        : location(location), manager(manager) {
    time_t now = time(0);
    lastUpdated = ctime(&now);
    if(maxCapacity < 0)
        throw ExceptionNegativeCapacity("Capacity can't be negative");
    else
        this->maxCapacity = maxCapacity;
}

void Inventory::addItem(const StockItem& item) {
    if (items.size() < maxCapacity) {
        items.push_back(item);
        time_t now = time(0);
        lastUpdated = ctime(&now);
    }
}

bool Inventory::removeItem(const std::string& itemName) {
    auto it = std::remove_if(items.begin(), items.end(),
                             [&itemName](const StockItem& item) { return item.getName() == itemName; });

    if (it != items.end()) {
        items.erase(it, items.end());
        time_t now = time(0);
        lastUpdated = ctime(&now);
        return true;
    }
    return false;
}

StockItem* Inventory::findItem(const std::string& itemName) {
    for (auto& item : items) {
        if (item.getName() == itemName) {
            return &item;
        }
    }
    return nullptr;
}

std::vector<StockItem> Inventory::getLowStockItems() const {
    std::vector<StockItem> lowStock;
    for (const auto& item : items) {
        if (item.needsRestocking()) {
            lowStock.push_back(item);
        }
    }
    return lowStock;
}

void Inventory::updateStockLevel(const std::string& itemName, double amount) {
    for (auto& item : items) {
        if (item.getName() == itemName) {
            item.addQuantity(amount);
            time_t now = time(0);
            lastUpdated = ctime(&now);
            break;
        }
    }
}

std::string Inventory::getLocation() const {
    return location;
}

int Inventory::getMaxCapacity() const {
    return maxCapacity;
}

std::string Inventory::getManager() const {
    return manager;
}

std::string Inventory::getLastUpdated() const {
    return lastUpdated;
}

int Inventory::getItemCount() const {
    return static_cast<int>(items.size());
}