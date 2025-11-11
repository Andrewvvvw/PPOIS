#ifndef LAB3_FINANCE_REPORT_H
#define LAB3_FINANCE_REPORT_H

#include "../Report.h"
#include <vector>

class FinanceReport : public Report {
private:
    double totalRevenue;
    double totalExpenses;
    std::vector<std::string> financialNotes;
    std::string currency;

public:
    FinanceReport(const std::string& generatedBy, double revenue = 0.0, double expenses = 0.0);

    void addFinancialNote(const std::string& note);
    double calculateProfit() const;
    void adjustRevenue(double amount);
    void adjustExpenses(double amount);

    void generate() override;
    bool validate() const override;

    double getTotalRevenue() const;
    double getTotalExpenses() const;
    const std::vector<std::string>& getFinancialNotes() const;
};

#endif //LAB3_FINANCE_REPORT_H