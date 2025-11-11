#include "Manager.h"

Manager::Manager(const std::string& name, const std::string& position, double hourlyRate,
                 const std::string& dept, int accessLvl)
    : Employee(name, position, hourlyRate), department(dept), accessLevel(accessLvl > 0 ? accessLvl : 1),
      teamSize(0), bonus(0.0), isCertified(false) {}

std::string Manager::getDepartment() const {
    return department;
}

int Manager::getTeamSize() const {
    return teamSize;
}

double Manager::getBonus() const {
    return bonus;
}

int Manager::getAccessLevel() const {
    return accessLevel;
}

bool Manager::getIsCertified() const {
    return isCertified;
}

void Manager::setDepartment(const std::string& dept) {
    department = dept;
}

void Manager::setTeamSize(int size) {
    teamSize = size >= 0 ? size : 0;
}

void Manager::setBonus(double amount) {
    bonus = amount >= 0 ? amount : 0;
}

void Manager::setAccessLevel(int level) {
    accessLevel = level > 0 ? level : 1;
}

void Manager::setIsCertified(bool certified) {
    isCertified = certified;
}

std::string Manager::getRole() const {
    return "Manager";
}

void Manager::assignTask(const std::string& task, const std::string& employeeName) {
    if (!task.empty() && !employeeName.empty()) {
    }
}

bool Manager::approveExpense(double amount) {
    return amount >= 0 && amount <= 1000.0 * accessLevel;
}

double Manager::evaluateTeam() const {
    return teamSize > 0 ? 100.0 * (1.0 - 1.0 / (teamSize + 1)) : 0.0;
}

bool Manager::getBonusEligibility() const {
    return isCertified && teamSize >= 3 && accessLevel >= 2;
}
