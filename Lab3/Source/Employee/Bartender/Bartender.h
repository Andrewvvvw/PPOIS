#ifndef LAB3_BARTENDER_H
#define LAB3_BARTENDER_H

#include "../Employee.h"
#include "../../Menu/MenuItem/Drink/Drink.h"
#include <vector>
#include <string>

class Bartender : public Employee {
private:
    std::vector <std::string> knownCocktails;
    int maxDrinksPerHour;
    bool isCertified;
    double tipAmount;

public:
    Bartender(const std::string& name, double hourlyRate, int yearsOfExperience);

    std::unique_ptr<Drink> prepareDrink(const std::string& drinkName, double volume, bool isAlcoholic);
    void addCocktailToRepertoire(const std::string& cocktailName);
    bool canPrepare(const std::string& drinkName) const;
    void receiveTip(double amount);

    std::string getRole() const override;
};

#endif //LAB3_BARTENDER_H
