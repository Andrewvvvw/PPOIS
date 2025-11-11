#include "DeliveryPerson.h"

DeliveryPerson::DeliveryPerson(const std::string& name, double hourlyRate, const std::string& vehicle, int maxDistance)
        : Employee(name, "Delivery Person", hourlyRate),
          vehicleType(vehicle),
          maxDeliveryDistance(maxDistance),
          deliveriesCompleted(0) {}

void DeliveryPerson::completeDelivery(const std::string& address) {
    if (canDeliverTo(address)) {
        deliveriesCompleted++;
    }
}

void DeliveryPerson::addDeliveryArea(const std::string& area) {
    if (!canDeliverTo(area)) {
        deliveryAreas.push_back(area);
    }
}

bool DeliveryPerson::canDeliverTo(const std::string& area) const {
    return std::find(deliveryAreas.begin(), deliveryAreas.end(), area) != deliveryAreas.end();
}

void DeliveryPerson::updateVehicle(const std::string& newVehicle, int newMaxDistance) {
    vehicleType = newVehicle;
    maxDeliveryDistance = newMaxDistance;
}

std::string DeliveryPerson::getRole() const {
    return "Delivery Person";
}