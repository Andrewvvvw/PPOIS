#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include <vector>
#include "MenuItem/MenuItem.h"

class Menu {
private:
    std::vector <MenuItem> items;
    std::string name;
    int maxItems;

public:
    Menu(const std::string& name, int maxItems = 50);

    const std::string& getName() const;
    int getMaxItems() const;
    std::vector <MenuItem> getItems() const;

    bool addItem(const MenuItem& item);
    bool removeItem(const std::string& itemName);

    std::vector<MenuItem> getAvailableItems() const;
    double getAveragePrice() const;

    void applyGlobalDiscount(double discountPercentage);
    std::vector<std::string> getItemNames() const;
};

#endif //LAB3_MENU_H
