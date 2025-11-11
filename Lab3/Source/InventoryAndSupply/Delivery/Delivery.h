#ifndef LAB3_DELIVERY_H
#define LAB3_DELIVERY_H

#include "../PurchaseOrder/PurchaseOrder.h"
#include <string>

class Delivery {
    std::string deliveryId;
    std::string orderId;
    std::string deliveryDate;
    std::string status;
    std::string deliveryPerson;

public:
    Delivery(const std::string& deliveryId, const std::string& orderId,
             const std::string& deliveryDate, const std::string& deliveryPerson);

    void updateStatus(const std::string& newStatus);
    void changeDeliveryPerson(const std::string& newPerson);
    bool isDelivered() const;
    void processDelivery();

    std::string getDeliveryId() const;
    std::string getOrderId() const;
    std::string getDeliveryDate() const;
    std::string getStatus() const;
    std::string getDeliveryPerson() const;
};

#endif //LAB3_DELIVERY_H
