#include "Bartender.h"
#include <memory>

Bartender::Bartender(const std::string& name, double hourlyRate, int yearsOfExperience)
    : Employee(name, "Bartender", hourlyRate),
      maxDrinksPerHour(20),
      isCertified(yearsOfExperience >= 1),
      tipAmount(0.0) {}

std::unique_ptr<Drink> Bartender::prepareDrink(const std::string& drinkName, double volume, bool isAlcoholic) {
    if (!canPrepare(drinkName) || volume <= 0) {
        return nullptr;
    }

    Ingredient baseIngredient("Water", 1.0, "liter", 0, 0.5);
    if (isAlcoholic) {
        baseIngredient = Ingredient("Vodka", 0.5, "liter", 1200, 15.0);
    }

    return std::make_unique<Drink>(drinkName, 5.0, volume, isAlcoholic, baseIngredient);
}

void Bartender::addCocktailToRepertoire(const std::string& cocktailName) {
    if (std::find(knownCocktails.begin(), knownCocktails.end(), cocktailName) == knownCocktails.end()) {
        knownCocktails.push_back(cocktailName);
    }
}

bool Bartender::canPrepare(const std::string& drinkName) const {
    return std::find(knownCocktails.begin(), knownCocktails.end(), drinkName) != knownCocktails.end();
}

void Bartender::receiveTip(double amount) {
    if (amount > 0) {
        tipAmount += amount;
    }
}

std::string Bartender::getRole() const {
    return "Bartender";
}
