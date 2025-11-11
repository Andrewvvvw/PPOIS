#ifndef LAB3_DININGSESSION_H
#define LAB3_DININGSESSION_H

#include <vector>
#include <chrono>
#include "../Customer.h"
#include "Table/Table.h"

class DiningSession {
    int sessionId;
    const Table* table;
    std::vector<const Customer*> customers;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

public:
    DiningSession(int id, const Table* table, const Customer* customer);

    void addCustomer(const Customer* customer);
    void removeCustomer(int customerId);
    void endSession();
    double calculateSessionDuration() const;
    bool isActive() const;
};

#endif //LAB3_DININGSESSION_H
