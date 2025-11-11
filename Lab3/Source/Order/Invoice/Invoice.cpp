#include "Invoice.h"
#include <sstream>
#include <iomanip>

Invoice::Invoice(int id, Order* order, const std::string& issueDate, const std::string& dueDate)
    : invoiceId(id), order(order), issueDate(issueDate), dueDate(dueDate), isPaid(false) {}

int Invoice::getInvoiceId() const {
    return invoiceId;
}

Order* Invoice::getOrder() const {
    return order;
}

std::string Invoice::getIssueDate() const {
    return issueDate;
}

std::string Invoice::getDueDate() const {
    return dueDate;
}

bool Invoice::getIsPaid() const {
    return isPaid;
}

void Invoice::updateDueDate(const std::string& newDueDate) {
    dueDate = newDueDate;
}

void Invoice::markAsPaid() {
    isPaid = true;
}

double Invoice::calculateTotal() const {
    if (order) {
        return order->calculateTotal();
    }
    return 0.0;
}

std::string Invoice::generateInvoiceNumber() const {
    std::stringstream ss;
    ss << "INV-" << std::setfill('0') << std::setw(6) << invoiceId;
    return ss.str();
}

bool Invoice::isOverdue(const std::string& currentDate) const {
    if (isPaid) {
        return false;
    }

    return currentDate > dueDate;
}
