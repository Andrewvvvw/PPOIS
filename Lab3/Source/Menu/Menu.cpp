#include "Menu.h"
#include <algorithm>

Menu::Menu(const std::string& name, int maxItems)
    : name(name), maxItems(maxItems > 0 ? maxItems : 50) {}

bool Menu::addItem(const MenuItem& item) {
    if (items.size() >= maxItems) {
        return false;
    }
    items.push_back(item);
    return true;
}

bool Menu::removeItem(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const MenuItem& item) {
            return item.getName() == itemName;
        });

    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

std::vector<MenuItem> Menu::getAvailableItems() const {
    std::vector<MenuItem> availableItems;
    for (const auto& item : items) {
        if (item.getIsAvailable()) {
            availableItems.push_back(item);
        }
    }
    return availableItems;
}

double Menu::getAveragePrice() const {
    if (items.empty()) return 0.0;

    double total = 0.0;
    for (const auto& item : items) {
        total += item.getPrice();
    }
    return total / items.size();
}

void Menu::applyGlobalDiscount(double discountPercentage) {
    if (discountPercentage <= 0 || discountPercentage > 100) return;

    for (auto& item : items) {
        item.applyDiscount(discountPercentage);
    }
}

std::vector<std::string> Menu::getItemNames() const {
    std::vector<std::string> names;
    for (const auto& item : items) {
        names.push_back(item.getName());
    }
    return names;
}

const std::string& Menu::getName() const {
    return name;
}

int Menu::getMaxItems() const {
    return maxItems;
}

std::vector <MenuItem> Menu::getItems() const {
    return items;
}
