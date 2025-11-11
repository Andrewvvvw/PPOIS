#include "UnitTest++.h"
#include "Source/Customer/VIPCustomer/VIPCustomer.h"

SUITE(VIPCustomerTest) {
    TEST(ConstructorAndGetters) {
        VIPCustomer customer("John Doe", 1, "Manager1", 5000.0);
        CHECK_EQUAL("John Doe", customer.getName());
        CHECK_EQUAL(1, customer.getId());
        CHECK_EQUAL(0.0, customer.getTotalSpent());
    }

    TEST(ReserveItems) {
        VIPCustomer customer("Bob Wilson", 4, "Manager4");

        customer.reserveItem(101);
        customer.reserveItem(102);
        customer.reserveItem(101);
        customer.reserveItem(103);
    }

    TEST(SetPersonalManager) {
        VIPCustomer customer("Charlie Davis", 5, "Manager5");

        customer.setPersonalManager("New Manager");
    }

    TEST(TotalSpent) {
        VIPCustomer customer("Customer3", 8, "Manager8");

        customer.setTotalSpent(1000.0);
        CHECK_EQUAL(1000.0, customer.getTotalSpent());

        customer.setTotalSpent(5000.0);
        CHECK_EQUAL(5000.0, customer.getTotalSpent());
    }
}