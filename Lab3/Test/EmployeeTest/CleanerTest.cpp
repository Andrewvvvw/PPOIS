#include "UnitTest++.h"
#include "Source/Employee/Cleaner/Cleaner.h"
#include <vector>
#include <string>

SUITE(CleanerTest) {
    TEST(ConstructorAndGetters) {
        Cleaner cleaner("John Doe", 15.0, 2);
        cleaner.setYearsOfExperience(2);

                CHECK_EQUAL("John Doe", cleaner.getName());
                CHECK_EQUAL(15.0, cleaner.getHourlyRate());
                CHECK_EQUAL(2, cleaner.getYearsOfExperience());
                CHECK_EQUAL("Cleaner", cleaner.getRole());
                CHECK(cleaner.getIsActive());
    }

    TEST(AddAndCheckCleaningAreas) {
        Cleaner cleaner("Jane Smith", 12.0, 1);

                CHECK(!cleaner.isAreaInCharge("Kitchen"));

        cleaner.addCleaningArea("Kitchen");
                CHECK(cleaner.isAreaInCharge("Kitchen"));

        cleaner.addCleaningArea("Kitchen");
                CHECK(cleaner.isAreaInCharge("Kitchen"));
    }

    TEST(CleanArea) {
        Cleaner cleaner("Alice Brown", 13.0, 3);
        cleaner.addCleaningArea("Dining Area");

        cleaner.cleanArea("Dining Area");

        cleaner.cleanArea("Non-existent Area");
    }

    TEST(RestockSupplies) {
        Cleaner cleaner("Bob Wilson", 14.0, 2);

        cleaner.restockSupplies();

        cleaner.cleanArea("Restroom");
    }

    TEST(EdgeCases) {
        Cleaner emptyName("", 10.0, 1);
                CHECK(emptyName.getName().empty());

        Cleaner zeroRate("Zero Rate", 0.0, 1);
                CHECK_EQUAL(0.0, zeroRate.getHourlyRate());

        Cleaner negativeExp("Negative", 12.0, -1);
        negativeExp.setYearsOfExperience(-1);
                CHECK_EQUAL(0, negativeExp.getYearsOfExperience());
    }

    TEST(MultipleCleaningAreas) {
        Cleaner cleaner("Multi-Area Cleaner", 16.0, 5);

        std::vector<std::string> areas = {"Kitchen", "Dining Area", "Restroom", "Entrance"};

        for (const auto& area : areas) {
            cleaner.addCleaningArea(area);
                    CHECK(cleaner.isAreaInCharge(area));
        }

        cleaner.cleanArea("Kitchen");
        cleaner.cleanArea("Restroom");
    }
}