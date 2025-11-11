#include "Chef.h"
#include <memory>

Chef::Chef(const std::string& name, double hourlyRate, int yearsOfExperience)
        : Employee(name, "Chef", hourlyRate),
          maxDishesPerHour(10),
          hasKnifeSet(yearsOfExperience >= 2),
          yearsOfCulinaryExperience(yearsOfExperience) {}

std::unique_ptr <MenuItem> Chef::prepareDish(const std::string& dishName, double price, bool isAvailable) {
    if (!canPrepare(dishName)) {
        return nullptr;
    }
    return std::make_unique<MenuItem>(dishName, price, isAvailable);
}

void Chef::addSpecialty(const std::string& dishName) {
    if (std::find(specialties.begin(), specialties.end(), dishName) == specialties.end()) {
        specialties.push_back(dishName);
    }
}

bool Chef::canPrepare(const std::string& dishName) const {
    return std::find(specialties.begin(), specialties.end(), dishName) != specialties.end();
}

void Chef::upgradeKnifeSet() {
    hasKnifeSet = true;
    maxDishesPerHour += 2;
}

std::string Chef::getRole() const {
    return "Chef";
}