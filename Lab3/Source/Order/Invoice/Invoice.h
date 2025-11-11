#ifndef LAB3_INVOICE_H
#define LAB3_INVOICE_H

#include <string>
#include <vector>
#include "../Order.h"

class Invoice {
private:
    int invoiceId;
    Order* order;
    std::string issueDate;
    std::string dueDate;
    bool isPaid;

public:
    Invoice(int id, Order* order, const std::string& issueDate, const std::string& dueDate);

    int getInvoiceId() const;
    Order* getOrder() const;
    std::string getIssueDate() const;
    std::string getDueDate() const;
    bool getIsPaid() const;

    void updateDueDate(const std::string& newDueDate);
    void markAsPaid();
    double calculateTotal() const;
    std::string generateInvoiceNumber() const;
    bool isOverdue(const std::string& currentDate) const;
};

#endif //LAB3_INVOICE_H
