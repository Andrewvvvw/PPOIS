#include "UnitTest++.h"
#include "Source/Employee/Host/Host.h"

SUITE(HostTest) {
    TEST(ConstructorAndGetters) {
        Host host("John Doe", 15.0, 5);
        host.setYearsOfExperience(2);

                CHECK_EQUAL("John Doe", host.getName());
                CHECK_EQUAL(15.0, host.getHourlyRate());
                CHECK_EQUAL(2, host.getYearsOfExperience());
                CHECK_EQUAL("Host", host.getRole());
                CHECK(host.getIsActive());
    }

    TEST(AssignAndFreeTables) {
        Host host("Jane Smith", 12.0, 3);

                CHECK_EQUAL(0, host.getAssignedTablesCount());

        host.assignTable(1);
                CHECK(host.isTableAssigned(1));
                CHECK_EQUAL(1, host.getAssignedTablesCount());

        host.freeTable(1);
                CHECK(!host.isTableAssigned(1));
                CHECK_EQUAL(0, host.getAssignedTablesCount());
    }

    TEST(MaxTablesLimit) {
        Host host("Alice Brown", 13.0, 2);

        host.assignTable(1);
        host.assignTable(2);
        host.assignTable(3);

                CHECK_EQUAL(2, host.getAssignedTablesCount());
                CHECK(host.isTableAssigned(1));
                CHECK(host.isTableAssigned(2));
                CHECK(!host.isTableAssigned(3));
    }

    TEST(DuplicateTableAssignment) {
        Host host("Bob Wilson", 14.0, 3);

        host.assignTable(1);
        host.assignTable(1);

                CHECK_EQUAL(1, host.getAssignedTablesCount());
    }

    TEST(FreeNonExistentTable) {
        Host host("Charlie Davis", 16.0, 4);

        host.freeTable(1);
                CHECK_EQUAL(0, host.getAssignedTablesCount());

        host.assignTable(1);
        host.freeTable(2);
                CHECK_EQUAL(1, host.getAssignedTablesCount());
    }

    TEST(EdgeCases) {
        Host zeroMaxTables("Zero Max", 10.0, 0);
        zeroMaxTables.assignTable(1);
                CHECK_EQUAL(1, zeroMaxTables.getAssignedTablesCount());

        Host negativeMaxTables("Negative Max", 10.0, -5);
        negativeMaxTables.assignTable(1);
                CHECK_EQUAL(1, negativeMaxTables.getAssignedTablesCount());

        Host emptyName("", 10.0, 3);
                CHECK(emptyName.getName().empty());
    }

    TEST(GetAssignedTablesCount) {
        Host host("Table Counter", 12.0, 5);

                CHECK_EQUAL(0, host.getAssignedTablesCount());

        host.assignTable(1);
        host.assignTable(2);
                CHECK_EQUAL(2, host.getAssignedTablesCount());

        host.freeTable(1);
                CHECK_EQUAL(1, host.getAssignedTablesCount());
    }
}