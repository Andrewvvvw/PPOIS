#include "UnitTest++.h"
#include "Source/Customer/RegularCustomer/RegularCustomer.h"

SUITE(RegularCustomerTest) {
    TEST(ConstructorAndGetters) {
        RegularCustomer customer("John Doe", 1);
        CHECK_EQUAL("John Doe", customer.getName());
        CHECK_EQUAL(1, customer.getId());
        CHECK_EQUAL(0.0, customer.getTotalSpent());
    }

    TEST(TotalSpent) {
        RegularCustomer customer("Jane Smith", 2, 100.0);
        CHECK_EQUAL(100.0, customer.getTotalSpent());

        customer.setTotalSpent(200.0);
        CHECK_EQUAL(200.0, customer.getTotalSpent());
    }

    TEST(AddFavoriteItems) {
        RegularCustomer customer("Alice Brown", 3);

        customer.addFavoriteItem(101);
        customer.addFavoriteItem(102);
        customer.addFavoriteItem(101);

        customer.addFavoriteItem(103);
    }
}