#include "Employee.h"

Employee::Employee(const std::string& name, const std::string& position, double hourlyRate)
        : name(name), position(position), hourlyRate(hourlyRate > 0 ? hourlyRate : 0),
          yearsOfExperience(0), isActive(true) {}

void Employee::addExperience(int years) {
    if (years > 0) {
        yearsOfExperience += years;
    }
}

std::string Employee::getName() const {
    return name;
}

double Employee::getHourlyRate() const {
    return hourlyRate;
}

int Employee::getYearsOfExperience() const {
    return yearsOfExperience;
}

bool Employee::getIsActive() const {
    return isActive;
}

void Employee::setName(const std::string& name) {
    this->name = name;
}

void Employee::setHourlyRate(double rate) {
    hourlyRate = rate > 0 ? rate : 0;
}

void Employee::setYearsOfExperience(int years) {
    yearsOfExperience = years >= 0 ? years : 0;
}

void Employee::setIsActive(bool active) {
    isActive = active;
}
