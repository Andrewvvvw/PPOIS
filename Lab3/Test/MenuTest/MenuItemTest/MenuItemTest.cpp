#include "../../../Source/Menu/MenuItem/MenuItem.h"
#include "../../../Source/Menu/MenuItem/AllergenInfo/AllergenInfo.h"
#include <UnitTest++.h>

SUITE(MenuItemTest) {
    TEST(TestMenuItemCreation) {
        MenuItem item("Pasta", 12.99, true);

        CHECK_EQUAL("Pasta", item.getName());
        CHECK_EQUAL(12.99, item.getPrice());
        CHECK(item.getIsAvailable());
        CHECK(item.getAllergens().empty());
    }

    TEST(TestPriceManagement) {
        MenuItem item("Pizza", 15.99);

        CHECK_EQUAL(15.99, item.getPrice());

        item.setPrice(17.99);
        CHECK_EQUAL(17.99, item.getPrice());

        CHECK(item.isPriceAboveAverage(15.0));
        CHECK(!item.isPriceAboveAverage(20.0));

        item.applyDiscount(10.0);
        CHECK_CLOSE(16.191, item.getPrice(), 0.001);
    }

    TEST(TestAvailability) {
        MenuItem item("Salad", 8.99, true);

        CHECK(item.getIsAvailable());

        item.setIsAvailable(false);
        CHECK(!item.getIsAvailable());

        item.setIsAvailable(true);
        CHECK(item.getIsAvailable());
    }

    TEST(TestAllergenManagement) {
        MenuItem item("Burger", 10.99);
        AllergenInfo gluten("Gluten", "Found in wheat, barley, rye", AllergenSeverity::HIGH, true);
        AllergenInfo dairy("Dairy", "Milk products", AllergenSeverity::MEDIUM, true);

        item.addAllergen(gluten);
        item.addAllergen(dairy);

        CHECK(item.containsAllergen("Gluten"));
        CHECK(item.containsAllergen("Dairy"));
        CHECK_EQUAL(2, item.getAllergens().size());

        CHECK(item.removeAllergen("Gluten"));
        CHECK(!item.containsAllergen("Gluten"));
        CHECK_EQUAL(1, item.getAllergens().size());

        CHECK(!item.removeAllergen("Nonexistent"));
    }

    TEST(TestSevereAllergens) {
        MenuItem item1("Mild Dish", 9.99);
        MenuItem item2("Severe Dish", 12.99);

        AllergenInfo mild("Mild", "Not severe", AllergenSeverity::LOW, false);
        AllergenInfo severe("Severe", "Very dangerous", AllergenSeverity::HIGH, true);

        item1.addAllergen(mild);
        item2.addAllergen(severe);

        CHECK(!item1.hasSevereAllergens());
        CHECK(item2.hasSevereAllergens());
    }

    TEST(TestEdgeCases) {
        MenuItem emptyName("", 5.99);
                CHECK(emptyName.getName().empty());

        MenuItem freeItem("Free Sample", 0.0);
                CHECK_EQUAL(0.0, freeItem.getPrice());

        freeItem.setPrice(-5.0);
                CHECK_EQUAL(0.0, freeItem.getPrice());
        freeItem.setPrice(10.0);
        freeItem.applyDiscount(150.0);
                CHECK_EQUAL(10.0, freeItem.getPrice());
        freeItem.setPrice(10.0);
        freeItem.applyDiscount(-50.0);
                CHECK_EQUAL(10.0, freeItem.getPrice());

        freeItem.setPrice(10.0);
        freeItem.applyDiscount(100.0);
                CHECK_EQUAL(0.0, freeItem.getPrice());
    }

    TEST(TestMultipleAllergens) {
        MenuItem item("Complex Dish", 25.99);

        for (int i = 0; i < 100; i++) {
            AllergenInfo allergen("Allergen_" + std::to_string(i),
                                "Description " + std::to_string(i),
                                (i % 3 == 0) ? AllergenSeverity::HIGH :
                                (i % 3 == 1) ? AllergenSeverity::MEDIUM :
                                AllergenSeverity::LOW,
                                i % 2 == 0);
            item.addAllergen(allergen);
        }

        CHECK_EQUAL(100, item.getAllergens().size());

        CHECK(item.containsAllergen("Allergen_0"));
        CHECK(item.containsAllergen("Allergen_50"));
        CHECK(item.containsAllergen("Allergen_99"));
        CHECK(item.hasSevereAllergens());

        for (int i = 0; i < 100; i++) {
            item.removeAllergen("Allergen_" + std::to_string(i));
        }

        CHECK(item.getAllergens().empty());
        CHECK(!item.hasSevereAllergens());
    }
}
