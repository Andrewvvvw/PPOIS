#ifndef LAB3_ORDERITEM_H
#define LAB3_ORDERITEM_H

#include <string>

class OrderItem {
private:
    std::string dishName;
    int quantity;
    double pricePerItem;

public:
    OrderItem(const std::string& name, int qty, double price);

    std::string getDishName() const;
    int getQuantity() const;
    double getPricePerItem() const;

    void setQuantity(int newQuantity);
    double calculateItemTotal() const;
};

#endif //LAB3_ORDERITEM_H
