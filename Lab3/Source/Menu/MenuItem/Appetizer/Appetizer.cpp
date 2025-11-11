#include "Appetizer.h"

Appetizer::Appetizer(const std::string& name, double price, bool isAvailable,
                   int spiceLevel, bool isVegetarian, int calories,
                   std::shared_ptr<Recipe> recipe)
    : MenuItem(name, price, isAvailable),
      spiceLevel(spiceLevel >= 0 ? (spiceLevel <= 10 ? spiceLevel : 10) : 0),
      isVegetarian(isVegetarian),
      calories(calories >= 0 ? calories : 0),
      recipe(recipe) {}

void Appetizer::setRecipe(std::shared_ptr<Recipe> newRecipe) {
    recipe = newRecipe;
}

std::shared_ptr<Recipe> Appetizer::getRecipe() const {
    return recipe;
}

bool Appetizer::hasRecipe() const {
    return recipe != nullptr;
}

void Appetizer::increaseSpiceLevel() {
    if (spiceLevel < 10) {
        spiceLevel++;
    }
}

bool Appetizer::isHighCalorie(int threshold) const {
    return calories > threshold;
}

int Appetizer::getSpiceLevel() const {
    return spiceLevel;
}

bool Appetizer::getIsVegetarian() const {
    return isVegetarian;
}

int Appetizer::getCalories() const {
    return calories;
}

void Appetizer::setSpiceLevel(int level) {
    if (level >= 0 && level <= 10) {
        spiceLevel = level;
    }
}

void Appetizer::setIsVegetarian(bool vegetarian) {
    isVegetarian = vegetarian;
}

void Appetizer::setCalories(int cal) {
    if (cal >= 0) {
        calories = cal;
    }
}