#include "../../../Source/Order/Payment/CashPayment/CashPayment.h"
#include "../../../Source/Order/Invoice/Invoice.h"
#include "../../../Source/Order/Order.h"
#include "../../../Source/Customer/Customer.h"
#include <UnitTest++.h>

SUITE(CashPaymentTest) {
    TEST(TestCashPaymentCreation) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CashPayment payment(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-001");

        CHECK_EQUAL(1, payment.getPaymentId());
        CHECK_EQUAL(100.0, payment.getAmount());
        CHECK_EQUAL("2025-12-31", payment.getPaymentDate());
    }

    TEST(TestProcessPaymentSuccess) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CashPayment payment(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-001");

        CHECK(payment.processPayment());
        CHECK(payment.isPaymentSuccessful());
    }

    TEST(TestProcessPaymentInsufficientFunds) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CashPayment payment(1, &invoice, 100.0, "2025-12-31", 80.0, "John Doe", "RCPT-001");

        CHECK(!payment.processPayment());
        CHECK(!payment.isPaymentSuccessful());
    }

    TEST(TestGetPaymentDetails) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CashPayment payment(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-001");

        std::string details = payment.getPaymentDetails();
        CHECK(details.find("Cash Payment") != std::string::npos);
        CHECK(details.find("100.000000") != std::string::npos);
        CHECK(details.find("120.000000") != std::string::npos);
        CHECK(details.find("20.000000") != std::string::npos);
    }

    TEST(TestSupportsRefund) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CashPayment payment(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-001");

        CHECK(payment.supportsRefund());
    }

    TEST(TestCalculateChange) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        CashPayment payment1(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-001");
        CHECK_EQUAL(20.0, payment1.calculateChange());

        CashPayment payment2(1, &invoice, 100.0, "2025-12-31", 100.0, "John Doe", "RCPT-002");
        CHECK_EQUAL(0.0, payment2.calculateChange());

        CashPayment payment3(1, &invoice, 100.0, "2025-12-31", 80.0, "John Doe", "RCPT-003");
        CHECK_EQUAL(0.0, payment3.calculateChange());
    }

    TEST(TestIsExactAmount) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        CashPayment payment1(1, &invoice, 100.0, "2025-12-31", 100.0, "John Doe", "RCPT-001");
        CHECK(payment1.isExactAmount());

        CashPayment payment2(1, &invoice, 100.0, "2025-12-31", 120.0, "John Doe", "RCPT-002");
        CHECK(!payment2.isExactAmount());

        CashPayment payment3(1, &invoice, 100.0, "2025-12-31", 100.001, "John Doe", "RCPT-003");
        CHECK(payment3.isExactAmount());
    }

    TEST(TestEdgeCases) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        CashPayment payment1(1, &invoice, 0.0, "2025-12-31", 0.0, "John Doe", "RCPT-001");
        CHECK(payment1.isExactAmount());
        CHECK(payment1.processPayment());

        CashPayment payment2(1, &invoice, 0.01, "2025-12-31", 0.01, "John Doe", "RCPT-002");
        CHECK(payment2.isExactAmount());
        CHECK(payment2.processPayment());
    }
}
