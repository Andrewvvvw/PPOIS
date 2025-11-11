#include "PurchaseOrder.h"
#include <algorithm>
#include "../../Exceptions/Exceptions.h"

PurchaseOrder::PurchaseOrder(const std::string& orderId, const std::string& supplierId, const std::string& orderDate)
    : orderId(orderId), supplierId(supplierId), orderDate(orderDate), status("Pending") {}

void PurchaseOrder::addItem(const StockItem& item) {
    items.push_back(item);
}

bool PurchaseOrder::removeItem(const std::string& itemName) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&itemName](const StockItem& item) { return item.getName() == itemName; });

    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

void PurchaseOrder::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

double PurchaseOrder::calculateTotalCost() const {
    if(this->items.empty())
        throw ExceptionEmptyOrder("Order can't be empty");
        
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getQuantity() * item.getMinStockLevel();
    }
    return total;
}

bool PurchaseOrder::containsItem(const std::string& itemName) const {
    return std::any_of(items.begin(), items.end(),
        [&itemName](const StockItem& item) { return item.getName() == itemName; });
}

std::string PurchaseOrder::getOrderId() const {
    return orderId;
}

std::string PurchaseOrder::getSupplierId() const {
    return supplierId;
}

std::string PurchaseOrder::getOrderDate() const {
    return orderDate;
}

std::string PurchaseOrder::getStatus() const {
    return status;
}

const std::vector<StockItem>& PurchaseOrder::getItems() const {
    return items;
}
