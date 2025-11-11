#include "StockItem.h"
#include "../../../Exceptions/Exceptions.h"

StockItem::StockItem(const std::string& name, const std::string& category, double quantity,
                     const std::string& unit, double minStockLevel)
        : name(name), category(category), unit(unit) {
            if(quantity < 0)
                throw ExceptionNegativeQuantity("Quantity can't be negative");
            else
                this->quantity = quantity;
            
            if(minStockLevel < 0)
                throw ExceptionNegativeStockMinimum("MinStockLevel can't be negative");
            else
                this->minStockLevel = minStockLevel;
        }

void StockItem::addQuantity(double amount) {
    quantity += amount;
    if (quantity < 0) quantity = 0;
}

bool StockItem::needsRestocking() const {
    return quantity <= minStockLevel;
}

void StockItem::updateMinStockLevel(double newLevel) {
    minStockLevel = newLevel > 0 ? newLevel : 0;
}

double StockItem::calculateDaysLeft(double dailyUsage) const {
    return dailyUsage > 0 ? quantity / dailyUsage : 0;
}

void StockItem::setCategory(const std::string& newCategory) {
    category = newCategory;
}

std::string StockItem::getName() const {
    return name;
}

std::string StockItem::getCategory() const {
    return category;
}

double StockItem::getQuantity() const {
    return quantity;
}

std::string StockItem::getUnit() const {
    return unit;
}

double StockItem::getMinStockLevel() const {
    return minStockLevel;
}