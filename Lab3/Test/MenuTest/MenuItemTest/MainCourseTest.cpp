#include "../../../Source/Menu/MenuItem/MainCourse/MainCourse.h"
#include "../../../Source/Menu/MenuItem/Ingredient/Ingredient.h"
#include "../../../Source/Menu/MenuItem/Recipe/Recipe.h"
#include <UnitTest++.h>

SUITE(MainCourseTest) {
    TEST(TestMainCourseCreation) {
        std::vector<Ingredient> ingredients = {
                Ingredient("Chicken", 200.0, "grams", 1.65, 150.0),
                Ingredient("Rice", 150.0, "grams", 1.3, 30.0)
        };

        MainCourse dish("Chicken with Rice", 350.0, true, ingredients, 30, "Asian", false, 2);

                CHECK_EQUAL("Chicken with Rice", dish.getName());
                CHECK_EQUAL(350.0, dish.getPrice());

                CHECK(dish.containsIngredient("Chicken"));
                CHECK(dish.containsIngredient("Rice"));
    }

    TEST(TestRecipeManagement) {
        MainCourse dish("Pasta", 250.0, true, {}, 20, "Italian", true, 1);

                CHECK(!dish.hasRecipe());

        std::vector<std::string> steps = {"Boil water", "Cook pasta", "Add sauce"};
        std::vector<std::string> ingredients = {"Pasta", "Tomato", "Basil"};
        auto recipe = std::make_shared<Recipe>("Pasta Recipe", ingredients, steps, 20, 1);

        dish.setRecipe(recipe);
                CHECK(dish.hasRecipe());
                CHECK_EQUAL("Pasta Recipe", dish.getRecipe()->getName());
    }

    TEST(TestIngredientManagement) {
        Ingredient pasta("Pasta", 100.0, "grams", 1.6, 50.0);
        Ingredient sauce("Tomato Sauce", 50.0, "ml", 0.6, 20.0);

        MainCourse dish("Pasta", 250.0, true, {pasta}, 20, "Italian", true, 1);

                CHECK(dish.containsIngredient("Pasta"));
                CHECK(!dish.containsIngredient("Tomato Sauce"));

        dish.addIngredient(sauce);
                CHECK(dish.containsIngredient("Tomato Sauce"));

        dish.removeIngredient("Pasta");
                CHECK(!dish.containsIngredient("Pasta"));
    }

    TEST(TestCalorieCalculation) {
        std::vector<Ingredient> ingredients = {
                Ingredient("Pasta", 100.0, "grams", 1.6, 50.0),
                Ingredient("Cheese", 50.0, "grams", 4.0, 100.0),
                Ingredient("Tomato", 30.0, "grams", 0.18, 20.0)
        };

        MainCourse dish("Pasta Carbonara", 350.0, true, ingredients, 25, "Italian", false, 3);
        double expectedCalories = 1.6 + 4.0 + 0.18;
                CHECK_EQUAL(expectedCalories, dish.calculateTotalCalories());
    }

    TEST(TestSpicinessControl) {
        std::vector<Ingredient> ingredients = {Ingredient("Base", 100.0, "grams", 1.0, 50.0)};
        MainCourse dish("Curry", 300.0, true, ingredients, 40, "Indian", true, 5);

        dish.setSpiciness(8);
        dish.setSpiciness(15);
        dish.setSpiciness(-5);
    }

    TEST(TestEmptyDish) {
        MainCourse emptyDish("Empty", 0.0, false, {}, 0, "", true, 0);

                CHECK_EQUAL(0.0, emptyDish.calculateTotalCalories());
                CHECK(!emptyDish.containsIngredient("Anything"));
        emptyDish.removeIngredient("Nonexistent");
    }

    TEST(TestMultipleIngredients) {
        std::vector<Ingredient> ingredients;
        for (int i = 0; i < 100; ++i) {
            ingredients.emplace_back("Ingredient" + std::to_string(i), 10.0, "grams", 0.1, 1.0);
        }

        MainCourse bigDish("Big Dish", 1000.0, true, ingredients, 60, "Fusion", true, 5);
                CHECK_CLOSE(10.0, bigDish.calculateTotalCalories(), 0.0001);
                CHECK(bigDish.containsIngredient("Ingredient50"));

        bigDish.removeIngredient("Ingredient50");
                CHECK(!bigDish.containsIngredient("Ingredient50"));
                CHECK_CLOSE(9.9, bigDish.calculateTotalCalories(), 0.0001);
    }
}