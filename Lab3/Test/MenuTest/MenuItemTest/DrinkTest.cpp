#include "../../../Source/Menu/MenuItem/Drink/Drink.h"
#include "../../../Source/Menu/MenuItem/Ingredient/Ingredient.h"
#include "../../../Source/Menu/MenuItem/Recipe/Recipe.h"
#include <UnitTest++.h>

SUITE(DrinkTest) {
    TEST(TestDrinkCreation) {
        Ingredient ingredient("Coffee", 1.0, "cup", 2.0, 100.0);
        Drink coffee("Americano", 150.0, 250.0, false, ingredient);

                CHECK_EQUAL("Americano", coffee.getName());
                CHECK_EQUAL(150.0, coffee.getPrice());
                CHECK_EQUAL(250.0, coffee.getVolume());
                CHECK_EQUAL(false, coffee.getIsAlcoholic());
                CHECK_EQUAL("Coffee", coffee.getMainIngredient().getName());
    }

    TEST(TestDrinkWithRecipe) {
        Ingredient ingredient("Coffee", 1.0, "cup", 2.0, 100.0);
        std::vector<std::string> steps = {"Boil water", "Brew coffee", "Serve hot"};
        std::vector<std::string> ingredients = {"Coffee", "Water"};
        auto recipe = std::make_shared<Recipe>("Americano Recipe", ingredients, steps, 5, 2);

        Drink coffee("Americano", 150.0, 250.0, false, ingredient, recipe);

                CHECK(coffee.hasRecipe());
                CHECK_EQUAL("Americano Recipe", coffee.getRecipe()->getName());
    }

    TEST(TestSetRecipe) {
        Ingredient ingredient("Coffee", 1.0, "cup", 2.0, 100.0);
        Drink coffee("Americano", 150.0, 250.0, false, ingredient);

                CHECK(!coffee.hasRecipe());

        std::vector<std::string> steps = {"Brew coffee"};
        std::vector<std::string> ingredients = {"Coffee"};
        auto recipe = std::make_shared<Recipe>("Simple Coffee", ingredients, steps, 3, 1);

        coffee.setRecipe(recipe);

                CHECK(coffee.hasRecipe());
                CHECK_EQUAL("Simple Coffee", coffee.getRecipe()->getName());
    }

    TEST(TestVolumeModification) {
        Ingredient ingredient("Tea", 1.0, "cup", 1.0, 50.0);
        Drink tea("Green Tea", 100.0, 200.0, false, ingredient);

        tea.setVolume(300.0);
                CHECK_EQUAL(300.0, tea.getVolume());

        tea.setVolume(-100.0);
                CHECK_EQUAL(300.0, tea.getVolume());
    }

    TEST(TestAlcoholicProperty) {
        Ingredient ingredient("Gin", 50.0, "ml", 100.0, 200.0);
        Drink ginTonic("Gin Tonic", 300.0, 250.0, true, ingredient);

                CHECK(ginTonic.getIsAlcoholic());

        ginTonic.setIsAlcoholic(false);
                CHECK(!ginTonic.getIsAlcoholic());
    }

    TEST(TestChangeMainIngredient) {
        Ingredient oldIngredient("Coffee", 1.0, "cup", 2.0, 100.0);
        Drink drink("Hot Drink", 120.0, 200.0, false, oldIngredient);

        Ingredient newIngredient("Tea", 1.0, "cup", 1.0, 50.0);
        drink.changeMainIngredient(newIngredient);

                CHECK_EQUAL("Tea", drink.getMainIngredient().getName());
                CHECK_EQUAL(1.0, drink.getMainIngredient().getCalories());
    }

    TEST(TestRecipeOperations) {
        Ingredient ingredient("Coffee", 1.0, "cup", 2.0, 100.0);
        std::vector<std::string> steps = {"Step 1", "Step 2"};
        std::vector<std::string> ingredients = {"Coffee", "Water"};
        auto recipe = std::make_shared<Recipe>("Coffee Recipe", ingredients, steps, 5, 2);

        Drink coffee("Americano", 150.0, 250.0, false, ingredient, recipe);

                CHECK(coffee.hasRecipe());
                CHECK_EQUAL(2, coffee.getRecipe()->getSteps().size());
                CHECK_EQUAL(2, coffee.getRecipe()->getIngredients().size());

        coffee.setRecipe(nullptr);
                CHECK(!coffee.hasRecipe());
    }

    TEST(TestInheritance) {
        Ingredient ingredient("Milk", 200.0, "ml", 120.0, 50.0);
        Drink milk("Milk", 80.0, 200.0, false, ingredient);

                CHECK_EQUAL(80.0, milk.getPrice());

        milk.setPrice(90.0);
                CHECK_EQUAL(90.0, milk.getPrice());
    }
}