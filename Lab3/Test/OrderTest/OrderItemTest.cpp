#include "../../Source/Order/OrderItem/OrderItem.h"
#include "../../Source/Exceptions/Exceptions.h"
#include <UnitTest++.h>

SUITE(OrderItemTest) {
    TEST(TestOrderItemCreation) {
        OrderItem item("Pizza Margherita", 2, 12.99);

                CHECK_EQUAL("Pizza Margherita", item.getDishName());
                CHECK_EQUAL(2, item.getQuantity());
                CHECK_EQUAL(12.99, item.getPricePerItem());
                CHECK_EQUAL(25.98, item.calculateItemTotal());
    }

    TEST(TestInvalidPrice) {
                CHECK_THROW(OrderItem("Invalid Item", 1, 0.0), ExceptionIncorrectItemPrice);
                CHECK_THROW(OrderItem("Invalid Item", 1, -5.0), ExceptionIncorrectItemPrice);
    }

    TEST(TestSetQuantity) {
        OrderItem item("Pasta Carbonara", 1, 14.50);

        item.setQuantity(3);
                CHECK_EQUAL(3, item.getQuantity());
                CHECK_EQUAL(43.50, item.calculateItemTotal());

        item.setQuantity(0);
                CHECK_EQUAL(3, item.getQuantity());

        item.setQuantity(-5);
                CHECK_EQUAL(3, item.getQuantity());
    }

    TEST(TestCalculateItemTotal) {
        OrderItem item1("Caesar Salad", 2, 8.99);
                CHECK_EQUAL(17.98, item1.calculateItemTotal());

        OrderItem item2("Ice Cream", 1, 4.50);
                CHECK_EQUAL(4.50, item2.calculateItemTotal());

        OrderItem item3("Soda", 5, 2.00);
                CHECK_EQUAL(10.00, item3.calculateItemTotal());
    }

    TEST(TestEdgeCases) {
        OrderItem item("Minimal Item", 1, 0.01);
                CHECK_EQUAL(0.01, item.calculateItemTotal());

        item.setQuantity(1000);
                CHECK_EQUAL(10.00, item.calculateItemTotal());
    }

    TEST(TestGetMethods) {
        OrderItem item("Test Item", 42, 1.23);

                CHECK_EQUAL("Test Item", item.getDishName());
                CHECK_EQUAL(42, item.getQuantity());
                CHECK_EQUAL(1.23, item.getPricePerItem());
    }

    TEST(TestMultipleItems) {
        OrderItem item1("Item A", 1, 10.0);
        OrderItem item2("Item B", 2, 15.0);
        OrderItem item3("Item C", 3, 20.0);

                CHECK_EQUAL(10.0, item1.calculateItemTotal());
                CHECK_EQUAL(30.0, item2.calculateItemTotal());
                CHECK_EQUAL(60.0, item3.calculateItemTotal());
    }

    TEST(TestPrecision) {
        OrderItem item("Precision Test", 3, 3.33);
                CHECK_CLOSE(9.99, item.calculateItemTotal(), 0.001);
    }
}