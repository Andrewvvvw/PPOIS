#ifndef LAB3_INGREDIENT_H
#define LAB3_INGREDIENT_H
#include <string>

class Ingredient {
private:
    std::string name;
    double quantity;
    std::string unit;
    double calories;
    double price;

public:
    Ingredient(const std::string& name, double quantity, const std::string& unit,
               double calories, double price);

    std::string getName() const;
    double getQuantity() const;
    std::string getUnit() const;
    double getCalories() const;
    double getPrice() const;

    void setQuantity(double newQuantity);
    void setPrice(double newPrice);

    bool isLowInStock(double threshold) const;
    double calculateTotalCalories() const;
    bool isExpensive(double priceThreshold) const;
    void scaleQuantity(double factor);
};
#endif //LAB3_INGREDIENT_H
