#include "Ingredient.h"

Ingredient::Ingredient(const std::string& name, double quantity, const std::string& unit,
                       double calories, double price)
        : name(name), quantity(quantity), unit(unit), calories(calories), price(price) {}

std::string Ingredient::getName() const {
    return name;
}

double Ingredient::getQuantity() const {
    return quantity;
}

std::string Ingredient::getUnit() const {
    return unit;
}

double Ingredient::getCalories() const {
    return calories;
}

double Ingredient::getPrice() const {
    return price;
}

void Ingredient::setQuantity(double newQuantity) {
    quantity = newQuantity;
}

void Ingredient::setPrice(double newPrice) {
    price = newPrice;
}

bool Ingredient::isLowInStock(double threshold) const {
    return quantity < threshold;
}

double Ingredient::calculateTotalCalories() const {
    return quantity * calories;
}

bool Ingredient::isExpensive(double priceThreshold) const {
    return price > priceThreshold;
}

void Ingredient::scaleQuantity(double factor) {
    quantity *= factor;
}