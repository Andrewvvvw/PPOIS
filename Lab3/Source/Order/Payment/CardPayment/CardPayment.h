#ifndef LAB3_CARDPAYMENT_H
#define LAB3_CARDPAYMENT_H
#include "../Payment.h"

class CardPayment : public Payment {
private:
    std::string cardNumber;
    std::string cardHolderName;
    std::string expiryDate;
    std::string cvv;
    std::string cardType;

public:
    CardPayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                const std::string& cardNumber, const std::string& cardHolderName,
                const std::string& expiryDate, const std::string& cvv, const std::string& cardType);

    bool processPayment() override;
    std::string getPaymentDetails() const override;
    bool supportsRefund() const override;

    bool validateCard() const;
    void processCardFee();
    std::string maskCardNumber() const;
};
#endif //LAB3_CARDPAYMENT_H
