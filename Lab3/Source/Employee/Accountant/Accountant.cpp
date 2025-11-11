#include "Accountant.h"
#include <sstream>
#include <iomanip>

Accountant::Accountant(const std::string& name, double hourlyRate, int yearsOfExperience)
    : Employee(name, "Accountant", hourlyRate),
      totalBudget(0.0),
      hasCertification(false),
      yearsAsAccountant(yearsOfExperience) {}

void Accountant::trackExpense(double amount, const std::string& description) {
    if (amount > 0) {
        totalBudget -= amount;
        financialRecords.push_back("Expense: " + description + ": -$" + std::to_string(amount));
    }
}

double Accountant::calculateTaxes(double revenue) const {
    return revenue * 0.15;
}

void Accountant::updateBudget(double amount) {
    if (amount > 0) {
        totalBudget += amount;
        financialRecords.push_back("Budget updated: +$" + std::to_string(amount));
    }
}

void Accountant::renewCertification() {
    hasCertification = true;
}

std::string Accountant::generateFinancialSummary() const {
    std::ostringstream ss;
    ss << "Financial Summary - " << getName() << "\n";
    ss << "Current Budget: $" << std::fixed << std::setprecision(2) << totalBudget << "\n";
    ss << "Certified: " << (hasCertification ? "Yes" : "No") << "\n";
    ss << "Years of Experience: " << yearsAsAccountant << "\n";
    return ss.str();
}

std::string Accountant::getRole() const {
    return "Accountant";
}
