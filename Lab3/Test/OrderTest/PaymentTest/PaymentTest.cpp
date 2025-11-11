#include <UnitTest++.h>
#include "../../../Source/Order/Order.h"
#include "../../../Source/Order/Invoice/Invoice.h"
#include "../../../Source/Order/Payment/OnlinePayment/OnlinePayment.h"

SUITE(PaymentTest) {
        TEST(TestPaymentGetters) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(1, &invoice, 100.0, "2023-11-10", "TXN123", "Stripe", "test@example.com", "Credit Card");

            CHECK_EQUAL(1, payment.getPaymentId());
            CHECK_EQUAL(100.0, payment.getAmount());
            CHECK_EQUAL("2023-11-10", payment.getPaymentDate());
            CHECK_EQUAL("Pending", payment.getStatus());
            CHECK_EQUAL(&invoice, payment.getInvoice());
        }

        TEST(TestProcessPayment) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(2, &invoice, 100.0, "2023-11-10", "TXN124", "PayPal", "test2@example.com", "PayPal");

            CHECK(payment.processPayment());
            CHECK_EQUAL("Completed", payment.getStatus());
        }

        TEST(TestUpdateStatus) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(3, &invoice, 100.0, "2023-11-10", "TXN125", "Stripe", "test3@example.com", "Debit Card");

            payment.updateStatus("Failed");
            CHECK_EQUAL("Failed", payment.getStatus());
        }

        TEST(TestIsPaymentSuccessful) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(4, &invoice, 100.0, "2023-11-10", "TXN126", "Stripe", "test4@example.com", "Credit Card");

            CHECK(!payment.isPaymentSuccessful());
            payment.processPayment();
            CHECK(payment.isPaymentSuccessful());
        }

        TEST(TestSupportsRefund) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(5, &invoice, 100.0, "2023-11-10", "TXN127", "Stripe", "test5@example.com", "Credit Card");

            CHECK(payment.supportsRefund());
        }

    TEST(TestGetPaymentDetails) {
        Order order(1, nullptr);
        Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
        OnlinePayment payment(6, &invoice, 100.0, "2023-11-10", "TXN128", "Stripe", "test6@example.com", "Credit Card");

        std::string details = payment.getPaymentDetails();
                CHECK(details.find("Online Payment - Gateway: Stripe") != std::string::npos);
                CHECK(details.find("Method: Credit Card") != std::string::npos);
                CHECK(details.find("Amount: 100.000000") != std::string::npos);
    }
        TEST(TestVerifyTransaction) {
            Order order(1, nullptr);
            Invoice invoice(1, &order, "2023-11-10", "2023-12-10");
            OnlinePayment payment(7, &invoice, 100.0, "2023-11-10", "TXN129", "Stripe", "test7@example.com", "Credit Card");

            CHECK(payment.verifyTransaction());
        }
}