#include "../../Source/Order/Invoice/Invoice.h"
#include "../../Source/Order/Order.h"
#include "../../Source/Customer/Customer.h"
#include "../../Source/Order/OrderItem/OrderItem.h"
#include "../../Source/Order/Discount/Discount.h"
#include "../../Source/Exceptions/Exceptions.h"
#include <UnitTest++.h>
#include <memory>

SUITE(InvoiceTest) {
    TEST(TestInvoiceCreation) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);

        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        CHECK_EQUAL(1001, invoice.getInvoiceId());
        CHECK_EQUAL(&order, invoice.getOrder());
        CHECK_EQUAL("2025-11-10", invoice.getIssueDate());
        CHECK_EQUAL("2025-12-10", invoice.getDueDate());
        CHECK_EQUAL(false, invoice.getIsPaid());
    }

    TEST(TestUpdateDueDate) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);
        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        invoice.updateDueDate("2025-12-31");
        CHECK_EQUAL("2025-12-31", invoice.getDueDate());
    }

    TEST(TestMarkAsPaid) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);
        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        CHECK_EQUAL(false, invoice.getIsPaid());
        invoice.markAsPaid();
        CHECK_EQUAL(true, invoice.getIsPaid());
    }

    TEST(TestCalculateTotal) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);
        OrderItem item1("Item 1", 2, 100.0);
        OrderItem item2("Item 2", 3, 50.0);

        order.addItem(item1);
        order.addItem(item2);

        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        double expectedTotal = 100.0 * 2 + 50.0 * 3;
                CHECK_EQUAL(expectedTotal, invoice.calculateTotal());
    }

    TEST(TestCalculateTotalWithDiscount) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);
        OrderItem item1("Item 1", 2, 100.0);
        OrderItem item2("Item 2", 3, 50.0);

        order.addItem(item1);
        order.addItem(item2);

        auto discount = std::make_unique<Discount>("SALE10", 10.0, true);
        order.applyDiscount(std::move(discount));

        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        double subtotal = 100.0 * 2 + 50.0 * 3;
        double expectedTotal = subtotal * 0.9;
                CHECK_EQUAL(expectedTotal, invoice.calculateTotal());
    }

    TEST(TestGenerateInvoiceNumber) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);

        Invoice invoice1(1, &order, "2025-11-10", "2025-12-10");
        CHECK_EQUAL("INV-000001", invoice1.generateInvoiceNumber());

        Invoice invoice2(42, &order, "2025-11-10", "2025-12-10");
        CHECK_EQUAL("INV-000042", invoice2.generateInvoiceNumber());

        Invoice invoice3(999999, &order, "2025-11-10", "2025-12-10");
        CHECK_EQUAL("INV-999999", invoice3.generateInvoiceNumber());
    }

    TEST(TestIsOverdue) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);

        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        CHECK_EQUAL(false, invoice.isOverdue("2025-12-09"));

        CHECK_EQUAL(false, invoice.isOverdue("2025-12-10"));

        CHECK_EQUAL(true, invoice.isOverdue("2025-12-11"));

        invoice.markAsPaid();
        CHECK_EQUAL(false, invoice.isOverdue("2025-12-11"));
    }

    TEST(TestNullOrder) {
        Invoice invoice(1001, nullptr, "2025-11-10", "2025-12-10");

        CHECK_EQUAL(0.0, invoice.calculateTotal());
        CHECK_EQUAL("INV-001001", invoice.generateInvoiceNumber());
    }

    TEST(TestMultipleUpdates) {
        Customer customer("John Doe", 1);
        Order order(1, &customer);
        Invoice invoice(1001, &order, "2025-11-10", "2025-12-10");

        CHECK_EQUAL(false, invoice.getIsPaid());

        invoice.updateDueDate("2025-12-31");
        CHECK_EQUAL("2025-12-31", invoice.getDueDate());

        invoice.markAsPaid();
        CHECK_EQUAL(true, invoice.getIsPaid());

        invoice.updateDueDate("2025-01-01");
        CHECK_EQUAL(true, invoice.getIsPaid());
    }
}
