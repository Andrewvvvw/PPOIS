#ifndef LAB3_ORDER_H
#define LAB3_ORDER_H

#include <vector>
#include <string>
#include <memory>
#include "OrderItem/OrderItem.h"
#include "../Customer/Customer.h"
#include "Discount/Discount.h"
#include "BillSplitter/BillSplitter.h"
#include "LoyaltyProgram/LoyaltyProgram.h"

class Order {
private:
    int orderId;
    std::vector<Customer*> customers;
    std::vector<OrderItem> items;
    bool isPaid;
    std::unique_ptr<Discount> discount;
    std::unique_ptr<BillSplitter> billSplitter;
    double serviceCharge;
    LoyaltyProgram loyaltyProgram;

public:
    Order(int id, Customer* customer, double serviceCharge = 0.0);

    int getOrderId() const;
    const std::vector<Customer*>& getCustomers() const;
    bool getPaymentStatus() const;
    double getServiceCharge() const;
    void setServiceCharge(double charge);

    void addCustomer(Customer* customer);
    void removeCustomer(int customerId);
    void addItem(const OrderItem& item, Customer* customer = nullptr);
    void removeItem(int index);
    double calculateTotal() const;
    double calculateSubtotal() const;
    void applyDiscount(std::unique_ptr<Discount> discount);
    void removeDiscount();
    const Discount* getDiscount() const;
    void markAsPaid();

    void splitBillEqually();
    double getCustomerShare(Customer* customer) const;
    std::map<Customer*, double> getIndividualBills() const;

    void applyLoyaltyDiscount(int customerId);
    double getLoyaltyDiscount(int customerId) const;
    std::string getCustomerTier(int customerId) const;
};

#endif //LAB3_ORDER_H
