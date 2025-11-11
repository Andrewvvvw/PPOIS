#ifndef LAB3_INVENTORY_H
#define LAB3_INVENTORY_H
#include "StockItem/StockItem.h"
#include <vector>
#include <string>

class Inventory {
    std::vector<StockItem> items;
    std::string location;
    int maxCapacity;
    std::string manager;
    std::string lastUpdated;

public:
    Inventory(const std::string& location, int maxCapacity, const std::string& manager);

    void addItem(const StockItem& item);
    bool removeItem(const std::string& itemName);
    StockItem* findItem(const std::string& itemName);
    std::vector<StockItem> getLowStockItems() const;
    void updateStockLevel(const std::string& itemName, double amount);

    std::string getLocation() const;
    int getMaxCapacity() const;
    std::string getManager() const;
    std::string getLastUpdated() const;
    int getItemCount() const;
};
#endif //LAB3_INVENTORY_H
