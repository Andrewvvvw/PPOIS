#ifndef LAB3_CHEF_H
#define LAB3_CHEF_H

#include "../Employee.h"
#include "../../Menu/MenuItem/MenuItem.h"
#include <vector>
#include <string>
#include <memory>

class Chef : public Employee {
private:
    std::vector <std::string> specialties;
    int maxDishesPerHour;
    bool hasKnifeSet;
    int yearsOfCulinaryExperience;

public:
    Chef(const std::string& name, double hourlyRate, int yearsOfExperience);

    std::unique_ptr <MenuItem> prepareDish(const std::string& dishName, double price, bool isAvailable = true);
    void addSpecialty(const std::string& dishName);
    bool canPrepare(const std::string& dishName) const;
    void upgradeKnifeSet();

    std::string getRole() const override;
};

#endif //LAB3_CHEF_H