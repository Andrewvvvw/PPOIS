#ifndef LAB3_ONLINEPAYMENT_H
#define LAB3_ONLINEPAYMENT_H
#include "../Payment.h"

class OnlinePayment : public Payment {
private:
    std::string transactionId;
    std::string paymentGateway;
    std::string customerEmail;
    std::string paymentMethod;

public:
    OnlinePayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                  const std::string& transactionId, const std::string& paymentGateway,
                  const std::string& customerEmail, const std::string& paymentMethod);

    bool processPayment() override;
    std::string getPaymentDetails() const override;
    bool supportsRefund() const override;

    bool verifyTransaction() const;

};
#endif //LAB3_ONLINEPAYMENT_H
