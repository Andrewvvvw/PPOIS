#include "FinanceReport.h"

FinanceReport::FinanceReport(const std::string& generatedBy, double revenue, double expenses)
    : Report("Financial Report", generatedBy), totalRevenue(revenue), totalExpenses(expenses) {}

void FinanceReport::addFinancialNote(const std::string& note) {
    if (!note.empty()) {
        financialNotes.push_back(note);
    }
}

double FinanceReport::calculateProfit() const {
    return totalRevenue - totalExpenses;
}

void FinanceReport::adjustRevenue(double amount) {
    totalRevenue += amount;
}

void FinanceReport::adjustExpenses(double amount) {
    totalExpenses += amount;
}

void FinanceReport::generate() {
    isFinalized = true;
}

bool FinanceReport::validate() const {
    return Report::validate() && totalRevenue >= 0 && totalExpenses >= 0;
}

double FinanceReport::getTotalRevenue() const {
    return totalRevenue;
}

double FinanceReport::getTotalExpenses() const {
    return totalExpenses;
}

const std::vector<std::string>& FinanceReport::getFinancialNotes() const {
    return financialNotes;
}