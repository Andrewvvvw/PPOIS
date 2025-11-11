#include "UnitTest++.h"
#include "Source/Employee/Chef/Chef.h"
#include "Source/Menu/MenuItem/MenuItem.h"
#include <memory>

SUITE(ChefTest) {
    TEST(ConstructorAndGetters) {
        Chef chef("John Doe", 30.0, 5);
        chef.setYearsOfExperience(5);

                CHECK_EQUAL("John Doe", chef.getName());
                CHECK_EQUAL(30.0, chef.getHourlyRate());
                CHECK_EQUAL(5, chef.getYearsOfExperience());
                CHECK_EQUAL("Chef", chef.getRole());
                CHECK(chef.getIsActive());
    }

    TEST(AddAndCheckSpecialties) {
        Chef chef("Jane Smith", 25.0, 3);

                CHECK(!chef.canPrepare("Pasta Carbonara"));

        chef.addSpecialty("Pasta Carbonara");
                CHECK(chef.canPrepare("Pasta Carbonara"));

        chef.addSpecialty("Pasta Carbonara");
                CHECK(chef.canPrepare("Pasta Carbonara"));
    }

    TEST(PrepareDish) {
        Chef chef("Alice Brown", 35.0, 7);
        chef.addSpecialty("Beef Wellington");

        auto dish = chef.prepareDish("Beef Wellington", 45.0, true);
                CHECK(dish != nullptr);
                CHECK_EQUAL("Beef Wellington", dish->getName());
                CHECK_EQUAL(45.0, dish->getPrice());
                CHECK(dish->getIsAvailable());

        auto unknownDish = chef.prepareDish("Unknown Dish", 20.0, false);
                CHECK(unknownDish == nullptr);
    }

    TEST(UpgradeKnifeSet) {
        Chef chef("Bob Wilson", 28.0, 1);

        chef.upgradeKnifeSet();

        auto dish = chef.prepareDish("Steak", 35.0, true);
                CHECK(dish == nullptr);
    }

    TEST(KnifeSetExperienceBased) {
        Chef experiencedChef("Experienced", 40.0, 3);
        Chef newChef("New Chef", 25.0, 1);

        experiencedChef.setYearsOfExperience(3);
        newChef.setYearsOfExperience(1);

                CHECK(experiencedChef.getYearsOfExperience() >= 2);
                CHECK(newChef.getYearsOfExperience() < 2);
    }

    TEST(EdgeCases) {
        Chef emptyName("", 10.0, 2);
                CHECK(emptyName.getName().empty());

        Chef zeroRate("Zero Rate", 0.0, 2);
                CHECK_EQUAL(0.0, zeroRate.getHourlyRate());

        Chef negativeExp("Negative", 20.0, -1);
        negativeExp.setYearsOfExperience(-1);
                CHECK_EQUAL(0, negativeExp.getYearsOfExperience());
    }
}