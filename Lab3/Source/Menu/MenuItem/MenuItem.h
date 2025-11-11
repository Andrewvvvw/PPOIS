#ifndef LAB3_MENUITEM_H
#define LAB3_MENUITEM_H

#include <string>
#include <vector>
#include "AllergenInfo/AllergenInfo.h"

class MenuItem {
private:
    std::string name;
    double price;
    bool isAvailable;
    std::vector <AllergenInfo> allergens;

public:
    MenuItem(const std::string& name, double price, bool isAvailable = true);

    std::string getName() const;
    double getPrice() const;
    bool getIsAvailable() const;

    void setPrice(double newPrice);
    void setIsAvailable(bool available);

    bool isPriceAboveAverage(double averagePrice) const;
    void applyDiscount(double discountPercentage);

    void addAllergen(const AllergenInfo& allergen);
    bool removeAllergen(const std::string& allergenName);
    bool containsAllergen(const std::string& allergenName) const;
    const std::vector<AllergenInfo>& getAllergens() const;
    bool hasSevereAllergens() const;
};

#endif //LAB3_MENUITEM_H
