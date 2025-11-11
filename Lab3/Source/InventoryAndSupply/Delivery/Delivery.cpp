#include "Delivery.h"

Delivery::Delivery(const std::string& deliveryId, const std::string& orderId,
                 const std::string& deliveryDate, const std::string& deliveryPerson)
    : deliveryId(deliveryId), orderId(orderId), deliveryDate(deliveryDate),
      status("Scheduled"), deliveryPerson(deliveryPerson) {}

void Delivery::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

void Delivery::changeDeliveryPerson(const std::string& newPerson) {
    deliveryPerson = newPerson;
}

bool Delivery::isDelivered() const {
    return status == "Delivered";
}

void Delivery::processDelivery() {
    status = "In Transit";
}

std::string Delivery::getDeliveryId() const {
    return deliveryId;
}

std::string Delivery::getOrderId() const {
    return orderId;
}

std::string Delivery::getDeliveryDate() const {
    return deliveryDate;
}

std::string Delivery::getStatus() const {
    return status;
}

std::string Delivery::getDeliveryPerson() const {
    return deliveryPerson;
}
