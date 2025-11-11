#ifndef LAB3_DELIVERYPERSON_H
#define LAB3_DELIVERYPERSON_H

#include "../Employee.h"
#include <vector>
#include <string>
#include <utility>

class DeliveryPerson : public Employee {
private:
    std::vector<std::string> deliveryAreas;
    std::string vehicleType;
    int maxDeliveryDistance;
    int deliveriesCompleted;

public:
    DeliveryPerson(const std::string& name, double hourlyRate, const std::string& vehicle, int maxDistance);

    void completeDelivery(const std::string& address);
    void addDeliveryArea(const std::string& area);
    bool canDeliverTo(const std::string& area) const;
    void updateVehicle(const std::string& newVehicle, int newMaxDistance);

    std::string getRole() const override;
};

#endif //LAB3_DELIVERYPERSON_H