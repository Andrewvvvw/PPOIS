#include "UnitTest++.h"
#include "Source/Employee/Accountant/Accountant.h"
#include <sstream>

SUITE(AccountantTest) {
    TEST(ConstructorAndGetters) {
        Accountant accountant("John Doe", 25.0, 5);
        accountant.setYearsOfExperience(5);

        CHECK_EQUAL("John Doe", accountant.getName());
        CHECK_EQUAL(25.0, accountant.getHourlyRate());
        CHECK_EQUAL(5, accountant.getYearsOfExperience());
        CHECK_EQUAL("Accountant", accountant.getRole());
    }

    TEST(TrackExpense) {
        Accountant accountant("Jane Smith", 30.0, 3);
        accountant.setYearsOfExperience(3);

        accountant.trackExpense(100.0, "Office supplies");
        accountant.trackExpense(250.0, "Software license");

        std::string summary = accountant.generateFinancialSummary();
        CHECK(summary.find("Office supplies") == std::string::npos);
        CHECK(summary.find("Software license") == std::string::npos);
    }

    TEST(CalculateTaxes) {
        Accountant accountant("Alice Brown", 35.0, 7);
        accountant.setYearsOfExperience(7);

        double taxes1 = accountant.calculateTaxes(1000.0);
        double taxes2 = accountant.calculateTaxes(5000.0);

        CHECK_EQUAL(150.0, taxes1);
        CHECK_EQUAL(750.0, taxes2);
    }

    TEST(UpdateBudget) {
        Accountant accountant("Bob Wilson", 40.0, 2);
        accountant.setYearsOfExperience(2);

        accountant.updateBudget(10000.0);
        std::string summary1 = accountant.generateFinancialSummary();
        CHECK(summary1.find("10000.00") != std::string::npos);

        accountant.updateBudget(-2500.0);

        accountant.updateBudget(5000.0);
        std::string summary2 = accountant.generateFinancialSummary();
        CHECK(summary2.find("15000.00") != std::string::npos);
    }

    TEST(RenewCertification) {
        Accountant accountant("Charlie Davis", 28.0, 1);
        accountant.setYearsOfExperience(1);
        std::string summary1 = accountant.generateFinancialSummary();
        CHECK(summary1.find("No") != std::string::npos);

        accountant.renewCertification();
        std::string summary2 = accountant.generateFinancialSummary();
        CHECK(summary2.find("Yes") != std::string::npos);
    }

    TEST(FinancialSummary) {
        Accountant accountant("Eve Johnson", 32.0, 4);
        accountant.setYearsOfExperience(4);

        std::string summary = accountant.generateFinancialSummary();
        CHECK(summary.find("Eve Johnson") != std::string::npos);

        accountant.trackExpense(150.0, "Office chair");
        std::string updatedSummary = accountant.generateFinancialSummary();
        CHECK(updatedSummary.find("-150.00") != std::string::npos);
    }

    TEST(EdgeCases) {
        Accountant zeroRate("Zero Rate", 0.0, 0);
        zeroRate.setYearsOfExperience(0);
        CHECK_EQUAL(0.0, zeroRate.getHourlyRate());

        Accountant negativeExp("Negative Exp", 20.0, -1);
        negativeExp.setYearsOfExperience(-1);
        CHECK_EQUAL(0, negativeExp.getYearsOfExperience());

        Accountant emptyName("", 10.0, 2);
        emptyName.setYearsOfExperience(2);
        CHECK(emptyName.getName().empty());
    }
}
