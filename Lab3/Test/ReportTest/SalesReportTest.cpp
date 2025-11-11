#include "UnitTest++.h"
#include "..\..\Source\Report\SalesReport\SalesReport.h"
#include <ctime>

SUITE(SalesReportTest) {
    TEST(TestConstructor) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);
        CHECK_EQUAL("Sales Report", report.getTitle());
        CHECK_EQUAL("Test User", report.getGeneratedBy());
        CHECK_CLOSE(0.0, report.getTotalSales(), 0.001);
        CHECK_EQUAL(0, report.getItemsSold());
        CHECK(report.getDailySales().empty());
        CHECK(!report.getIsFinalized());
        CHECK(report.validate());
    }

    TEST(TestAddSale) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);

        report.addSale(1, 100.0);
        CHECK_CLOSE(100.0, report.getTotalSales(), 0.001);

        report.addSale(1, 50.0);
        CHECK_CLOSE(150.0, report.getTotalSales(), 0.001);

        report.addSale(2, 75.0);
        CHECK_CLOSE(225.0, report.getTotalSales(), 0.001);

        report.addSale(0, 10.0);
        report.addSale(3, -5.0);
        report.addSale(-1, 10.0);
        CHECK_CLOSE(225.0, report.getTotalSales(), 0.001);

        const auto& sales = report.getDailySales();
        CHECK_EQUAL(2, sales.size());
        CHECK_CLOSE(150.0, sales.at(1), 0.001);
        CHECK_CLOSE(75.0, sales.at(2), 0.001);
    }

    TEST(TestSetTotalSales) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);

        report.setTotalSales(1000.50);
        CHECK_CLOSE(1000.50, report.getTotalSales(), 0.001);

        report.setTotalSales(-500.0);
        CHECK_CLOSE(1000.50, report.getTotalSales(), 0.001);

        report.setTotalSales(0.0);
        CHECK_CLOSE(0.0, report.getTotalSales(), 0.001);
    }

    TEST(TestIncrementItemsSold) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);

        report.incrementItemsSold(5);
        CHECK_EQUAL(5, report.getItemsSold());

        report.incrementItemsSold(3);
        CHECK_EQUAL(8, report.getItemsSold());

        report.incrementItemsSold(-2);
        report.incrementItemsSold(0);
        CHECK_EQUAL(8, report.getItemsSold());
    }

    TEST(TestGenerate) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);

        CHECK(!report.getIsFinalized());
        report.generate();
        CHECK(report.getIsFinalized());
    }

    TEST(TestValidate) {
        time_t now = time(nullptr);

        {
            SalesReport valid("Test User", now - 86400, now);
            valid.addSale(1, 100.0);
            valid.incrementItemsSold(5);
            CHECK(valid.validate());
        }

        {
            SalesReport invalid1("", now - 86400, now);
            CHECK(!invalid1.validate());
        }

        {
            SalesReport invalid2("Test User", now, now - 86400);
            CHECK(!invalid2.validate());
        }

        {
            SalesReport valid2("Test User", now, now);
            CHECK(valid2.validate());
        }
    }

    TEST(TestGetDailySales) {
        time_t now = time(nullptr);
        SalesReport report("Test User", now - 86400, now);

        const auto& sales1 = report.getDailySales();
        CHECK(sales1.empty());

        report.addSale(1, 100.0);
        report.addSale(2, 200.0);

        const auto& sales2 = report.getDailySales();
        CHECK_EQUAL(2, sales2.size());
        CHECK_CLOSE(100.0, sales2.at(1), 0.001);
        CHECK_CLOSE(200.0, sales2.at(2), 0.001);

        const auto& sales3 = report.getDailySales();
        CHECK_EQUAL(2, sales3.size());
    }
}
