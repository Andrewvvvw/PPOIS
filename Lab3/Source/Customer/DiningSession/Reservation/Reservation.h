#ifndef LAB3_RESERVATION_H
#define LAB3_RESERVATION_H

#include <string>
#include <chrono>
#include "../../Customer.h"

class Reservation {
    int reservationId;
    const Customer* customer;
    int tableId;
    std::chrono::system_clock::time_point reservationTime;
    int durationMinutes;

public:
    Reservation(int id, const Customer* customer, int tableId,
               const std::chrono::system_clock::time_point& time, int duration);

    bool isActive(const std::chrono::system_clock::time_point& currentTime) const;
    bool isForTable(int tableId) const;
    bool isForCustomer(int customerId) const;
    void extendDuration(int additionalMinutes);
    bool conflictsWith(const Reservation& other) const;
};

#endif //LAB3_RESERVATION_H
