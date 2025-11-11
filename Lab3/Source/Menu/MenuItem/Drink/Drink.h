#ifndef LAB3_DRINK_H
#define LAB3_DRINK_H

#include "../MenuItem.h"
#include "../Ingredient/Ingredient.h"
#include "../Recipe/Recipe.h"
#include <memory>

class Drink : public MenuItem {
private:
    double volume;
    bool isAlcoholic;
    Ingredient mainIngredient;
    std::shared_ptr<Recipe> recipe;

public:
    Drink(const std::string& name, double price, double volume,
          bool isAlcoholic, const Ingredient& ingredient,
          std::shared_ptr<Recipe> recipe = nullptr);

    void setRecipe(std::shared_ptr<Recipe> newRecipe);
    std::shared_ptr<Recipe> getRecipe() const;
    bool hasRecipe() const;

    double getVolume() const;
    bool getIsAlcoholic() const;
    const Ingredient& getMainIngredient() const;
    void setVolume(double newVolume);
    void setIsAlcoholic(bool alcoholic);
    void changeMainIngredient(const Ingredient& newIngredient);
};

#endif //LAB3_DRINK_H
