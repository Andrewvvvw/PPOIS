#include "OnlinePayment.h"

OnlinePayment::OnlinePayment(int id, Invoice* invoice, double amount, const std::string& paymentDate,
                           const std::string& transactionId, const std::string& paymentGateway,
                           const std::string& customerEmail, const std::string& paymentMethod)
    : Payment(id, invoice, amount, paymentDate),
      transactionId(transactionId),
      paymentGateway(paymentGateway),
      customerEmail(customerEmail),
      paymentMethod(paymentMethod) {}

bool OnlinePayment::processPayment() {

    if (!verifyTransaction()) {
        updateStatus("Failed: Transaction verification failed");
        return false;
    }

    updateStatus("Completed");
    return true;
}

std::string OnlinePayment::getPaymentDetails() const {
    return "Online Payment - Gateway: " + paymentGateway +
           " - Method: " + paymentMethod +
           " - Amount: " + std::to_string(getAmount()) +
           " USD - Transaction: " + transactionId;
}

bool OnlinePayment::supportsRefund() const {
    return true;
}

bool OnlinePayment::verifyTransaction() const {

    return !transactionId.empty() &&
           !paymentGateway.empty() &&
           !customerEmail.empty() &&
           customerEmail.find('@') != std::string::npos;
}
