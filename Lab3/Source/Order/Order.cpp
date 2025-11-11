#include "Order.h"
#include <stdexcept>
#include <algorithm>

Order::Order(int id, Customer* customer, double serviceCharge)
    : orderId(id), isPaid(false), serviceCharge(serviceCharge) {
    if (customer) {
        customers.push_back(customer);
    }
    billSplitter = std::make_unique<BillSplitter>(0.0, serviceCharge, 1);
}

int Order::getOrderId() const {
    return orderId;
}

const std::vector<Customer*>& Order::getCustomers() const {
    return customers;
}

bool Order::getPaymentStatus() const {
    return isPaid;
}

double Order::getServiceCharge() const {
    return serviceCharge;
}

void Order::setServiceCharge(double charge) {
    serviceCharge = charge;
    if (billSplitter) {
        billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
    }
}

void Order::addCustomer(Customer* customer) {
    if (!customer) return;
    if (std::find(customers.begin(), customers.end(), customer) == customers.end()) {
        customers.push_back(customer);
        if (billSplitter) {
            billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
        }
    }
}

void Order::removeCustomer(int customerId) {
    auto it = std::find_if(customers.begin(), customers.end(),
        [customerId](const Customer* c) { return c->getId() == customerId; });

    if (it != customers.end()) {
        customers.erase(it);
        if (billSplitter) {
            billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
        }
    }
}

void Order::addItem(const OrderItem& item, Customer* customer) {
    items.push_back(item);
    if (billSplitter && customer) {
        billSplitter->addItem(customer, item.calculateItemTotal());
    } else if (billSplitter) {
        billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
    }
}

void Order::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
        if (billSplitter) {
            billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
        }
    }
}

double Order::calculateSubtotal() const {
    double subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item.calculateItemTotal();
    }
    return subtotal;
}

double Order::calculateTotal() const {
    double total = calculateSubtotal();

    if (discount) {
        total = discount->applyDiscount(total);
    }

    if (serviceCharge > 0) {
        total += total * serviceCharge;
    }

    return total;
}

void Order::applyDiscount(std::unique_ptr<Discount> newDiscount) {
    discount = std::move(newDiscount);
}

void Order::removeDiscount() {
    discount.reset();
}

const Discount* Order::getDiscount() const {
    return discount.get();
}

void Order::splitBillEqually() {
    if (!billSplitter) {
        billSplitter = std::make_unique<BillSplitter>(calculateSubtotal(), serviceCharge, customers.size());
    }
    billSplitter->splitBill(customers);
}

double Order::getCustomerShare(Customer* customer) const {
    if (!billSplitter) {
        return calculateTotal() / (customers.empty() ? 1 : customers.size());
    }
    return billSplitter->getCustomerShare(customer);
}

std::map<Customer*, double> Order::getIndividualBills() const {
    std::map<Customer*, double> result;
    if (!billSplitter) {
        double share = calculateTotal() / (customers.empty() ? 1 : customers.size());
        for (auto* customer : customers) {
            result[customer] = share;
        }
    } else {
        for (auto* customer : customers) {
            result[customer] = billSplitter->getCustomerShare(customer);
        }
    }
    return result;
}

void Order::markAsPaid() {
    isPaid = true;
    double total = calculateTotal();
    for (auto customer : customers) {
        loyaltyProgram.updateCustomerSpending(customer->getId(), total);
    }
}

void Order::applyLoyaltyDiscount(int customerId) {
    bool customerFound = false;
    for (auto* customer : customers) {
        if (customer->getId() == customerId) {
            customerFound = true;
            break;
        }
    }

    if (!customerFound)
        return;

    double orderTotal = calculateSubtotal();
    loyaltyProgram.updateCustomerSpending(customerId, orderTotal);
    double discountRate = loyaltyProgram.calculateDiscount(customerId);

    if (discountRate > 0) {
        double discountAmount = orderTotal * discountRate;
        applyDiscount(std::make_unique<Discount>("LOYALTY", discountAmount, false));
    }
}

double Order::getLoyaltyDiscount(int customerId) const {
    return loyaltyProgram.calculateDiscount(customerId);
}

std::string Order::getCustomerTier(int customerId) const {
    return loyaltyProgram.getTierName(customerId);
}