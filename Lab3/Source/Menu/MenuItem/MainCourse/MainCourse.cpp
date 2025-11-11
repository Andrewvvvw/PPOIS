#include "MainCourse.h"
#include <algorithm>
MainCourse::MainCourse(const std::string& name, double price, bool isAvailable,
                     const std::vector<Ingredient>& ingredients, int cookingTime,
                     const std::string& cuisine, bool isVegetarian, int spicinessLevel,
                     std::shared_ptr<Recipe> recipe)
        : MenuItem(name, price, isAvailable),
          ingredients(ingredients),
          cookingTime(cookingTime),
          cuisine(cuisine),
          isVegetarian(isVegetarian),
          spicinessLevel(spicinessLevel),
          recipe(recipe) {}

void MainCourse::setRecipe(std::shared_ptr<Recipe> newRecipe) {
    recipe = newRecipe;
}

std::shared_ptr<Recipe> MainCourse::getRecipe() const {
    return recipe;
}

bool MainCourse::hasRecipe() const {
    return recipe != nullptr;
}

void MainCourse::addIngredient(const Ingredient& ingredient) {
    ingredients.push_back(ingredient);
}

void MainCourse::removeIngredient(const std::string& ingredientName) {
    ingredients.erase(
            std::remove_if(ingredients.begin(), ingredients.end(),
                           [&ingredientName](const Ingredient& ing) {
                               return ing.getName() == ingredientName;
                           }),
            ingredients.end());
}

bool MainCourse::containsIngredient(const std::string& ingredientName) const {
    return std::any_of(ingredients.begin(), ingredients.end(),
                       [&ingredientName](const Ingredient& ing) {
                           return ing.getName() == ingredientName;
                       });
}

double MainCourse::calculateTotalCalories() const {
    double totalCalories = 0.0;
    for (const auto& ingredient : ingredients) {
        totalCalories += ingredient.getCalories();
    }
    return totalCalories;
}

void MainCourse::setSpiciness(int level) {
    spicinessLevel = std::max(0, std::min(level, 10));
}