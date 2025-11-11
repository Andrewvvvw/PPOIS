#ifndef LAB3_PAYMENT_H
#define LAB3_PAYMENT_H

#include <string>
#include "../Invoice/Invoice.h"

class Payment {
protected:
    int paymentId;
    Invoice* invoice;
    double amount;
    std::string paymentDate;
    std::string status;

public:
    Payment(int id, Invoice* invoice, double amount, const std::string& paymentDate);

    virtual ~Payment() = default;

    int getPaymentId() const;
    Invoice* getInvoice() const;
    double getAmount() const;
    std::string getPaymentDate() const;
    std::string getStatus() const;

    virtual bool processPayment() = 0;
    void updateStatus(const std::string& newStatus);
    bool isPaymentSuccessful() const;
    virtual std::string getPaymentDetails() const = 0;
    virtual bool supportsRefund() const = 0;
};

#endif //LAB3_PAYMENT_H
