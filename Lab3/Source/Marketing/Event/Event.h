#ifndef LAB3_EVENT_H
#define LAB3_EVENT_H

#include <string>
#include <vector>
#include "../../Employee/Employee.h"

class Event {
private:
    std::string name;
    std::string date;
    int maxAttendees;
    double ticketPrice;
    std::vector <const Employee*> assignedStaff;
    bool isScheduled;
    int durationHours;

public:
    Event(const std::string& name, const std::string& date, int maxAttendees, double ticketPrice, int durationHours);

    bool assignStaff(const Employee* employee);
    bool cancelEvent();
    double calculateExpectedRevenue() const;
    bool isEventOnDate(const std::string& checkDate) const;
    std::vector<std::string> getEventDetails() const;

    std::string getName() const;
    std::string getDate() const;
    int getMaxAttendees() const;
    double getTicketPrice() const;
    bool getIsScheduled() const;
    int getDurationHours() const;
};

#endif //LAB3_EVENT_H
