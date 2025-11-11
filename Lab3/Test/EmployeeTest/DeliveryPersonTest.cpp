#include "UnitTest++.h"
#include "Source/Employee/DeliveryPerson/DeliveryPerson.h"
#include <vector>
#include <string>

SUITE(DeliveryPersonTest) {
    TEST(ConstructorAndGetters) {
        DeliveryPerson dp("John Doe", 18.0, "Bike", 5);
        dp.setYearsOfExperience(2);

                CHECK_EQUAL("John Doe", dp.getName());
                CHECK_EQUAL(18.0, dp.getHourlyRate());
                CHECK_EQUAL(2, dp.getYearsOfExperience());
                CHECK_EQUAL("Delivery Person", dp.getRole());
                CHECK(dp.getIsActive());
    }

    TEST(AddAndCheckDeliveryAreas) {
        DeliveryPerson dp("Jane Smith", 15.0, "Scooter", 10);

                CHECK(!dp.canDeliverTo("Downtown"));

        dp.addDeliveryArea("Downtown");
                CHECK(dp.canDeliverTo("Downtown"));

        dp.addDeliveryArea("Downtown");
                CHECK(dp.canDeliverTo("Downtown"));
    }

    TEST(CompleteDelivery) {
        DeliveryPerson dp("Alice Brown", 16.0, "Car", 20);
        dp.addDeliveryArea("Uptown");

        dp.completeDelivery("Uptown");
        dp.completeDelivery("Unknown Area");
    }

    TEST(UpdateVehicle) {
        DeliveryPerson dp("Bob Wilson", 17.0, "Bike", 5);

        dp.updateVehicle("Motorcycle", 15);

        dp.addDeliveryArea("Suburb");
        dp.completeDelivery("Suburb");
    }

    TEST(EdgeCases) {
        DeliveryPerson emptyName("", 10.0, "Bike", 5);
                CHECK(emptyName.getName().empty());

        DeliveryPerson zeroRate("Zero Rate", 0.0, "Bike", 5);
                CHECK_EQUAL(0.0, zeroRate.getHourlyRate());

        DeliveryPerson negativeExp("Negative", 12.0, "Bike", 5);
        negativeExp.setYearsOfExperience(-1);
                CHECK_EQUAL(0, negativeExp.getYearsOfExperience());
    }

    TEST(MultipleDeliveryAreas) {
        DeliveryPerson dp("Multi-Area Delivery", 20.0, "Car", 30);

        std::vector<std::string> areas = {"North", "South", "East", "West"};

        for (const auto& area : areas) {
            dp.addDeliveryArea(area);
                    CHECK(dp.canDeliverTo(area));
        }

        for (const auto& area : areas) {
            dp.completeDelivery(area);
        }
    }
}