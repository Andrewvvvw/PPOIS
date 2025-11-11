#include "Cleaner.h"

Cleaner::Cleaner(const std::string& name, double hourlyRate, int yearsOfExperience)
        : Employee(name, "Cleaner", hourlyRate),
          cleaningSpeed(1 + (yearsOfExperience / 2)),
          hasCleaningSupplies(true),
          yearsOfExperience(yearsOfExperience) {}

void Cleaner::cleanArea(const std::string& area) {
    if (!isAreaInCharge(area) || !hasCleaningSupplies) {
        return;
    }
}

void Cleaner::addCleaningArea(const std::string& area) {
    if (!isAreaInCharge(area)) {
        cleaningAreas.push_back(area);
    }
}

bool Cleaner::isAreaInCharge(const std::string& area) const {
    return std::find(cleaningAreas.begin(), cleaningAreas.end(), area) != cleaningAreas.end();
}

void Cleaner::restockSupplies() {
    hasCleaningSupplies = true;
}

std::string Cleaner::getRole() const {
    return "Cleaner";
}