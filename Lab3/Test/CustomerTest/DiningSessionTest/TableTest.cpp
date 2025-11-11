#include "../../../Source/Customer/DiningSession/Table/Table.h"
#include "UnitTest++.h"

SUITE(TableTest) {
    TEST(TestConstructor) {
        Table table(1, 4, "Window");
                CHECK(table.isAvailable());
    }

    TEST(TestCanAccommodate) {
        Table table(2, 4, "Window");

                CHECK(table.canAccommodate(3));
                CHECK(table.canAccommodate(4));
                CHECK(!table.canAccommodate(5));

        table.occupy();
                CHECK(!table.canAccommodate(1));
                CHECK(!table.canAccommodate(4));
    }

    TEST(TestOccupyAndVacate) {
        Table table(3, 4, "Center");

                CHECK(table.isAvailable());
        table.occupy();
                CHECK(!table.isAvailable());
        table.vacate();
                CHECK(table.isAvailable());
    }

    TEST(TestIsSuitableForGroup) {
        Table table(4, 4, "Terrace");

                CHECK(table.isSuitableForGroup(2));
                CHECK(table.isSuitableForGroup(3));
                CHECK(table.isSuitableForGroup(4));
                CHECK(table.isSuitableForGroup(5));
                CHECK(!table.isSuitableForGroup(1));
                CHECK(!table.isSuitableForGroup(6));

        table.occupy();
                CHECK(!table.isSuitableForGroup(2));
                CHECK(!table.isSuitableForGroup(4));
    }

    TEST(TestEdgeCases) {
        Table table(5, 4, "Bar");

                CHECK(!table.isSuitableForGroup(0));
                CHECK(!table.isSuitableForGroup(-1));

        Table largeTable(6, 10, "Private");
                CHECK(largeTable.isSuitableForGroup(9));
                CHECK(largeTable.isSuitableForGroup(10));
                CHECK(largeTable.isSuitableForGroup(11));
                CHECK(!largeTable.isSuitableForGroup(12));
                CHECK(largeTable.isSuitableForGroup(8));
                CHECK(!largeTable.isSuitableForGroup(13));
    }

    TEST(TestMultipleOperations) {
        Table table(7, 4, "Outdoor");

                CHECK(table.isAvailable());
                CHECK(table.canAccommodate(4));
                CHECK(table.isSuitableForGroup(4));

        table.occupy();
                CHECK(!table.isAvailable());
                CHECK(!table.canAccommodate(4));
                CHECK(!table.isSuitableForGroup(4));

        table.vacate();
                CHECK(table.isAvailable());
                CHECK(table.canAccommodate(4));
                CHECK(table.isSuitableForGroup(4));
    }

    TEST(TestBoundaryConditions) {
        Table table(8, 1, "VIP");

                CHECK(table.canAccommodate(1));
                CHECK(!table.canAccommodate(2));

                CHECK(table.isSuitableForGroup(1));
                CHECK(table.isSuitableForGroup(2));

        Table zeroCapacityTable(9, 0, "Corner");
                CHECK(zeroCapacityTable.canAccommodate(0));
                CHECK(!zeroCapacityTable.canAccommodate(1));
                CHECK(zeroCapacityTable.isSuitableForGroup(0));
                CHECK(zeroCapacityTable.isSuitableForGroup(1));
    }
}