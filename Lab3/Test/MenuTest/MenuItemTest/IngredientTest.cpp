#include "../../../Source/Menu/MenuItem/Ingredient/Ingredient.h"
#include <UnitTest++.h>

SUITE(IngredientTest) {
    TEST(TestIngredientCreation) {
        Ingredient ingredient("Flour", 500.0, "grams", 1820.0, 30.0);

        CHECK_EQUAL("Flour", ingredient.getName());
        CHECK_EQUAL(500.0, ingredient.getQuantity());
        CHECK_EQUAL("grams", ingredient.getUnit());
        CHECK_EQUAL(1820.0, ingredient.getCalories());
        CHECK_EQUAL(30.0, ingredient.getPrice());
    }

    TEST(TestSetters) {
        Ingredient ingredient("Sugar", 1000.0, "grams", 4000.0, 50.0);

        ingredient.setQuantity(750.0);
        CHECK_EQUAL(750.0, ingredient.getQuantity());

        ingredient.setPrice(60.0);
        CHECK_EQUAL(60.0, ingredient.getPrice());
    }

    TEST(TestIsLowInStock) {
        Ingredient ingredient("Salt", 100.0, "grams", 0.0, 10.0);

        CHECK(ingredient.isLowInStock(150.0));
        CHECK(!ingredient.isLowInStock(50.0));
        CHECK(!ingredient.isLowInStock(100.0));
    }

    TEST(TestCalculateTotalCalories) {
        Ingredient ingredient("Butter", 100.0, "grams", 7.17, 100.0);
        CHECK_EQUAL(717.0, ingredient.calculateTotalCalories());

        ingredient.setQuantity(50.0);
        CHECK_EQUAL(358.5, ingredient.calculateTotalCalories());
    }

    TEST(TestIsExpensive) {
        Ingredient cheapIngredient("Water", 1000.0, "ml", 0.0, 20.0);
        Ingredient expensiveIngredient("Saffron", 1.0, "gram", 3.0, 1000.0);

        CHECK(!cheapIngredient.isExpensive(50.0));
        CHECK(expensiveIngredient.isExpensive(50.0));
        CHECK(!expensiveIngredient.isExpensive(1000.0));
    }

    TEST(TestScaleQuantity) {
        Ingredient ingredient("Milk", 200.0, "ml", 130.0, 40.0);

        ingredient.scaleQuantity(2.0);
        CHECK_EQUAL(400.0, ingredient.getQuantity());

        ingredient.scaleQuantity(0.5);
        CHECK_EQUAL(200.0, ingredient.getQuantity());

        ingredient.scaleQuantity(0.0);
        CHECK_EQUAL(0.0, ingredient.getQuantity());
    }

    TEST(TestEdgeCases) {
        Ingredient zeroIngredient("Air", 0.0, "ml", 0.0, 0.0);

        CHECK_EQUAL(0.0, zeroIngredient.calculateTotalCalories());
        CHECK(zeroIngredient.isLowInStock(0.1));
        CHECK(!zeroIngredient.isExpensive(0.0));

        zeroIngredient.scaleQuantity(10.0);
        CHECK_EQUAL(0.0, zeroIngredient.getQuantity());
    }

    TEST(TestNegativeValues) {
        Ingredient ingredient("Vinegar", -100.0, "ml", -50.0, -10.0);

        CHECK_EQUAL(-100.0, ingredient.getQuantity());
        CHECK_EQUAL(-50.0, ingredient.getCalories());
        CHECK_EQUAL(-10.0, ingredient.getPrice());

        ingredient.scaleQuantity(-2.0);
        CHECK_EQUAL(200.0, ingredient.getQuantity());

        ingredient.setQuantity(-50.0);
        CHECK_EQUAL(-50.0, ingredient.getQuantity());
    }
}
