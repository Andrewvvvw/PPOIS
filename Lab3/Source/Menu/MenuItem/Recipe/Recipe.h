#ifndef LAB3_RECIPE_H
#define LAB3_RECIPE_H

#include <string>
#include <vector>
#include <map>

class Recipe {
private:
    std::string name;
    std::vector<std::string> ingredients;
    std::vector<std::string> steps;
    int preparationTime;
    int difficulty;

public:
    Recipe(const std::string& name, const std::vector<std::string>& ingredients,
           const std::vector<std::string>& steps, int prepTime, int difficulty);

    void addIngredient(const std::string& ingredient);
    void addStep(const std::string& step);
    void setPreparationTime(int newTime);
    bool containsIngredient(const std::string& ingredient) const;
    std::string getFormattedRecipe() const;

    std::string getName() const;
    std::vector<std::string> getIngredients() const;
    std::vector<std::string> getSteps() const;
    int getPreparationTime() const;
    int getDifficulty() const;
};

#endif //LAB3_RECIPE_H
