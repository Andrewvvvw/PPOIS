#include "UnitTest++.h"
#include "../../Source/InventoryAndSupply/Inventory/StockItem/StockItem.h"
#include "../../Source/Exceptions/Exceptions.h"

TEST(StockItem_Constructor) {
    StockItem item("Test Item", "Test Category", 10.5, "pcs", 5.0);

    CHECK_EQUAL("Test Item", item.getName());
    CHECK_EQUAL("Test Category", item.getCategory());
    CHECK_EQUAL(10.5, item.getQuantity());
    CHECK_EQUAL("pcs", item.getUnit());
    CHECK_EQUAL(5.0, item.getMinStockLevel());

    CHECK_THROW(StockItem("Invalid", "Test", -1, "pcs", 5), ExceptionNegativeQuantity);
    CHECK_THROW(StockItem("Invalid", "Test", 10, "pcs", -5), ExceptionNegativeStockMinimum);
}

TEST(StockItem_SettersAndGetters) {
    StockItem item("Test Item", "Test Category", 10, "pcs", 5);

    item.addQuantity(15);
            CHECK_EQUAL(25, item.getQuantity());

    item.setCategory("New Category");
            CHECK_EQUAL("New Category", item.getCategory());

            CHECK_EQUAL("Test Item", item.getName());
            CHECK_EQUAL("pcs", item.getUnit());
            CHECK_EQUAL(5, item.getMinStockLevel());
}

TEST(StockItem_NeedsRestocking) {
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);
    CHECK(!item1.needsRestocking());

    StockItem item2("Item 2", "Category 2", 5, "pcs", 5);
    CHECK(item2.needsRestocking());

    StockItem item3("Item 3", "Category 3", 4, "pcs", 5);
    CHECK(item3.needsRestocking());

    StockItem item4("Item 4", "Category 4", 0, "pcs", 5);
    CHECK(item4.needsRestocking());
}

TEST(StockItem_CalculateDaysLeft) {
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);

    CHECK_EQUAL(5, item1.calculateDaysLeft(2));
    CHECK_EQUAL(10, item1.calculateDaysLeft(1));
    CHECK_EQUAL(0, item1.calculateDaysLeft(0));
    CHECK_EQUAL(0, item1.calculateDaysLeft(-5));

    StockItem item2("Item 2", "Category 2", 0, "pcs", 5);
    CHECK_EQUAL(0, item2.calculateDaysLeft(5));
}

TEST(StockItem_UpdateMinStockLevel) {
    StockItem item("Test Item", "Test Category", 10, "pcs", 5);

    item.updateMinStockLevel(8);
    CHECK_EQUAL(8, item.getMinStockLevel());

    item.updateMinStockLevel(0);
    CHECK_EQUAL(0, item.getMinStockLevel());

    item.updateMinStockLevel(-5);
    CHECK_EQUAL(0, item.getMinStockLevel());
}

TEST(StockItem_EdgeCases) {
    StockItem item("Test", "Test", 0, "pcs", 1);
            CHECK(item.needsRestocking());
            CHECK_EQUAL(0, item.calculateDaysLeft(0));

    item.addQuantity(-5);
            CHECK_EQUAL(0, item.getQuantity());

    item.updateMinStockLevel(10);
            CHECK(item.needsRestocking());
}
