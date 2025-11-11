#ifndef LAB3_PURCHASEORDER_H
#define LAB3_PURCHASEORDER_H

#include "../Inventory/StockItem/StockItem.h"
#include <vector>
#include <string>

class PurchaseOrder {
    std::string orderId;
    std::string supplierId;
    std::vector <StockItem> items;
    std::string orderDate;
    std::string status;

public:
    PurchaseOrder(const std::string& orderId, const std::string& supplierId, const std::string& orderDate);

    void addItem(const StockItem& item);
    bool removeItem(const std::string& itemName);
    void updateStatus(const std::string& newStatus);
    double calculateTotalCost() const;
    bool containsItem(const std::string& itemName) const;

    std::string getOrderId() const;
    std::string getSupplierId() const;
    std::string getOrderDate() const;
    std::string getStatus() const;
    const std::vector<StockItem>& getItems() const;
};

#endif //LAB3_PURCHASEORDER_H
