#include "UnitTest++.h"
#include "..\..\Source\Report\InventoryReport\InventoryReport.h"

SUITE(InventoryReportTest) {
    TEST(TestConstructor) {
        InventoryReport report("Test User");

        CHECK_EQUAL("Inventory Report", report.getTitle());
        CHECK_EQUAL("Test User", report.getGeneratedBy());
        CHECK_EQUAL(0, report.getTotalItems());
        CHECK_CLOSE(0.0, report.getTotalValue(), 0.001);
        CHECK(report.getItemQuantities().empty());
        CHECK(!report.getIsFinalized());
        CHECK(report.validate());
    }

    TEST(TestUpdateItemQuantity) {
        InventoryReport report("Test User");

        report.updateItemQuantity(1, 10);
        CHECK_EQUAL(10, report.getTotalItems());

        report.updateItemQuantity(1, 15);
        CHECK_EQUAL(15, report.getTotalItems());

        report.updateItemQuantity(2, 5);
        CHECK_EQUAL(20, report.getTotalItems());

        report.updateItemQuantity(0, 10);
        report.updateItemQuantity(3, -5);
        CHECK_EQUAL(20, report.getTotalItems());

        const auto& quantities = report.getItemQuantities();
        CHECK_EQUAL(2, quantities.size());
        CHECK_EQUAL(15, quantities.at(1));
        CHECK_EQUAL(5, quantities.at(2));
    }

    TEST(TestMarkLowStock) {
        InventoryReport report("Test User");

        report.markLowStock(1, true);
        report.markLowStock(2, true);
        report.markLowStock(1, false);
        report.markLowStock(0, true);
    }

    TEST(TestCalculateTotalValue) {
        InventoryReport report("Test User");

        report.calculateTotalValue(1000.50);
        CHECK_CLOSE(1000.50, report.getTotalValue(), 0.001);

        report.calculateTotalValue(-500.0);
        CHECK_CLOSE(1000.50, report.getTotalValue(), 0.001);

        report.calculateTotalValue(0.0);
        CHECK_CLOSE(0.0, report.getTotalValue(), 0.001);
    }

    TEST(TestGenerate) {
        InventoryReport report("Test User");

        CHECK(!report.getIsFinalized());
        report.generate();
        CHECK(report.getIsFinalized());
    }

    TEST(TestValidate) {
        {
            InventoryReport valid("Test User");
            valid.updateItemQuantity(1, 10);
            valid.calculateTotalValue(100.0);
            CHECK(valid.validate());
        }

        {
            InventoryReport invalid1("");
            CHECK(!invalid1.validate());
        }

        {
            InventoryReport invalid2("Test User");
            invalid2.updateItemQuantity(1, -1);
            CHECK(invalid2.validate());
        }

        {
            InventoryReport invalid3("Test User");
            invalid3.calculateTotalValue(-100.0);
            CHECK(invalid3.validate());
        }
    }

    TEST(TestGetItemQuantities) {
        InventoryReport report("Test User");

        const auto& quantities1 = report.getItemQuantities();
        CHECK(quantities1.empty());

        report.updateItemQuantity(1, 10);
        report.updateItemQuantity(2, 20);

        const auto& quantities2 = report.getItemQuantities();
        CHECK_EQUAL(2, quantities2.size());
        CHECK_EQUAL(10, quantities2.at(1));
        CHECK_EQUAL(20, quantities2.at(2));

        const auto& quantities3 = report.getItemQuantities();
        CHECK_EQUAL(2, quantities3.size());
    }
}
