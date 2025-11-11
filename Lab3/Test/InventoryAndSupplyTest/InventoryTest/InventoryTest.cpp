#include "UnitTest++.h"
#include "../../Source/InventoryAndSupply/Inventory/Inventory.h"
#include "../../Source/InventoryAndSupply/Inventory/StockItem/StockItem.h"
#include "../../Source/Exceptions/Exceptions.h"

TEST(Inventory_Constructor) {
    Inventory inventory("Warehouse A", 100, "John Doe");

    CHECK_EQUAL("Warehouse A", inventory.getLocation());
    CHECK_EQUAL(100, inventory.getMaxCapacity());
    CHECK_EQUAL("John Doe", inventory.getManager());
    CHECK_EQUAL(0, inventory.getItemCount());

    CHECK_THROW(Inventory("Warehouse B", -10, "Jane Smith"), ExceptionNegativeCapacity);
}

TEST(Inventory_AddItem) {
    Inventory inventory("Warehouse A", 2, "John Doe");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10);

    CHECK_EQUAL(0, inventory.getItemCount());

    inventory.addItem(item1);
    CHECK_EQUAL(1, inventory.getItemCount());

    inventory.addItem(item2);
    CHECK_EQUAL(2, inventory.getItemCount());

    StockItem item3("Item 3", "Category 3", 30, "l", 15);
    inventory.addItem(item3);
    CHECK_EQUAL(2, inventory.getItemCount());
}

TEST(Inventory_RemoveItem) {
    Inventory inventory("Warehouse A", 10, "John Doe");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10);

    inventory.addItem(item1);
    inventory.addItem(item2);

    CHECK_EQUAL(2, inventory.getItemCount());

    bool removed = inventory.removeItem("Item 1");
    CHECK(removed);
    CHECK_EQUAL(1, inventory.getItemCount());

    removed = inventory.removeItem("Nonexistent Item");
    CHECK(!removed);
    CHECK_EQUAL(1, inventory.getItemCount());
}

TEST(Inventory_FindItem) {
    Inventory inventory("Warehouse A", 10, "John Doe");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10);

    inventory.addItem(item1);
    inventory.addItem(item2);

    StockItem* foundItem = inventory.findItem("Item 1");
    CHECK(foundItem != nullptr);
    CHECK_EQUAL("Item 1", foundItem->getName());

    foundItem = inventory.findItem("Nonexistent Item");
    CHECK(foundItem == nullptr);
}

TEST(Inventory_GetLowStockItems) {
    Inventory inventory("Warehouse A", 10, "John Doe");
    StockItem item1("Item 1", "Category 1", 4, "pcs", 5);
    StockItem item2("Item 2", "Category 2", 20, "kg", 10);
    StockItem item3("Item 3", "Category 1", 3, "l", 5);

    inventory.addItem(item1);
    inventory.addItem(item2);
    inventory.addItem(item3);

    std::vector<StockItem> lowStock = inventory.getLowStockItems();
    CHECK_EQUAL(2, lowStock.size());

    bool hasItem1 = false;
    bool hasItem3 = false;

    for (const auto& item : lowStock) {
        if (item.getName() == "Item 1") hasItem1 = true;
        if (item.getName() == "Item 3") hasItem3 = true;
    }

    CHECK(hasItem1);
    CHECK(hasItem3);
}

TEST(Inventory_UpdateStockLevel) {
    Inventory inventory("Warehouse A", 10, "John Doe");
    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);

    inventory.addItem(item1);

    inventory.updateStockLevel("Item 1", 15);
    StockItem* foundItem = inventory.findItem("Item 1");
            CHECK_EQUAL(25, foundItem->getQuantity());

    inventory.updateStockLevel("Nonexistent Item", 20);
            CHECK_EQUAL(1, inventory.getItemCount());
}

TEST(Inventory_Getters) {
    Inventory inventory("Warehouse A", 50, "John Doe");

            CHECK_EQUAL("Warehouse A", inventory.getLocation());
            CHECK_EQUAL(50, inventory.getMaxCapacity());
            CHECK_EQUAL("John Doe", inventory.getManager());

    std::string lastUpdated = inventory.getLastUpdated();
            CHECK(!lastUpdated.empty());

            CHECK_EQUAL(0, inventory.getItemCount());

    StockItem item1("Item 1", "Category 1", 10, "pcs", 5);
    inventory.addItem(item1);
            CHECK_EQUAL(1, inventory.getItemCount());
}