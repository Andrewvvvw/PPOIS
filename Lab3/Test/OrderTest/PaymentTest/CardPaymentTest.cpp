#include "../../../Source/Order/Payment/CardPayment/CardPayment.h"
#include "../../../Source/Order/Invoice/Invoice.h"
#include "../../../Source/Order/Order.h"
#include "../../../Source/Customer/Customer.h"
#include "../../../Source/Exceptions/Exceptions.h"
#include <UnitTest++.h>

SUITE(CardPaymentTest) {
    TEST(TestCardPaymentCreation) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 110.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        CHECK_EQUAL(1, payment.getPaymentId());
        CHECK_EQUAL(110.0, payment.getAmount());
        CHECK_EQUAL("2025-12-31", payment.getPaymentDate());
    }

    TEST(TestProcessPayment) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 110.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        CHECK(payment.processPayment());
        CHECK(payment.isPaymentSuccessful());
    }

    TEST(TestGetPaymentDetails) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 110.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        std::string details = payment.getPaymentDetails();
        CHECK(details.find("Card Payment") != std::string::npos);
        CHECK(details.find("****1111") != std::string::npos);
        CHECK(details.find("John Doe") != std::string::npos);
    }

    TEST(TestSupportsRefund) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 110.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        CHECK(payment.supportsRefund());
    }

    TEST(TestValidateCard) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        CardPayment validPayment(1, &invoice, 110.0, "2025-12-31",
                               "4111111111111111", "John Doe", "12/25", "123", "Visa");
        CHECK(validPayment.validateCard());
    }

    TEST(TestMaskCardNumber) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 110.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        std::string masked = payment.maskCardNumber();
        CHECK_EQUAL("****1111", masked);
    }

    TEST(TestProcessCardFee) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");
        CardPayment payment(1, &invoice, 100.0, "2025-12-31",
                          "4111111111111111", "John Doe", "12/25", "123", "Visa");

        payment.processCardFee();
        CHECK_EQUAL(100.0, payment.getAmount());
    }

    TEST(TestInvalidCard) {
        Customer customer("Test Customer", 1);
        Order order(1, &customer, 0.0);
        Invoice invoice(1, &order, "2025-12-30", "2026-01-30");

        CardPayment invalidPayment(2, &invoice, 110.0, "2025-12-31",
                                 "1234", "John Doe", "12/25", "123", "Visa");
        CHECK(!invalidPayment.validateCard());
    }
}
