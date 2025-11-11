#include "InventoryReport.h"

InventoryReport::InventoryReport(const std::string& generatedBy)
    : Report("Inventory Report", generatedBy), totalItems(0), totalValue(0.0) {}

void InventoryReport::updateItemQuantity(int itemId, int quantity) {
    if (itemId <= 0 || quantity < 0) return;

    auto it = itemQuantities.find(itemId);
    if (it != itemQuantities.end()) {
        totalItems = totalItems - it->second + quantity;
    } else {
        totalItems += quantity;
    }

    itemQuantities[itemId] = quantity;
}

void InventoryReport::markLowStock(int itemId, bool isLowStock) {
    if (itemId <= 0) return;
    lowStockItems[itemId] = isLowStock;
}

void InventoryReport::calculateTotalValue(double value) {
    if (value >= 0) {
        totalValue = value;
    }
}

void InventoryReport::generate() {
    isFinalized = true;
}

bool InventoryReport::validate() const {
    return Report::validate() && totalItems >= 0 && totalValue >= 0;
}

int InventoryReport::getTotalItems() const {
    return totalItems;
}

double InventoryReport::getTotalValue() const {
    return totalValue;
}

const std::map<int, int>& InventoryReport::getItemQuantities() const {
    return itemQuantities;
}
