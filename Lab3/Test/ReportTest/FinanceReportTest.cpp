#include "UnitTest++.h"
#include "..\..\Source\Report\FinanceReport\FinanceReport.h"

SUITE(FinanceReportTest) {
    TEST(TestConstructor) {
        FinanceReport report("Test User", 1000.0, 500.0);

        CHECK_EQUAL("Financial Report", report.getTitle());
        CHECK_EQUAL("Test User", report.getGeneratedBy());
        CHECK_CLOSE(1000.0, report.getTotalRevenue(), 0.001);
        CHECK_CLOSE(500.0, report.getTotalExpenses(), 0.001);
        CHECK(report.getFinancialNotes().empty());
        CHECK(!report.getIsFinalized());
        CHECK(report.validate());
    }

    TEST(TestDefaultValues) {
        FinanceReport report("Test User");

        CHECK_CLOSE(0.0, report.getTotalRevenue(), 0.001);
        CHECK_CLOSE(0.0, report.getTotalExpenses(), 0.001);
        CHECK(report.getFinancialNotes().empty());
        CHECK(report.validate());
    }

    TEST(TestAddFinancialNote) {
        FinanceReport report("Test User");

        report.addFinancialNote("Initial investment");
        report.addFinancialNote("Q1 Revenue");

        const auto& notes = report.getFinancialNotes();
        CHECK_EQUAL(2, notes.size());
        CHECK_EQUAL("Initial investment", notes[0]);
        CHECK_EQUAL("Q1 Revenue", notes[1]);

        report.addFinancialNote("");
        CHECK_EQUAL(2, notes.size());
    }

    TEST(TestCalculateProfit) {
        {
            FinanceReport report("Test User", 1000.0, 500.0);
            CHECK_CLOSE(500.0, report.calculateProfit(), 0.001);
        }

        {
            FinanceReport report("Test User", 500.0, 1000.0);
            CHECK_CLOSE(-500.0, report.calculateProfit(), 0.001);
        }

        {
            FinanceReport report("Test User", 0.0, 0.0);
            CHECK_CLOSE(0.0, report.calculateProfit(), 0.001);
        }
    }

    TEST(TestAdjustRevenue) {
        FinanceReport report("Test User", 1000.0, 500.0);

        report.adjustRevenue(200.0);
        CHECK_CLOSE(1200.0, report.getTotalRevenue(), 0.001);

        report.adjustRevenue(-100.0);
        CHECK_CLOSE(1100.0, report.getTotalRevenue(), 0.001);

        CHECK_CLOSE(600.0, report.calculateProfit(), 0.001);
    }

    TEST(TestAdjustExpenses) {
        FinanceReport report("Test User", 1000.0, 500.0);

        report.adjustExpenses(100.0);
        CHECK_CLOSE(600.0, report.getTotalExpenses(), 0.001);

        report.adjustExpenses(-50.0);
        CHECK_CLOSE(550.0, report.getTotalExpenses(), 0.001);

        CHECK_CLOSE(450.0, report.calculateProfit(), 0.001);
    }

    TEST(TestGenerate) {
        FinanceReport report("Test User");

        CHECK(!report.getIsFinalized());
        report.generate();
        CHECK(report.getIsFinalized());
    }

    TEST(TestValidate) {
        {
            FinanceReport valid1("Test User", 1000.0, 500.0);
            CHECK(valid1.validate());

            FinanceReport valid2("Test User", 0.0, 0.0);
            CHECK(valid2.validate());
        }

        {
            FinanceReport invalid1("", 1000.0, 500.0);
            CHECK(!invalid1.validate());

            FinanceReport invalid2("Test User", -100.0, 500.0);
            CHECK(!invalid2.validate());

            FinanceReport invalid3("Test User", 1000.0, -500.0);
            CHECK(!invalid3.validate());

            FinanceReport invalid4("", -100.0, -500.0);
            CHECK(!invalid4.validate());
        }
    }

    TEST(TestGetFinancialNotes) {
        FinanceReport report("Test User");

        const auto& notes1 = report.getFinancialNotes();
        CHECK(notes1.empty());

        report.addFinancialNote("Note 1");
        report.addFinancialNote("Note 2");

        const auto& notes2 = report.getFinancialNotes();
        CHECK_EQUAL(2, notes2.size());
        CHECK_EQUAL("Note 1", notes2[0]);
        CHECK_EQUAL("Note 2", notes2[1]);

        const auto& notes3 = report.getFinancialNotes();
        CHECK_EQUAL(2, notes3.size());
    }
}
