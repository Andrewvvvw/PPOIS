#include "../../Source/Order/BillSplitter/BillSplitter.h"
#include "../../Source/Customer/Customer.h"
#include "../../Source/Customer/Guest/Guest.h"
#include "../../Source/Customer/RegularCustomer/RegularCustomer.h"
#include "../../Source/Customer/VIPCustomer/VIPCustomer.h"
#include "../../Source/Exceptions/Exceptions.h"
#include <UnitTest++.h>
#include <memory>

SUITE(BillSplitterTest) {
    TEST(TestBillSplitterCreation) {
        BillSplitter splitter(100.0, 0.1, 4);

                CHECK_THROW(BillSplitter(-100.0, 0.1, 4), ExceptionNegativeBillTotal);
                CHECK_THROW(BillSplitter(100.0, -0.1, 4), ExceptionNegativeServiceCharge);
                CHECK_THROW(BillSplitter(100.0, 0.1, 0), ExceptionIncorrectCustomerAmount);
                CHECK_THROW(BillSplitter(100.0, 0.1, -1), ExceptionIncorrectCustomerAmount);
    }

    TEST(TestSplitBillEqual) {
        std::vector<Customer*> customers;
        Guest guest1("John", 1, "john@example.com");
        Guest guest2("Alice", 2, "alice@example.com");
        customers.push_back(&guest1);
        customers.push_back(&guest2);

        BillSplitter splitter(100.0, 0.0, 2);
        splitter.splitBill(customers);

                CHECK_EQUAL(50.0, splitter.getCustomerShare(&guest1));
                CHECK_EQUAL(50.0, splitter.getCustomerShare(&guest2));
    }

    TEST(TestSplitBillUnequal) {
        std::vector<Customer*> customers;
        Guest guest1("John", 1, "john@example.com");
        Guest guest2("Alice", 2, "alice@example.com");
        Guest guest3("Bob", 3, "bob@example.com");
        customers.push_back(&guest1);
        customers.push_back(&guest2);
        customers.push_back(&guest3);

        BillSplitter splitter(100.0, 0.0, 3);
        splitter.splitBill(customers);

                CHECK_CLOSE(33.3333, splitter.getCustomerShare(&guest1), 0.0001);
                CHECK_CLOSE(33.3333, splitter.getCustomerShare(&guest2), 0.0001);
                CHECK_CLOSE(33.3333, splitter.getCustomerShare(&guest3), 0.0001);
    }

    TEST(TestAddItem) {
        std::vector<Customer*> customers;
        Guest guest("John", 1, "john@example.com");
        customers.push_back(&guest);

        BillSplitter splitter(100.0, 0.0, 1);
        splitter.splitBill(customers);

        splitter.addItem(&guest, 15.0);
                CHECK_EQUAL(115.0, splitter.getCustomerShare(&guest));

                CHECK_THROW(splitter.addItem(&guest, -10.0), ExceptionNegativeItemAmount);
    }

    TEST(TestApplyServiceCharge) {
        std::vector<Customer*> customers;
        Guest guest1("John", 1, "john@example.com");
        Guest guest2("Alice", 2, "alice@example.com");
        customers.push_back(&guest1);
        customers.push_back(&guest2);

        BillSplitter splitter(100.0, 0.1, 2);
        splitter.splitBill(customers);
        splitter.applyServiceCharge();

                CHECK_EQUAL(55.0, splitter.getCustomerShare(&guest1));
                CHECK_EQUAL(55.0, splitter.getCustomerShare(&guest2));

        BillSplitter noChargeSplitter(100.0, 0.0, 2);
        noChargeSplitter.splitBill(customers);
        noChargeSplitter.applyServiceCharge();
                CHECK_EQUAL(50.0, noChargeSplitter.getCustomerShare(&guest1));
    }

    TEST(TestEdgeCases) {
        {
            std::vector<Customer*> emptyCustomers;
            BillSplitter splitter(100.0, 0.1, 1);
            splitter.splitBill(emptyCustomers);
        }

        {
            std::vector<Customer*> customers;
            Guest guest("Single", 1, "single@example.com");
            customers.push_back(&guest);

            BillSplitter splitter(100.0, 0.1, 1);
            splitter.splitBill(customers);
            splitter.applyServiceCharge();

                    CHECK_EQUAL(110.0, splitter.getCustomerShare(&guest));
        }

        {
            std::vector<Customer*> customers;
            Guest guest1("John", 1, "john@example.com");
            Guest guest2("Alice", 2, "alice@example.com");
            customers.push_back(&guest1);
            customers.push_back(&guest2);

            BillSplitter splitter(0.0, 0.1, 2);
            splitter.splitBill(customers);

                    CHECK_EQUAL(0.0, splitter.getCustomerShare(&guest1));
                    CHECK_EQUAL(0.0, splitter.getCustomerShare(&guest2));
        }
    }
}