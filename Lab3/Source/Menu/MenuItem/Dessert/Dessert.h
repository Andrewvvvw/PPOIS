#ifndef LAB3_DESSERT_H
#define LAB3_DESSERT_H

#include <string>
#include "../MenuItem.h"
#include "../Recipe/Recipe.h"
#include <vector>
#include <memory>

class Dessert : public MenuItem {
private:
    bool isGlutenFree;
    bool isVegan;
    int calories;
    std::string mainIngredient;
    float sweetnessLevel;
    std::shared_ptr<Recipe> recipe;

public:
    Dessert(const std::string& name, double price, bool isGlutenFree,
            bool isVegan, int calories, const std::string& mainIngredient,
            float sweetnessLevel, bool isAvailable = true,
            std::shared_ptr<Recipe> recipe = nullptr);

    void setRecipe(std::shared_ptr<Recipe> newRecipe);
    std::shared_ptr<Recipe> getRecipe() const;
    bool hasRecipe() const;

    bool getIsGlutenFree() const;
    bool getIsVegan() const;
    int getCalories() const;
    std::string getMainIngredient() const;
    float getSweetnessLevel() const;

    void setSweetnessLevel(float level);
    void reduceCalories(int amount);
    bool isHealthyOption() const;
    void makeGlutenFree();
    std::vector<std::string> getDietaryInfo() const;
};

#endif //LAB3_DESSERT_H
