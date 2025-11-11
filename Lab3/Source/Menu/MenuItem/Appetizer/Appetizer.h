#ifndef LAB3_APPETIZER_H
#define LAB3_APPETIZER_H

#include "../MenuItem.h"
#include "../Recipe/Recipe.h"
#include <memory>

class Appetizer : public MenuItem {
private:
    int spiceLevel;
    bool isVegetarian;
    int calories;
    std::shared_ptr <Recipe> recipe;

public:
    Appetizer(const std::string& name, double price, bool isAvailable,
             int spiceLevel, bool isVegetarian, int calories,
             std::shared_ptr<Recipe> recipe = nullptr);

    void setRecipe(std::shared_ptr<Recipe> newRecipe);
    std::shared_ptr<Recipe> getRecipe() const;
    bool hasRecipe() const;

    void increaseSpiceLevel();
    bool isHighCalorie(int threshold) const;

    int getSpiceLevel() const;
    bool getIsVegetarian() const;
    int getCalories() const;

    void setSpiceLevel(int level);
    void setIsVegetarian(bool vegetarian);
    void setCalories(int cal);
};

#endif //LAB3_APPETIZER_H