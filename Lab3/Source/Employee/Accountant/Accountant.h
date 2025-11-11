#ifndef LAB3_ACCOUNTANT_H
#define LAB3_ACCOUNTANT_H

#include "../Employee.h"

class Accountant : public Employee {
private:
    double totalBudget;
    std::vector<std::string> financialRecords;
    bool hasCertification;
    int yearsAsAccountant;

public:
    Accountant(const std::string& name, double hourlyRate, int yearsOfExperience);

    void trackExpense(double amount, const std::string& description);
    double calculateTaxes(double revenue) const;
    void updateBudget(double amount);
    void renewCertification();
    std::string generateFinancialSummary() const;

    std::string getRole() const override;
};

#endif //LAB3_ACCOUNTANT_H