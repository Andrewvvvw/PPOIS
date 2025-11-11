#include "../../../Source/Menu/MenuItem/Recipe/Recipe.h"
#include <UnitTest++.h>

SUITE(RecipeTest) {
    TEST(TestRecipeCreation) {
        std::vector<std::string> ingredients = {"Pasta", "Tomato", "Cheese"};
        std::vector<std::string> steps = {"Boil water", "Add pasta", "Add sauce"};

        Recipe recipe("Pasta Carbonara", ingredients, steps, 30, 2);

        CHECK_EQUAL("Pasta Carbonara", recipe.getName());
        CHECK_EQUAL(3, recipe.getIngredients().size());
        CHECK_EQUAL(3, recipe.getSteps().size());
        CHECK_EQUAL(30, recipe.getPreparationTime());
        CHECK_EQUAL(2, recipe.getDifficulty());
    }

    TEST(TestAddIngredient) {
        Recipe recipe("Test Recipe", {}, {}, 10, 1);

        recipe.addIngredient("Salt");
        CHECK(recipe.containsIngredient("Salt"));
        CHECK_EQUAL(1, recipe.getIngredients().size());

        recipe.addIngredient("Salt");
        CHECK_EQUAL(2, recipe.getIngredients().size());
    }

    TEST(TestAddStep) {
        Recipe recipe("Test Recipe", {}, {}, 10, 1);

        recipe.addStep("First step");
        recipe.addStep("Second step");

        auto steps = recipe.getSteps();
        CHECK_EQUAL(2, steps.size());
        CHECK_EQUAL("First step", steps[0]);
        CHECK_EQUAL("Second step", steps[1]);
    }

    TEST(TestSetPreparationTime) {
        Recipe recipe("Test Recipe", {}, {}, 10, 1);

        recipe.setPreparationTime(45);
        CHECK_EQUAL(45, recipe.getPreparationTime());

        recipe.setPreparationTime(-10);
        CHECK_EQUAL(45, recipe.getPreparationTime());
    }

    TEST(TestContainsIngredient) {
        std::vector<std::string> ingredients = {"Flour", "Eggs", "Milk"};
        Recipe recipe("Pancakes", ingredients, {}, 20, 1);

        CHECK(recipe.containsIngredient("Flour"));
        CHECK(recipe.containsIngredient("Eggs"));
        CHECK(recipe.containsIngredient("Milk"));
        CHECK(!recipe.containsIngredient("Sugar"));
        CHECK(!recipe.containsIngredient("flour"));
    }

    TEST(TestGetFormattedRecipe) {
        std::vector<std::string> ingredients = {"Flour", "Eggs"};
        std::vector<std::string> steps = {"Mix", "Bake"};
        Recipe recipe("Cake", ingredients, steps, 60, 2);

        std::string formatted = recipe.getFormattedRecipe();

        CHECK(formatted.find("Recipe: Cake") != std::string::npos);
        CHECK(formatted.find("Ingredients (2):") != std::string::npos);
        CHECK(formatted.find("- Flour") != std::string::npos);
        CHECK(formatted.find("- Eggs") != std::string::npos);
        CHECK(formatted.find("1. Mix") != std::string::npos);
        CHECK(formatted.find("2. Bake") != std::string::npos);
        CHECK(formatted.find("Preparation time: 60 minutes") != std::string::npos);
        CHECK(formatted.find("Difficulty: 2/5") != std::string::npos);
    }

    TEST(TestEmptyRecipe) {
        Recipe empty("Empty Recipe", {}, {}, 0, 0);

        CHECK(empty.getIngredients().empty());
        CHECK(empty.getSteps().empty());
        CHECK_EQUAL(0, empty.getPreparationTime());
        CHECK_EQUAL(3, empty.getDifficulty());

        std::string formatted = empty.getFormattedRecipe();
        CHECK(formatted.find("Recipe: Empty Recipe") != std::string::npos);
        CHECK(formatted.find("Ingredients (0):") != std::string::npos);
        CHECK(formatted.find("Steps (0):") != std::string::npos);
    }

    TEST(TestLargeRecipe) {
        std::vector<std::string> ingredients;
        std::vector<std::string> steps;

        for (int i = 0; i < 100; i++) {
            ingredients.push_back("Ingredient_" + std::to_string(i));
            steps.push_back("Step_" + std::to_string(i + 1));
        }

        Recipe largeRecipe("Large Recipe", ingredients, steps, 120, 3);

        CHECK_EQUAL(100, largeRecipe.getIngredients().size());
        CHECK_EQUAL(100, largeRecipe.getSteps().size());

        CHECK(largeRecipe.containsIngredient("Ingredient_0"));
        CHECK(largeRecipe.containsIngredient("Ingredient_99"));

        auto stepsList = largeRecipe.getSteps();
        CHECK_EQUAL("Step_1", stepsList[0]);
        CHECK_EQUAL("Step_100", stepsList[99]);

        std::string formatted = largeRecipe.getFormattedRecipe();
        CHECK(formatted.find("Ingredients (100):") != std::string::npos);
        CHECK(formatted.find("Steps (100):") != std::string::npos);
    }
}
