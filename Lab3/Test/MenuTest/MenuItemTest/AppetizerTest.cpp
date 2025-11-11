#include "UnitTest++.h"
#include "../../Source/Menu/MenuItem/Appetizer/Appetizer.h"
#include "../../Source/Menu/MenuItem/Recipe/Recipe.h"

using namespace std;

TEST(Appetizer_Constructor) {
    Appetizer app("Bruschetta", 8.99, true, 2, true, 350);

            CHECK_EQUAL("Bruschetta", app.getName());
            CHECK_EQUAL(8.99, app.getPrice());
            CHECK(app.getIsAvailable());
            CHECK_EQUAL(2, app.getSpiceLevel());
            CHECK(app.getIsVegetarian());
            CHECK_EQUAL(350, app.getCalories());
            CHECK(!app.hasRecipe());
}

TEST(Appetizer_RecipeManagement) {
    auto recipe = make_shared<Recipe>(
            "Bruschetta Recipe",
            vector<string>{"Bread", "Tomatoes", "Basil"},
            vector<string>{"Toast bread", "Add toppings"},
            15,
            2
    );

    Appetizer app("Bruschetta", 8.99, true, 2, true, 350);

    app.setRecipe(recipe);
            CHECK(app.hasRecipe());
            CHECK(recipe == app.getRecipe());

    app.setRecipe(nullptr);
            CHECK(!app.hasRecipe());
            CHECK(nullptr == app.getRecipe());
}

TEST(Appetizer_SpiceLevel) {
    Appetizer app("Spicy Wings", 12.99, true, 3, false, 450);

            CHECK_EQUAL(3, app.getSpiceLevel());

    app.increaseSpiceLevel();
            CHECK_EQUAL(4, app.getSpiceLevel());

    app.setSpiceLevel(1);
            CHECK_EQUAL(1, app.getSpiceLevel());

    app.setSpiceLevel(10);
    app.increaseSpiceLevel();
            CHECK_EQUAL(10, app.getSpiceLevel());
}

TEST(Appetizer_Calories) {
    Appetizer lowCal("Salad", 7.99, true, 1, true, 200);
    Appetizer highCal("Nachos", 10.99, true, 2, false, 800);

            CHECK(!lowCal.isHighCalorie(300));
            CHECK(highCal.isHighCalorie(500));

    lowCal.setCalories(400);
            CHECK(lowCal.isHighCalorie(300));
}

TEST(Appetizer_VegetarianStatus) {
    Appetizer veg("Spring Rolls", 6.99, true, 1, true, 300);
    Appetizer nonVeg("Chicken Wings", 11.99, true, 3, false, 650);

            CHECK(veg.getIsVegetarian());
            CHECK(!nonVeg.getIsVegetarian());

    nonVeg.setIsVegetarian(true);
            CHECK(nonVeg.getIsVegetarian());
}

TEST(Appetizer_InheritedFromMenuItem) {
    Appetizer app("Garlic Bread", 5.99, true, 1, true, 320);

    app.setPrice(6.49);
            CHECK_EQUAL(6.49, app.getPrice());

    app.setIsAvailable(false);
            CHECK(!app.getIsAvailable());

    AllergenInfo gluten("Gluten", "Contains gluten", AllergenSeverity::MEDIUM, true);
    app.addAllergen(gluten);
            CHECK(app.containsAllergen("Gluten"));

    app.applyDiscount(10);
            CHECK_CLOSE(5.84, app.getPrice(), 0.01);
}

TEST(Appetizer_EdgeCases) {
    Appetizer minApp("Minimal", 0.01, false, 0, false, 0);
            CHECK_EQUAL(0, minApp.getSpiceLevel());
            CHECK_EQUAL(0, minApp.getCalories());

    Appetizer maxApp("Maxed", 999.99, true, 100, true, 10000);
            CHECK_EQUAL(10, maxApp.getSpiceLevel());
            CHECK_EQUAL(10000, maxApp.getCalories());
}

TEST(Appetizer_CaloriesEdgeCases) {
    Appetizer negativeCal("Negative Cal", 5.99, true, 1, true, -100);
            CHECK_EQUAL(0, negativeCal.getCalories());

    negativeCal.setCalories(-50);
            CHECK_EQUAL(0, negativeCal.getCalories());

    Appetizer highCalApp("High Cal", 9.99, true, 2, false, 1000);
            CHECK(highCalApp.isHighCalorie(500));
            CHECK(!highCalApp.isHighCalorie(1500));
}

TEST(Appetizer_RecipeEdgeCases) {
    auto emptyRecipe = make_shared<Recipe>(
            "",
            vector<string>{},
            vector<string>{"Just mix everything"},
            10,
            1
    );

    Appetizer app("Test App", 7.99, true, 2, true, 300);

    app.setRecipe(emptyRecipe);
            CHECK(app.hasRecipe());
            CHECK_EQUAL("", app.getRecipe()->getName());

    auto newRecipe = make_shared<Recipe>(
            "New Recipe",
            vector<string>{"Ing1", "Ing2"},
            vector<string>{"Step 1", "Step 2"},
            20,
            2
    );

    app.setRecipe(newRecipe);
            CHECK_EQUAL("New Recipe", app.getRecipe()->getName());
}

TEST(Appetizer_SpiceLevelEdgeCases) {
    Appetizer negSpice("Negative Spice", 6.99, true, -5, true, 200);
            CHECK_EQUAL(0, negSpice.getSpiceLevel());

    negSpice.setSpiceLevel(-10);
            CHECK_EQUAL(0, negSpice.getSpiceLevel());

    Appetizer maxSpice("Max Spice", 8.99, true, 10, false, 400);
            CHECK_EQUAL(10, maxSpice.getSpiceLevel());

    maxSpice.increaseSpiceLevel();
            CHECK_EQUAL(10, maxSpice.getSpiceLevel());
}

TEST(Appetizer_PriceAndAvailability) {
    Appetizer priceyApp("Pricey App", 19.99, true, 2, false, 600);

    priceyApp.setPrice(24.99);
            CHECK_EQUAL(24.99, priceyApp.getPrice());

    priceyApp.applyDiscount(20);
            CHECK_CLOSE(19.99, priceyApp.getPrice(), 0.01);
            CHECK(priceyApp.getIsAvailable());
    priceyApp.setIsAvailable(false);
            CHECK(!priceyApp.getIsAvailable());
}

TEST(Appetizer_AllergenManagement) {
    Appetizer allergenApp("Allergen Test", 12.99, true, 2, true, 350);

    AllergenInfo nuts("Nuts", "Contains tree nuts", AllergenSeverity::HIGH, true);
    AllergenInfo dairy("Dairy", "Contains milk products", AllergenSeverity::MEDIUM, true);

    allergenApp.addAllergen(nuts);
            CHECK(allergenApp.containsAllergen("Nuts"));

    allergenApp.addAllergen(dairy);
            CHECK(allergenApp.containsAllergen("Dairy"));

    AllergenInfo nuts2("Nuts", "Another nuts entry", AllergenSeverity::HIGH, true);
    allergenApp.addAllergen(nuts2);

    auto allergens = allergenApp.getAllergens();
            CHECK_EQUAL(2, allergens.size());
}