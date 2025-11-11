#ifndef LAB3_CASHPAYMENT_H
#define LAB3_CASHPAYMENT_H
#include "../Payment.h"

class CashPayment : public Payment {
private:
    double amountTendered;
    std::string cashierName;
    std::string receiptNumber;
    bool changeGiven;

public:
    CashPayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                double amountTendered, const std::string& cashierName, const std::string& receiptNumber);

    bool processPayment() override;
    std::string getPaymentDetails() const override;
    bool supportsRefund() const override;

    double calculateChange() const;
    bool isExactAmount() const;
};
#endif //LAB3_CASHPAYMENT_H
