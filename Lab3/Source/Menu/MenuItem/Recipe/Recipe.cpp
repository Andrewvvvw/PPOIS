#include "Recipe.h"
#include <algorithm>
#include <sstream>

Recipe::Recipe(const std::string& name, const std::vector<std::string>& ingredients,
               const std::vector<std::string>& steps, int prepTime, int difficulty)
    : name(name), ingredients(ingredients), steps(steps),
      preparationTime(prepTime > 0 ? prepTime : 0),
      difficulty(difficulty >= 1 && difficulty <= 5 ? difficulty : 3) {}

void Recipe::addIngredient(const std::string& ingredient) {
    if (!ingredient.empty()) {
        ingredients.push_back(ingredient);
    }
}

void Recipe::addStep(const std::string& step) {
    if (!step.empty()) {
        steps.push_back(step);
    }
}

void Recipe::setPreparationTime(int newTime) {
    if (newTime > 0) {
        preparationTime = newTime;
    }
}

bool Recipe::containsIngredient(const std::string& ingredient) const {
    return std::find(ingredients.begin(), ingredients.end(), ingredient) != ingredients.end();
}

std::string Recipe::getFormattedRecipe() const {
    std::ostringstream oss;
    oss << "Recipe: " << name << "\n\n";

    oss << "Ingredients (" << ingredients.size() << "):\n";
    for (const auto& ing : ingredients) {
        oss << "- " << ing << "\n";
    }

    oss << "\nSteps (" << steps.size() << "):\n";
    for (size_t i = 0; i < steps.size(); ++i) {
        oss << i + 1 << ". " << steps[i] << "\n";
    }

    oss << "\nPreparation time: " << preparationTime << " minutes\n";
    oss << "Difficulty: " << difficulty << "/5";

    return oss.str();
}

std::string Recipe::getName() const {
    return name;
}

std::vector<std::string> Recipe::getIngredients() const {
    return ingredients;
}

std::vector<std::string> Recipe::getSteps() const {
    return steps;
}

int Recipe::getPreparationTime() const {
    return preparationTime;
}

int Recipe::getDifficulty() const {
    return difficulty;
}
