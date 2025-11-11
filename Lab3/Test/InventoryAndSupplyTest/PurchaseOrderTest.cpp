#include "UnitTest++.h"
#include "../../Source/InventoryAndSupply/PurchaseOrder/PurchaseOrder.h"
#include "../../Source/InventoryAndSupply/Inventory/StockItem/StockItem.h"
#include "../../Source/Exceptions/Exceptions.h"

TEST(PurchaseOrder_Constructor) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");

    CHECK_EQUAL("ORD123", order.getOrderId());
    CHECK_EQUAL("SUP456", order.getSupplierId());
    CHECK_EQUAL("2023-11-10", order.getOrderDate());
    CHECK_EQUAL("Pending", order.getStatus());
    CHECK(order.getItems().empty());
}

TEST(PurchaseOrder_AddRemoveItems) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5.0);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10.0);

    order.addItem(item1);
    CHECK_EQUAL(1, order.getItems().size());

    order.addItem(item2);
    CHECK_EQUAL(2, order.getItems().size());

    bool removed = order.removeItem("Item 1");
    CHECK(removed);
    CHECK_EQUAL(1, order.getItems().size());

    removed = order.removeItem("Non-existent Item");
    CHECK(!removed);
    CHECK_EQUAL(1, order.getItems().size());
}

TEST(PurchaseOrder_UpdateStatus) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");

    CHECK_EQUAL("Pending", order.getStatus());

    order.updateStatus("Shipped");
    CHECK_EQUAL("Shipped", order.getStatus());

    order.updateStatus("Delivered");
    CHECK_EQUAL("Delivered", order.getStatus());
}

TEST(PurchaseOrder_CalculateTotalCost) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");

    CHECK_THROW(order.calculateTotalCost(), ExceptionEmptyOrder);

    StockItem item1("Item 1", "Category 1", 10, "pcs", 5.0);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10.0);

    order.addItem(item1);
    order.addItem(item2);

    CHECK_EQUAL(250.0, order.calculateTotalCost());
}

TEST(PurchaseOrder_ContainsItem) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5.0);

    CHECK(!order.containsItem("Item 1"));

    order.addItem(item1);
    CHECK(order.containsItem("Item 1"));
    CHECK(!order.containsItem("Non-existent Item"));
}

TEST(PurchaseOrder_Getters) {
    PurchaseOrder order("ORD123", "SUP456", "2023-11-10");

    CHECK_EQUAL("ORD123", order.getOrderId());
    CHECK_EQUAL("SUP456", order.getSupplierId());
    CHECK_EQUAL("2023-11-10", order.getOrderDate());
    CHECK_EQUAL("Pending", order.getStatus());

    CHECK(order.getItems().empty());

    StockItem item1("Item 1", "Category 1", 10, "pcs", 5.0);
    order.addItem(item1);

    const auto& items = order.getItems();
    CHECK_EQUAL(1, items.size());
    if (!items.empty()) {
        CHECK_EQUAL("Item 1", items[0].getName());
    }
}
