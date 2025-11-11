#ifndef LAB3_MAINCOURSE_H
#define LAB3_MAINCOURSE_H

#include "../MenuItem.h"
#include "../Ingredient/Ingredient.h"
#include "../Recipe/Recipe.h"
#include <vector>
#include <string>
#include <memory>

class MainCourse : public MenuItem {
private:
    std::vector<Ingredient> ingredients;
    int cookingTime;
    std::string cuisine;
    bool isVegetarian;
    int spicinessLevel;
    std::shared_ptr<Recipe> recipe;

public:
    MainCourse(const std::string& name, double price, bool isAvailable,
               const std::vector<Ingredient>& ingredients, int cookingTime,
               const std::string& cuisine, bool isVegetarian, int spicinessLevel,
               std::shared_ptr<Recipe> recipe = nullptr);

    void setRecipe(std::shared_ptr<Recipe> newRecipe);
    std::shared_ptr<Recipe> getRecipe() const;
    bool hasRecipe() const;

    void addIngredient(const Ingredient& ingredient);
    void removeIngredient(const std::string& ingredientName);
    bool containsIngredient(const std::string& ingredientName) const;
    double calculateTotalCalories() const;
    void setSpiciness(int level);
};

#endif //LAB3_MAINCOURSE_H