#ifndef LAB3_INVENTORY_REPORT_H
#define LAB3_INVENTORY_REPORT_H

#include "../Report.h"
#include <map>

class InventoryReport : public Report {
private:
    std::map<int, int> itemQuantities;
    std::map<int, bool> lowStockItems;
    int totalItems;
    double totalValue;

public:
    InventoryReport(const std::string& generatedBy);

    void updateItemQuantity(int itemId, int quantity);
    void markLowStock(int itemId, bool isLowStock);
    void calculateTotalValue(double value);

    void generate() override;
    bool validate() const override;

    int getTotalItems() const;
    double getTotalValue() const;
    const std::map<int, int>& getItemQuantities() const;
};

#endif //LAB3_INVENTORY_REPORT_H
