#include "Dessert.h"

Dessert::Dessert(const std::string& name, double price, bool isGlutenFree,
                 bool isVegan, int calories, const std::string& mainIngredient,
                 float sweetnessLevel, bool isAvailable,
                 std::shared_ptr<Recipe> recipe)
        : MenuItem(name, price, isAvailable),
         isGlutenFree(isGlutenFree),
         isVegan(isVegan),
         calories(calories),
         mainIngredient(mainIngredient),
         sweetnessLevel(sweetnessLevel),
         recipe(recipe) {}

void Dessert::setRecipe(std::shared_ptr<Recipe> newRecipe) {
    recipe = newRecipe;
}

std::shared_ptr<Recipe> Dessert::getRecipe() const {
    return recipe;
}

bool Dessert::hasRecipe() const {
    return recipe != nullptr;
}

bool Dessert::getIsGlutenFree() const {
    return isGlutenFree;
}

bool Dessert::getIsVegan() const {
    return isVegan;
}

int Dessert::getCalories() const {
    return calories;
}

std::string Dessert::getMainIngredient() const {
    return mainIngredient;
}

float Dessert::getSweetnessLevel() const {
    return sweetnessLevel;
}

void Dessert::setSweetnessLevel(float level) {
    level <= 0 ? sweetnessLevel = 0 : (level >= 10 ? sweetnessLevel = 10 : sweetnessLevel = level);
}

void Dessert::reduceCalories(int amount) {
    if (amount > 0 && calories > amount) {
        calories -= amount;
    }
}

bool Dessert::isHealthyOption() const {
    return calories < 300 && isGlutenFree && sweetnessLevel <= 5.0f;
}

void Dessert::makeGlutenFree() {
    isGlutenFree = true;
}

std::vector<std::string> Dessert::getDietaryInfo() const {
    std::vector<std::string> info;
    if (isGlutenFree) info.push_back("Gluten-Free");
    if (isVegan) info.push_back("Vegan");
    if (calories < 300) info.push_back("Low-Calorie");
    return info;
}