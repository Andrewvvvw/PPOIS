#include "../../../Source/Order/Payment/OnlinePayment/OnlinePayment.h"
#include "../../../Source/Order/Invoice/Invoice.h"
#include "../../../Source/Order/Order.h"
#include "../../../Source/Customer/Customer.h"
#include <UnitTest++.h>

SUITE(OnlinePaymentTest) {
    TEST(TestOnlinePaymentCreation) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment payment(1, &invoice, 100.0, "2025-12-31",
                            "TXN123456789", "Stripe", "customer@example.com", "Credit Card");

        CHECK_EQUAL(1, payment.getPaymentId());
        CHECK_EQUAL(100.0, payment.getAmount());
        CHECK_EQUAL("2025-12-31", payment.getPaymentDate());
    }

    TEST(TestProcessPaymentSuccess) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment payment(1, &invoice, 100.0, "2025-12-31",
                            "TXN123456789", "Stripe", "customer@example.com", "Credit Card");

        CHECK(payment.processPayment());
        CHECK(payment.isPaymentSuccessful());
    }

    TEST(TestGetPaymentDetails) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment payment(1, &invoice, 100.0, "2025-12-31",
                              "TXN123456789", "Stripe", "customer@example.com", "Credit Card");

        std::string details = payment.getPaymentDetails();
                CHECK(details.find("Online Payment") != std::string::npos);
                CHECK(details.find("100.000000") != std::string::npos);
                CHECK(details.find("TXN123456789") != std::string::npos);
                CHECK(details.find("Stripe") != std::string::npos);
                CHECK(details.find("Credit Card") != std::string::npos);
    }

    TEST(TestSupportsRefund) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment payment(1, &invoice, 100.0, "2025-12-31",
                            "TXN123456789", "Stripe", "customer@example.com", "Credit Card");

        CHECK(payment.supportsRefund());
    }

    TEST(TestVerifyTransaction) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment payment1(1, &invoice, 100.0, "2025-12-31",
                             "TXN123456789", "Stripe", "customer@example.com", "Credit Card");
        CHECK(payment1.verifyTransaction());

        OnlinePayment payment2(1, &invoice, 100.0, "2025-12-31",
                             "", "Stripe", "customer@example.com", "Credit Card");
        CHECK(!payment2.verifyTransaction());
    }

    TEST(TestDifferentPaymentGateways) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment stripePayment(1, &invoice, 100.0, "2025-12-31",
                                  "TXN123456789", "Stripe", "customer@example.com", "Credit Card");
        CHECK(stripePayment.processPayment());

        OnlinePayment paypalPayment(2, &invoice, 200.0, "2025-12-31",
                                  "PAY987654321", "PayPal", "customer@example.com", "PayPal Balance");
        CHECK(paypalPayment.processPayment());
    }

    TEST(TestEdgeCases) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        OnlinePayment zeroPayment(1, &invoice, 0.0, "2025-12-31",
                                "TXN000000000", "Stripe", "customer@example.com", "Credit Card");
        CHECK(zeroPayment.processPayment());

        OnlinePayment smallPayment(2, &invoice, 0.01, "2025-12-31",
                                 "TXN999999999", "Stripe", "customer@example.com", "Credit Card");
        CHECK(smallPayment.processPayment());
    }
}
