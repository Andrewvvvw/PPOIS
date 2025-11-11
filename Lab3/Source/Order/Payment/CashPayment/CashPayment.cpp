#include "CashPayment.h"

CashPayment::CashPayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                         double amountTendered, const std::string& cashierName, const std::string& receiptNumber)
        : Payment(id, invoice, amount, paymentDate),
          amountTendered(amountTendered),
          cashierName(cashierName),
          receiptNumber(receiptNumber),
          changeGiven(amountTendered > amount) {}

bool CashPayment::processPayment() {
    if (amountTendered < getAmount()) {
        updateStatus("Failed: Insufficient funds");
        return false;
    }

    updateStatus("Completed");
    return true;
}

std::string CashPayment::getPaymentDetails() const {
    std::string details = "Cash Payment - Amount: " + std::to_string(getAmount()) +
                          " USD - Tendered: " + std::to_string(amountTendered) +
                          " USD - Change: " + std::to_string(calculateChange()) + " USD";
    return details;
}

bool CashPayment::supportsRefund() const {
    return true;
}

double CashPayment::calculateChange() const {
    return (amountTendered > getAmount()) ? (amountTendered - getAmount()) : 0.0;
}

bool CashPayment::isExactAmount() const {
    return std::abs(amountTendered - getAmount()) < 0.01;
}