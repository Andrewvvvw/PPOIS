#include "UnitTest++.h"
#include "../../Source/InventoryAndSupply/Supplier/Supplier.h"
#include "../../Source/Exceptions/Exceptions.h"

TEST(Supplier_Constructor) {
    Supplier supplier("SUP123", "Test Supplier", "John Doe", "+1234567890");

    CHECK_EQUAL("SUP123", supplier.getSupplierId());
    CHECK_EQUAL("Test Supplier", supplier.getName());
    CHECK_EQUAL("John Doe", supplier.getContactPerson());
    CHECK_EQUAL("+1234567890", supplier.getPhoneNumber());
    CHECK(supplier.getSuppliedItems().empty());

    CHECK_THROW(Supplier("SUP123", "", "John Doe", "+1234567890"), ExceptionEmptyName);
    CHECK_THROW(Supplier("SUP123", "Test Supplier", "John Doe", ""), ExceptionEmptyPhoneNumber);
}

TEST(Supplier_AddRemoveItems) {
    Supplier supplier("SUP123", "Test Supplier", "John Doe", "+1234567890");

    supplier.addSuppliedItem("Item 1");
    CHECK_EQUAL(1, supplier.getSuppliedItems().size());

    supplier.addSuppliedItem("Item 1");
    CHECK_EQUAL(1, supplier.getSuppliedItems().size());

    supplier.addSuppliedItem("Item 2");
    CHECK_EQUAL(2, supplier.getSuppliedItems().size());

    bool removed = supplier.removeSuppliedItem("Item 1");
    CHECK(removed);
    CHECK_EQUAL(1, supplier.getSuppliedItems().size());

    removed = supplier.removeSuppliedItem("Non-existent Item");
    CHECK(!removed);
    CHECK_EQUAL(1, supplier.getSuppliedItems().size());
}

TEST(Supplier_UpdateContactInfo) {
    Supplier supplier("SUP123", "Test Supplier", "John Doe", "+1234567890");

    supplier.updateContactInfo("Jane Smith", "+0987654321");

    CHECK_EQUAL("Jane Smith", supplier.getContactPerson());
    CHECK_EQUAL("+0987654321", supplier.getPhoneNumber());
    supplier.updateContactInfo("", "+1111111111");
    CHECK_EQUAL("", supplier.getContactPerson());
    supplier.updateContactInfo("John Doe", "");
    CHECK_EQUAL("", supplier.getPhoneNumber());
}

TEST(Supplier_SuppliesItem) {
    Supplier supplier("SUP123", "Test Supplier", "John Doe", "+1234567890");

    CHECK(!supplier.suppliesItem("Item 1"));

    supplier.addSuppliedItem("Item 1");
    CHECK(supplier.suppliesItem("Item 1"));
    CHECK(!supplier.suppliesItem("Non-existent Item"));

    supplier.addSuppliedItem("Item 2");
    supplier.addSuppliedItem("Item 3");

    CHECK(supplier.suppliesItem("Item 2"));
    CHECK(supplier.suppliesItem("Item 3"));

    supplier.removeSuppliedItem("Item 1");
    CHECK(!supplier.suppliesItem("Item 1"));
}

TEST(Supplier_Getters) {
    Supplier supplier("SUP123", "Test Supplier", "John Doe", "+1234567890");

    CHECK_EQUAL("SUP123", supplier.getSupplierId());
    CHECK_EQUAL("Test Supplier", supplier.getName());
    CHECK_EQUAL("John Doe", supplier.getContactPerson());
    CHECK_EQUAL("+1234567890", supplier.getPhoneNumber());

    CHECK(supplier.getSuppliedItems().empty());

    supplier.addSuppliedItem("Item 1");
    supplier.addSuppliedItem("Item 2");

    const auto& items = supplier.getSuppliedItems();
    CHECK_EQUAL(2, items.size());
    if (items.size() >= 2) {
        bool hasItem1 = false;
        bool hasItem2 = false;
        for (const auto& item : items) {
            if (item == "Item 1") hasItem1 = true;
            if (item == "Item 2") hasItem2 = true;
        }
        CHECK(hasItem1);
        CHECK(hasItem2);
    }
}
