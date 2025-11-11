#include "Event.h"

Event::Event(const std::string& name, const std::string& date, int maxAttendees, double ticketPrice, int durationHours)
    : name(name), date(date), maxAttendees(maxAttendees), ticketPrice(ticketPrice), durationHours(durationHours) {
    isScheduled = true;
}

bool Event::assignStaff(const Employee* employee) {
    if (!employee || assignedStaff.size() >= 5) {
        return false;
    }
    assignedStaff.push_back(employee);
    return true;
}

bool Event::cancelEvent() {
    if (!isScheduled) {
        return false;
    }
    isScheduled = false;
    assignedStaff.clear();
    return true;
}

double Event::calculateExpectedRevenue() const {
    return isScheduled ? maxAttendees * ticketPrice : 0.0;
}

bool Event::isEventOnDate(const std::string& checkDate) const {
    return date == checkDate && isScheduled;
}

std::vector<std::string> Event::getEventDetails() const {
    return {
        "Name: " + name,
        "Date: " + date,
        "Duration: " + std::to_string(durationHours) + " hours",
        "Max Attendees: " + std::to_string(maxAttendees),
        "Ticket Price: " + std::to_string(ticketPrice),
        "Status: " + std::string(isScheduled ? "Scheduled" : "Cancelled"),
        "Staff Assigned: " + std::to_string(assignedStaff.size())
    };
}

std::string Event::getName() const {
    return name;
}
std::string Event::getDate() const {
    return date;
}
int Event::getMaxAttendees() const {
    return maxAttendees;
}
double Event::getTicketPrice() const {
    return ticketPrice;
}
bool Event::getIsScheduled() const {
    return isScheduled;
}
int Event::getDurationHours() const {
    return durationHours;
}
