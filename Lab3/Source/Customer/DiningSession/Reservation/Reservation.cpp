#include "Reservation.h"
#include <chrono>

Reservation::Reservation(int id, const Customer* customer, int tableId,
                         const std::chrono::system_clock::time_point& time, int duration)
        : reservationId(id), customer(customer), tableId(tableId),
          reservationTime(time), durationMinutes(duration) {}

bool Reservation::isActive(const std::chrono::system_clock::time_point& currentTime) const {
    using namespace std::chrono;
    if(durationMinutes <= 0)
        return false;

    auto endTime = reservationTime + minutes(durationMinutes);
    return currentTime >= reservationTime && currentTime <= endTime;
}

bool Reservation::isForTable(int id) const {
    return tableId == id;
}

bool Reservation::isForCustomer(int id) const {
    if(customer)
        return customer->getId() == id;
    return false;
}

void Reservation::extendDuration(int additionalMinutes) {
    if (additionalMinutes > 0) {
        durationMinutes += additionalMinutes;
    }
}

bool Reservation::conflictsWith(const Reservation& other) const {
    if (tableId != other.tableId) return false;

    auto thisStart = reservationTime;
    auto thisEnd = reservationTime + std::chrono::minutes(durationMinutes);
    auto otherStart = other.reservationTime;
    auto otherEnd = other.reservationTime + std::chrono::minutes(other.durationMinutes);

    return !(thisEnd <= otherStart || thisStart >= otherEnd);
}