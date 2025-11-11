#include "../../Source/Menu/Menu.h"
#include "../../Source/Menu/MenuItem/MenuItem.h"
#include "../../Source/Menu/MenuItem/AllergenInfo/AllergenInfo.h"
#include <UnitTest++.h>

SUITE(MenuTest) {
    TEST (TestMenuCreation) {
        Menu menu("Lunch Menu", 10);

                CHECK_EQUAL("Lunch Menu", menu.getName());
                CHECK(menu.getAvailableItems().empty());
                CHECK_EQUAL(0.0, menu.getAveragePrice());
    }

    TEST (TestAddItem) {
        Menu menu("Dinner Menu", 2);
        MenuItem item1("Pasta", 12.99, true);
        MenuItem item2("Pizza", 15.99, true);
        MenuItem item3("Salad", 8.99, false);

                CHECK(menu.addItem(item1));
                CHECK(menu.addItem(item2));

                CHECK(!menu.addItem(item3));

        auto names = menu.getItemNames();
                CHECK_EQUAL(2, names.size());
                CHECK(std::find(names.begin(), names.end(), "Pasta") != names.end());
                CHECK(std::find(names.begin(), names.end(), "Pizza") != names.end());
    }

    TEST (TestRemoveItem) {
        Menu menu("Breakfast Menu");
        MenuItem item1("Pancakes", 9.99, true);
        MenuItem item2("Omelette", 11.99, true);

        menu.addItem(item1);
        menu.addItem(item2);

                CHECK(menu.removeItem("Pancakes"));

                CHECK(!menu.removeItem("Nonexistent"));

        auto names = menu.getItemNames();
                CHECK_EQUAL(1, names.size());
                CHECK(std::find(names.begin(), names.end(), "Omelette") != names.end());
    }

    TEST (TestGetAvailableItems) {
        Menu menu("Dessert Menu");
        MenuItem item1("Cake", 7.99, true);
        MenuItem item2("Ice Cream", 5.99, false);
        MenuItem item3("Pie", 6.99, true);

        menu.addItem(item1);
        menu.addItem(item2);
        menu.addItem(item3);

        auto availableItems = menu.getAvailableItems();
                CHECK_EQUAL(2, availableItems.size());

        std::vector<std::string> availableNames;
        for (const auto &item: availableItems) {
            availableNames.push_back(item.getName());
        }

                CHECK(std::find(availableNames.begin(), availableNames.end(), "Cake") != availableNames.end());
                CHECK(std::find(availableNames.begin(), availableNames.end(), "Pie") != availableNames.end());
    }

    TEST (TestGetAveragePrice) {
        Menu menu("Drinks Menu");

                CHECK_EQUAL(0.0, menu.getAveragePrice());

        menu.addItem(MenuItem("Coffee", 3.50, true));
        menu.addItem(MenuItem("Tea", 2.50, true));
        menu.addItem(MenuItem("Juice", 4.00, true));

        double expectedAverage = (3.50 + 2.50 + 4.00) / 3.0;
                CHECK_CLOSE(expectedAverage, menu.getAveragePrice(), 0.001);

        menu.addItem(MenuItem("Smoothie", 5.50, false));
        expectedAverage = (3.50 + 2.50 + 4.00 + 5.50) / 4.0;
                CHECK_CLOSE(expectedAverage, menu.getAveragePrice(), 0.001);
    }

    TEST (TestApplyGlobalDiscount) {
        Menu menu("Special Menu");
        menu.addItem(MenuItem("Burger", 10.0, true));
        menu.addItem(MenuItem("Fries", 5.0, true));

        menu.applyGlobalDiscount(10.0);

        auto items = menu.getAvailableItems();
                CHECK_CLOSE(9.0, items[0].getPrice(), 0.001);
                CHECK_CLOSE(4.5, items[1].getPrice(), 0.001);

        menu.applyGlobalDiscount(-20.0);
                CHECK_CLOSE(9.0, items[0].getPrice(), 0.001);
        menu.applyGlobalDiscount(150.0);
                CHECK_CLOSE(9.0, items[0].getPrice(), 0.001);
    }

    TEST (TestEdgeCases) {
        Menu emptyMenu("Empty Menu", 0);
                CHECK(emptyMenu.addItem(MenuItem("Item", 1.0, true)));
        Menu defaultMenu("Default Menu", -5);
        for (int i = 0; i < 50; i++) {
                    CHECK(defaultMenu.addItem(MenuItem("Item" + std::to_string(i), i + 1.0, true)));
        }
                CHECK(!defaultMenu.addItem(MenuItem("Extra", 51.0, true)));
        Menu testMenu("Test Menu");
                CHECK(!testMenu.removeItem("Nonexistent"));

        MenuItem emptyNameItem("", 0.0, true);
        bool addResult = testMenu.addItem(emptyNameItem);
        if (addResult) {
                    CHECK(testMenu.removeItem(""));
        } else {
                    CHECK(true);
        }

    }
}