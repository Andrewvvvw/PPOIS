#include "Payment.h"

Payment::Payment(int id, Invoice* invoice, double amount, const std::string& paymentDate)
    : paymentId(id), invoice(invoice), amount(amount), paymentDate(paymentDate), status("Pending") {}

int Payment::getPaymentId() const {
    return paymentId;
}

Invoice* Payment::getInvoice() const {
    return invoice;
}

double Payment::getAmount() const {
    return amount;
}

std::string Payment::getPaymentDate() const {
    return paymentDate;
}

std::string Payment::getStatus() const {
    return status;
}

void Payment::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

bool Payment::isPaymentSuccessful() const {
    return status == "Completed";
}
