#include <UnitTest++.h>
#include "../../Source/Order/Order.h"
#include "../../Source/Customer/Customer.h"
#include "../../Source/Order/OrderItem/OrderItem.h"
#include "../../Source/Order/Discount/Discount.h"

SUITE(OrderTest) {
    TEST(TestOrderCreation) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 10.0);

        CHECK_EQUAL(1, order.getOrderId());
        CHECK_EQUAL(10.0, order.getServiceCharge());
        CHECK(!order.getPaymentStatus());
    }

    TEST(TestAddRemoveCustomer) {
        Customer customer1("Customer 1", 1);
        Customer customer2("Customer 2", 2);
        Order order(1, &customer1);

        order.addCustomer(&customer2);
        const auto& customers = order.getCustomers();
        CHECK_EQUAL(2, customers.size());

        order.removeCustomer(1);
        CHECK_EQUAL(1, customers.size());
        CHECK_EQUAL(2, customers[0]->getId());
    }

    TEST(TestAddRemoveItems) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer);
        OrderItem item1("Pizza", 2, 10.0);
        OrderItem item2("Burger", 3, 5.0);

        order.addItem(item1);
        order.addItem(item2, &customer);

        CHECK_EQUAL(35.0, order.calculateSubtotal());
        CHECK_EQUAL(35.0, order.calculateTotal());
        order.removeItem(0);
        CHECK_EQUAL(15.0, order.calculateSubtotal());
    }

    TEST(TestDiscounts) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer);
        OrderItem item("Pizza", 2, 10.0);
        order.addItem(item);

        auto discount = std::make_unique<Discount>("TEST10", 10.0);
        order.applyDiscount(std::move(discount));

        CHECK_EQUAL(18.0, order.calculateTotal());

        order.removeDiscount();
        CHECK_EQUAL(20.0, order.calculateTotal());
    }

    TEST(TestMarkAsPaid) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer);

        CHECK(!order.getPaymentStatus());
        order.markAsPaid();
        CHECK(order.getPaymentStatus());
    }

    TEST(TestBillSplitting) {
        Customer customer1("Customer 1", 1);
        Customer customer2("Customer 2", 2);
        Order order(1, &customer1);
        order.addCustomer(&customer2);

        OrderItem item1("Pizza", 1, 30.0);
        OrderItem item2("Burger", 1, 10.0);

        order.addItem(item1, &customer1);
        order.addItem(item2, &customer2);

        auto bills = order.getIndividualBills();
        CHECK_EQUAL(2, bills.size());
        CHECK_EQUAL(30.0, bills[&customer1]);
        CHECK_EQUAL(10.0, bills[&customer2]);

        CHECK_EQUAL(30.0, order.getCustomerShare(&customer1));
        CHECK_EQUAL(10.0, order.getCustomerShare(&customer2));
    }
    TEST(TestLoyaltyProgram) {
        {
            Customer customer("New Customer", 1);
            Order order(1, &customer);
            OrderItem item("Pizza", 1, 100.0);
            order.addItem(item);

                    CHECK_EQUAL(0.0, order.getLoyaltyDiscount(1));
                    CHECK_EQUAL("Regular", order.getCustomerTier(1));

            order.applyLoyaltyDiscount(1);
                    CHECK_EQUAL(0.0, order.getLoyaltyDiscount(1));

                    CHECK_EQUAL(100.0, order.calculateTotal());
        }
        {
            Customer customer("Silver Customer", 2);
            Order order(2, &customer);
            OrderItem item("Expensive Item", 1, 1000.0);
            order.addItem(item);

            order.applyLoyaltyDiscount(2);

                    CHECK_EQUAL(0.05, order.getLoyaltyDiscount(2));
                    CHECK_EQUAL("Silver", order.getCustomerTier(2));

                    CHECK_EQUAL(950.0, order.calculateTotal());
        }

        {
            Customer customer("Gold Customer", 3);
            Order order(3, &customer);
            OrderItem item("Very Expensive Item", 1, 5000.0);
            order.addItem(item);

            order.applyLoyaltyDiscount(3);

                    CHECK_EQUAL(0.1, order.getLoyaltyDiscount(3));
                    CHECK_EQUAL("Gold", order.getCustomerTier(3));

                    CHECK_EQUAL(4500.0, order.calculateTotal());
        }

        {
            {
                Customer customer("Test Customer", 4);
                Order order1(4, &customer);
                OrderItem item1("Item 1", 1, 1000.0);
                order1.addItem(item1);

                order1.applyLoyaltyDiscount(4);
                        CHECK_EQUAL(0.05, order1.getLoyaltyDiscount(4));
                        CHECK_EQUAL("Silver", order1.getCustomerTier(4));
                        CHECK_EQUAL(950.0, order1.calculateTotal());
            }

            {
                Customer customer("Test Customer", 4);
                Order order2(5, &customer);
                OrderItem item2("Item 2", 1, 500.0);
                order2.addItem(item2);

                order2.applyLoyaltyDiscount(4);
                        CHECK_EQUAL(0.0, order2.getLoyaltyDiscount(4));
                        CHECK_EQUAL("Regular", order2.getCustomerTier(4));
                        CHECK_EQUAL(500.0, order2.calculateTotal());
            }
        }
    }
}
