#include "DiningSession.h"
#include <algorithm>

DiningSession::DiningSession(int id, const Table* table, const Customer* customer)
    : sessionId(id), table(table), startTime(std::chrono::system_clock::now()) {
    customers.push_back(customer);
}

void DiningSession::addCustomer(const Customer* customer) {
    if (std::find(customers.begin(), customers.end(), customer) == customers.end()) {
        customers.push_back(customer);
    }
}

void DiningSession::removeCustomer(int customerId) {
    customers.erase(
        std::remove_if(customers.begin(), customers.end(),
                      [customerId](const Customer* c) {
                          return c->getId() == customerId;
                      }),
        customers.end()
    );
}

void DiningSession::endSession() {
    endTime = std::chrono::system_clock::now();
}

double DiningSession::calculateSessionDuration() const {
    using namespace std::chrono;
    auto end = endTime.time_since_epoch() != time_point<system_clock>::duration() ?
               endTime : system_clock::now();
    return duration_cast<duration<double>>(end - startTime).count() / 60.0;
}

bool DiningSession::isActive() const {
    return endTime.time_since_epoch() == std::chrono::time_point<std::chrono::system_clock>::duration();
}
