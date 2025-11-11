#include "UnitTest++.h"
#include "Source/Employee/Bartender/Bartender.h"
#include "Source/Menu/MenuItem/Drink/Drink.h"
#include <memory>

SUITE(BartenderTest) {
    TEST(ConstructorAndGetters) {
        Bartender bartender("John Doe", 20.0, 3);
        bartender.setYearsOfExperience(3);

                CHECK_EQUAL("John Doe", bartender.getName());
                CHECK_EQUAL(20.0, bartender.getHourlyRate());
                CHECK_EQUAL(3, bartender.getYearsOfExperience());
                CHECK_EQUAL("Bartender", bartender.getRole());
                CHECK(bartender.getIsActive());
    }

    TEST(AddAndCheckCocktails) {
        Bartender bartender("Jane Smith", 18.0, 2);

                CHECK(!bartender.canPrepare("Mojito"));

        bartender.addCocktailToRepertoire("Mojito");
                CHECK(bartender.canPrepare("Mojito"));

        bartender.addCocktailToRepertoire("Mojito");
                CHECK(bartender.canPrepare("Mojito"));
    }

    TEST(PrepareDrink) {
        Bartender bartender("Alice Brown", 22.0, 5);
        bartender.addCocktailToRepertoire("Mojito");

        auto drink = bartender.prepareDrink("Mojito", 0.3, true);
                CHECK(drink != nullptr);
                CHECK_EQUAL("Mojito", drink->getName());
                CHECK_EQUAL(0.3, drink->getVolume());
                CHECK(drink->getIsAlcoholic());

        auto unknownDrink = bartender.prepareDrink("Unknown", 0.3, false);
                CHECK(unknownDrink == nullptr);
    }

    TEST(ReceiveTips) {
        Bartender bartender("Bob Wilson", 19.0, 1);

        bartender.receiveTip(5.0);
        bartender.receiveTip(3.5);
        bartender.receiveTip(-2.0);

        bartender.addCocktailToRepertoire("Cola");
        auto drink = bartender.prepareDrink("Cola", 0.5, false);
                CHECK(drink != nullptr);
    }

    TEST(Certification) {
        Bartender certifiedBartender("Certified", 25.0, 2);
        Bartender uncertifiedBartender("Uncertified", 15.0, 0);

        certifiedBartender.setYearsOfExperience(2);
        uncertifiedBartender.setYearsOfExperience(0);

                CHECK(certifiedBartender.getYearsOfExperience() >= 1);
                CHECK(uncertifiedBartender.getYearsOfExperience() < 1);
    }

    TEST(EdgeCases) {
        Bartender emptyName("", 10.0, 1);
                CHECK(emptyName.getName().empty());

        Bartender zeroRate("Zero Rate", 0.0, 1);
                CHECK_EQUAL(0.0, zeroRate.getHourlyRate());

        Bartender negativeExp("Negative", 15.0, -1);
        negativeExp.setYearsOfExperience(-1);
                CHECK_EQUAL(0, negativeExp.getYearsOfExperience());
    }
}