#include "UnitTest++.h"
#include "Source/Employee/SousChef/SousChef.h"

SUITE(SousChefTest) {
    TEST(ConstructorAndGetters) {
        SousChef chef("John Doe", 25.0, 3);

                CHECK_EQUAL("John Doe", chef.getName());
                CHECK_EQUAL("Sous Chef", chef.getRole());
                CHECK_EQUAL(25.0, chef.getHourlyRate());
                CHECK_EQUAL(3, chef.getYearsOfExperience());
                CHECK(chef.getIsActive());
                CHECK(!chef.isStationAssigned("Grill"));
    }

    TEST(StationAssignment) {
        SousChef chef("Jane Smith", 22.0, 2);

        chef.assignStation("Grill");
                CHECK(chef.isStationAssigned("Grill"));

        chef.assignStation("Grill");

        chef.assignStation("Sauce");
                CHECK(chef.isStationAssigned("Sauce"));

                CHECK(!chef.isStationAssigned("Fryer"));
    }

    TEST(DishPreparation) {
        SousChef chef("Bob Johnson", 20.0, 1);

        chef.completeDish();
        chef.certify();
                CHECK(chef.getRole() == "Sous Chef");

        for (int i = 1; i <= 5; i++) {
            chef.completeDish();
        }
    }

    TEST(Certification) {
        SousChef chef("Alice Brown", 23.0, 4);

                CHECK(!chef.getIsCertified());

        chef.certify();
                CHECK(chef.getIsCertified());

        chef.completeDish();
    }

    TEST(EdgeCases) {
        SousChef minChef("", 0.0, 0);
                CHECK_EQUAL("", minChef.getName());
                CHECK_EQUAL(0.0, minChef.getHourlyRate());
                CHECK_EQUAL(0, minChef.getYearsOfExperience());

        SousChef maxChef("A very long name that exceeds any reasonable limit for a name field",
                         1000.0,
                         50);
                CHECK(maxChef.getName().length() > 0);

        maxChef.assignStation("");
                CHECK(maxChef.isStationAssigned(""));
    }
}