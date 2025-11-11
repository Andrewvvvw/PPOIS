#include "Drink.h"

Drink::Drink(const std::string& name, double price, double volume, bool isAlcoholic, const Ingredient& ingredient, std::shared_ptr<Recipe> recipe)
        : MenuItem(name, price, true), volume(volume), isAlcoholic(isAlcoholic), mainIngredient(ingredient), recipe(recipe) {}

void Drink::setRecipe(std::shared_ptr<Recipe> newRecipe) {
    recipe = newRecipe;
}

std::shared_ptr<Recipe> Drink::getRecipe() const {
    return recipe;
}

bool Drink::hasRecipe() const {
    return recipe != nullptr;
}

double Drink::getVolume() const {
    return volume;
}

bool Drink::getIsAlcoholic() const {
    return isAlcoholic;
}

const Ingredient& Drink::getMainIngredient() const {
    return mainIngredient;
}

void Drink::setVolume(double newVolume) {
    if (newVolume > 0) {
        volume = newVolume;
    }
}

void Drink::setIsAlcoholic(bool alcoholic) {
    isAlcoholic = alcoholic;
}

void Drink::changeMainIngredient(const Ingredient& newIngredient) {
    mainIngredient = newIngredient;
}