#include "UnitTest++.h"
#include "Source/Customer/Customer.h"

SUITE(CustomerTest) {
    TEST(ConstructorAndGetters) {
        Customer customer("John Doe", 1, 100.0);

        CHECK_EQUAL("John Doe", customer.getName());
        CHECK_EQUAL(1, customer.getId());
        CHECK_EQUAL(100.0, customer.getTotalSpent());
    }

    TEST(DefaultTotalSpent) {
        Customer customer("Jane Smith", 2);

        CHECK_EQUAL("Jane Smith", customer.getName());
        CHECK_EQUAL(2, customer.getId());
        CHECK_EQUAL(0.0, customer.getTotalSpent());
    }

    TEST(SetTotalSpent) {
        Customer customer("Alice Brown", 3);

        customer.setTotalSpent(200.0);
        CHECK_EQUAL(200.0, customer.getTotalSpent());

        customer.setTotalSpent(0.0);
        CHECK_EQUAL(0.0, customer.getTotalSpent());

        customer.setTotalSpent(9999.99);
        CHECK_EQUAL(9999.99, customer.getTotalSpent());
    }

    TEST(EdgeCases) {
        Customer emptyName("", 6);
        CHECK_EQUAL("", emptyName.getName());

        Customer zeroId("Zero", 0);
        CHECK_EQUAL(0, zeroId.getId());

        Customer negativeTotal("Negative", 7, -100.0);
        CHECK_EQUAL(-100.0, negativeTotal.getTotalSpent());
    }
}