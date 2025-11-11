#include "OrderItem.h"
#include "../../Exceptions/Exceptions.h"

OrderItem::OrderItem(const std::string& name, int qty, double price)
    : dishName(name), quantity(qty), pricePerItem(price) {
        if(price <= 0) {
            throw ExceptionIncorrectItemPrice("Item price must be positive");
        }
}

std::string OrderItem::getDishName() const {
    return dishName;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getPricePerItem() const {
    return pricePerItem;
}

void OrderItem::setQuantity(int newQuantity) {
    if (newQuantity > 0) {
        quantity = newQuantity;
    }
}

double OrderItem::calculateItemTotal() const {
    return pricePerItem * quantity;
}
