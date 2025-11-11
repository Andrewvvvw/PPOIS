#include "UnitTest++.h"
#include "../../Source/Menu/MenuItem/Dessert/Dessert.h"
#include "../../Source/Menu/MenuItem/Recipe/Recipe.h"

using namespace std;

TEST(Dessert_Constructor) {
    Dessert dessert("Chocolate Cake", 8.99, false, false, 450, "Chocolate", 8.5f, true);

            CHECK_EQUAL("Chocolate Cake", dessert.getName());
            CHECK_EQUAL(8.99, dessert.getPrice());
            CHECK(!dessert.getIsGlutenFree());
            CHECK(!dessert.getIsVegan());
            CHECK_EQUAL(450, dessert.getCalories());
            CHECK_EQUAL("Chocolate", dessert.getMainIngredient());
            CHECK_EQUAL(8.5f, dessert.getSweetnessLevel());
            CHECK(dessert.getIsAvailable());
            CHECK(!dessert.hasRecipe());
}

TEST(Dessert_RecipeManagement) {
    auto recipe = make_shared<Recipe>(
            "Chocolate Cake Recipe",
            vector<string>{"Flour", "Sugar", "Cocoa", "Eggs"},
            vector<string>{"Mix", "Bake", "Cool"},
            60,
            4
    );

    Dessert dessert("Chocolate Cake", 8.99, false, false, 450, "Chocolate", 8.5f);

    dessert.setRecipe(recipe);
            CHECK(dessert.hasRecipe());
            CHECK(recipe == dessert.getRecipe());

    dessert.setRecipe(nullptr);
            CHECK(!dessert.hasRecipe());
            CHECK(nullptr == dessert.getRecipe());
}

TEST(Dessert_SweetnessLevel) {
    Dessert dessert("Cake", 5.99, false, false, 300, "Flour", 5.0f);

    dessert.setSweetnessLevel(7.5f);
            CHECK_EQUAL(7.5f, dessert.getSweetnessLevel());

    dessert.setSweetnessLevel(0.0f);
            CHECK_EQUAL(0.0f, dessert.getSweetnessLevel());

    dessert.setSweetnessLevel(10.0f);
            CHECK_EQUAL(10.0f, dessert.getSweetnessLevel());

    dessert.setSweetnessLevel(-5.0f);
            CHECK_EQUAL(0.0f, dessert.getSweetnessLevel());

    dessert.setSweetnessLevel(15.0f);
            CHECK_EQUAL(10.0f, dessert.getSweetnessLevel());
}

TEST(Dessert_Calories) {
    Dessert dessert("Cheesecake", 7.99, false, false, 500, "Cheese", 7.0f);

            CHECK_EQUAL(500, dessert.getCalories());

    dessert.reduceCalories(100);
            CHECK_EQUAL(400, dessert.getCalories());

    dessert.reduceCalories(500);
            CHECK_EQUAL(400, dessert.getCalories());
    dessert.reduceCalories(-50);
            CHECK_EQUAL(400, dessert.getCalories());
}

TEST(Dessert_HealthyOption) {
    Dessert healthy("Fruit Salad", 6.99, true, true, 150, "Fruits", 3.0f);
            CHECK(healthy.isHealthyOption());

    Dessert highCal("Cheesecake", 7.99, true, false, 400, "Cheese", 4.0f);
            CHECK(!highCal.isHealthyOption());

    Dessert tooSweet("Chocolate Mousse", 6.50, true, false, 250, "Chocolate", 8.0f);
            CHECK(!tooSweet.isHealthyOption());

    Dessert notGlutenFree("Brownie", 5.50, false, true, 200, "Chocolate", 7.0f);
            CHECK(!notGlutenFree.isHealthyOption());
}

TEST(Dessert_DietaryInfo) {
    Dessert healthyDessert("Fruit Salad", 6.99, true, true, 150, "Fruits", 3.0f);
    auto healthyInfo = healthyDessert.getDietaryInfo();
            CHECK_EQUAL(3, healthyInfo.size());
            CHECK(find(healthyInfo.begin(), healthyInfo.end(), "Gluten-Free") != healthyInfo.end());
            CHECK(find(healthyInfo.begin(), healthyInfo.end(), "Vegan") != healthyInfo.end());
            CHECK(find(healthyInfo.begin(), healthyInfo.end(), "Low-Calorie") != healthyInfo.end());

    Dessert regularDessert("Cheesecake", 7.99, false, false, 450, "Cheese", 7.0f);
    auto regularInfo = regularDessert.getDietaryInfo();
            CHECK(regularInfo.empty());
}

TEST(Dessert_MakeGlutenFree) {
    Dessert dessert("Brownie", 5.50, false, true, 200, "Chocolate", 7.0f);

            CHECK(!dessert.getIsGlutenFree());
    dessert.makeGlutenFree();
            CHECK(dessert.getIsGlutenFree());
}

TEST(Dessert_EdgeCases) {
    Dessert minDessert("Min", 0.01, false, false, 0, "", 0.0f, false);
            CHECK_EQUAL(0, minDessert.getCalories());
            CHECK_EQUAL(0.0f, minDessert.getSweetnessLevel());
            CHECK_EQUAL("", minDessert.getMainIngredient());
            CHECK(!minDessert.getIsAvailable());

    Dessert maxDessert("Max", 999.99, true, true, 10000,
                       "A very long ingredient name that exceeds normal limits",
                       10.0f, true);
            CHECK_EQUAL(10000, maxDessert.getCalories());
            CHECK_EQUAL(10.0f, maxDessert.getSweetnessLevel());
            CHECK(maxDessert.getIsGlutenFree());
            CHECK(maxDessert.getIsVegan());
}