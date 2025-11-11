#include "MenuItem.h"
#include <algorithm>

MenuItem::MenuItem(const std::string& name, double price, bool isAvailable)
    : name(name), price(price), isAvailable(isAvailable) {}

std::string MenuItem::getName() const {
    return name;
}

double MenuItem::getPrice() const {
    return price;
}

bool MenuItem::getIsAvailable() const {
    return isAvailable;
}

void MenuItem::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    }
}

void MenuItem::setIsAvailable(bool available) {
    isAvailable = available;
}

bool MenuItem::isPriceAboveAverage(double averagePrice) const {
    return price > averagePrice;
}

void MenuItem::applyDiscount(double discountPercentage) {
    if (discountPercentage > 0 && discountPercentage <= 100) {
        price *= (100 - discountPercentage) / 100.0;
    }
}

void MenuItem::addAllergen(const AllergenInfo& allergen) {
    if (!containsAllergen(allergen.getName())) {
        allergens.push_back(allergen);
    }
}

bool MenuItem::removeAllergen(const std::string& allergenName) {
    auto it = std::remove_if(allergens.begin(), allergens.end(),
                             [&allergenName](const AllergenInfo& a) {
                                 return a.getName() == allergenName;
                             });

    if (it != allergens.end()) {
        allergens.erase(it, allergens.end());
        return true;
    }
    return false;
}

bool MenuItem::containsAllergen(const std::string& allergenName) const {
    return std::any_of(allergens.begin(), allergens.end(),
                       [&allergenName](const AllergenInfo& a) {
                           return a.getName() == allergenName ||
                                  a.hasAlternative(allergenName);
                       });
}

const std::vector<AllergenInfo>& MenuItem::getAllergens() const {
    return allergens;
}

bool MenuItem::hasSevereAllergens() const {
    return std::any_of(allergens.begin(), allergens.end(),
                       [](const AllergenInfo& a) {
                           return a.isSevere();
                       });
}