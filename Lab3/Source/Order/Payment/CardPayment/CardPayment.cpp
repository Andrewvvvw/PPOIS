#include "CardPayment.h"

CardPayment::CardPayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                         const std::string& cardNumber, const std::string& cardHolderName,
                         const std::string& expiryDate, const std::string& cvv, const std::string& cardType)
        : Payment(id, invoice, amount, paymentDate),
          cardNumber(cardNumber),
          cardHolderName(cardHolderName),
          expiryDate(expiryDate),
          cvv(cvv),
          cardType(cardType) {}

bool CardPayment::processPayment() {
    if (!validateCard()) {
        updateStatus("Failed: Invalid card details");
        return false;
    }

    processCardFee();
    updateStatus("Completed");
    return true;
}

std::string CardPayment::getPaymentDetails() const {
    return "Card Payment - " + cardType + " - " + maskCardNumber() +
           " - " + cardHolderName + " - " + std::to_string(getAmount()) + " USD";
}

bool CardPayment::supportsRefund() const {
    return true;
}

bool CardPayment::validateCard() const {
    return !cardNumber.empty() && cardNumber.length() >= 13 &&
           !expiryDate.empty() && !cvv.empty() && cvv.length() == 3;
}

void CardPayment::processCardFee() {
    const double feeRate = 0.02;
    double fee = getAmount() * feeRate;
}

std::string CardPayment::maskCardNumber() const {
    if (cardNumber.length() < 4) return "****";
    return std::string(4, '*') + cardNumber.substr(cardNumber.length() - 4);
}