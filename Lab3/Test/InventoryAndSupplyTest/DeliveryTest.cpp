#include "UnitTest++.h"
#include "../../Source/InventoryAndSupply/Delivery/Delivery.h"

TEST(Delivery_Constructor) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    CHECK_EQUAL("DEL123", delivery.getDeliveryId());
    CHECK_EQUAL("ORD456", delivery.getOrderId());
    CHECK_EQUAL("2023-11-10", delivery.getDeliveryDate());
    CHECK_EQUAL("Scheduled", delivery.getStatus());
    CHECK_EQUAL("John Doe", delivery.getDeliveryPerson());
    CHECK(!delivery.isDelivered());
}

TEST(Delivery_UpdateStatus) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    delivery.updateStatus("In Transit");
    CHECK_EQUAL("In Transit", delivery.getStatus());

    delivery.updateStatus("Delivered");
    CHECK_EQUAL("Delivered", delivery.getStatus());
}

TEST(Delivery_ChangeDeliveryPerson) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    delivery.changeDeliveryPerson("Jane Smith");
    CHECK_EQUAL("Jane Smith", delivery.getDeliveryPerson());

    delivery.changeDeliveryPerson("Bob Johnson");
    CHECK_EQUAL("Bob Johnson", delivery.getDeliveryPerson());
}

TEST(Delivery_IsDelivered) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    CHECK(!delivery.isDelivered());

    delivery.updateStatus("In Transit");
    CHECK(!delivery.isDelivered());

    delivery.updateStatus("Delivered");
    CHECK(delivery.isDelivered());
}

TEST(Delivery_ProcessDelivery) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    CHECK_EQUAL("Scheduled", delivery.getStatus());

    delivery.processDelivery();
    CHECK_EQUAL("In Transit", delivery.getStatus());
}

TEST(Delivery_Getters) {
    Delivery delivery("DEL123", "ORD456", "2023-11-10", "John Doe");

    CHECK_EQUAL("DEL123", delivery.getDeliveryId());
    CHECK_EQUAL("ORD456", delivery.getOrderId());
    CHECK_EQUAL("2023-11-10", delivery.getDeliveryDate());
    CHECK_EQUAL("Scheduled", delivery.getStatus());
    CHECK_EQUAL("John Doe", delivery.getDeliveryPerson());
}
