#include "UnitTest++.h"
#include "../../Source/Marketing/Event/Event.h"
#include "../../Source/Employee/Manager/Manager.h"

TEST(Event_Constructor) {
    Event event("Tech Conference", "2023-12-15", 100, 99.99, 8);

            CHECK_EQUAL("Tech Conference", event.getName());
            CHECK_EQUAL("2023-12-15", event.getDate());
            CHECK_EQUAL(100, event.getMaxAttendees());
            CHECK_EQUAL(99.99, event.getTicketPrice());
            CHECK_EQUAL(8, event.getDurationHours());
            CHECK(event.getIsScheduled());
}

TEST(Event_AssignStaff) {
    Event event("Concert", "2023-12-20", 500, 149.99, 4);
    Manager* employee1 = new Manager("John Doe", "Manager", 25.0, "Operations", 5);
    Manager* employee2 = new Manager("Jane Smith", "Coordinator", 20.0, "HR", 3);
    Manager* employee3 = new Manager("Bob Johnson", "Technician", 22.0, "IT", 4);
    Manager* employee4 = new Manager("Alice Brown", "Staff", 18.0, "Logistics", 2);
    Manager* employee5 = new Manager("Charlie Davis", "Security", 19.0, "Security", 6);
    Manager* employee6 = new Manager("Eve Wilson", "Catering", 17.0, "Catering", 3);

            CHECK(event.assignStaff(employee1));
            CHECK(event.assignStaff(employee2));
            CHECK(event.assignStaff(employee3));
            CHECK(event.assignStaff(employee4));
            CHECK(event.assignStaff(employee5));

            CHECK(!event.assignStaff(employee6));
            CHECK(!event.assignStaff(nullptr));

    delete employee1;
    delete employee2;
    delete employee3;
    delete employee4;
    delete employee5;
    delete employee6;
}

TEST(Event_CancelEvent) {
    Event event("Workshop", "2023-12-10", 30, 49.99, 2);
    Manager* employee = new Manager("John Doe", "Instructor", 30.0, "Training", 1);

    event.assignStaff(employee);
            CHECK(event.getIsScheduled());

            CHECK(event.cancelEvent());
            CHECK(!event.getIsScheduled());

            CHECK(!event.cancelEvent());

    delete employee;
}

TEST(Event_CalculateExpectedRevenue) {
    Event event1("Concert", "2023-12-25", 1000, 199.99, 3);
            CHECK_EQUAL(199990.0, event1.calculateExpectedRevenue());

    Event event2("Cancelled Show", "2023-12-24", 500, 99.99, 2);
    event2.cancelEvent();
            CHECK_EQUAL(0.0, event2.calculateExpectedRevenue());
}

TEST(Event_IsEventOnDate) {
    Event event("Exhibition", "2023-12-15", 200, 29.99, 6);

            CHECK(event.isEventOnDate("2023-12-15"));
            CHECK(!event.isEventOnDate("2023-12-16"));

    event.cancelEvent();
            CHECK(!event.isEventOnDate("2023-12-15"));
}

TEST(Event_GetEventDetails) {
    Event event("Product Launch", "2023-12-01", 300, 149.99, 3);
    Manager* employee1 = new Manager("John Doe", "Host", 25.0, "Marketing", 3);
    Manager* employee2 = new Manager("Jane Smith", "Coordinator", 22.0, "Events", 2);

    event.assignStaff(employee1);
    event.assignStaff(employee2);

    auto details = event.getEventDetails();

            CHECK_EQUAL(7, details.size());
            CHECK_EQUAL("Name: Product Launch", details[0]);
            CHECK_EQUAL("Date: 2023-12-01", details[1]);
            CHECK_EQUAL("Duration: 3 hours", details[2]);
            CHECK_EQUAL("Max Attendees: 300", details[3]);
            CHECK(details[4].find("149.99") != std::string::npos);
            CHECK_EQUAL("Status: Scheduled", details[5]);
            CHECK_EQUAL("Staff Assigned: 2", details[6]);

    event.cancelEvent();
    details = event.getEventDetails();
            CHECK_EQUAL("Status: Cancelled", details[5]);

    delete employee1;
    delete employee2;
}

TEST(Event_Getters) {
    Event event("Test Event", "2023-12-31", 50, 9.99, 1);

            CHECK_EQUAL("Test Event", event.getName());
            CHECK_EQUAL("2023-12-31", event.getDate());
            CHECK_EQUAL(50, event.getMaxAttendees());
            CHECK_EQUAL(9.99, event.getTicketPrice());
            CHECK_EQUAL(1, event.getDurationHours());
            CHECK(event.getIsScheduled());
}