#include "UnitTest++.h"
#include "../../Source/Menu/MenuItem/AllergenInfo/AllergenInfo.h"

TEST(AllergenInfo_Constructor) {
    AllergenInfo allergen("Peanuts", "Common allergen found in many foods",
                          AllergenSeverity::HIGH, true);

            CHECK_EQUAL("Peanuts", allergen.getName());
            CHECK_EQUAL("Common allergen found in many foods", allergen.getDescription());
            CHECK(AllergenSeverity::HIGH == allergen.getSeverity());
            CHECK(allergen.getIsCommon());
            CHECK_EQUAL(0, allergen.getAlternativeNames().size());
}

TEST(AllergenInfo_AddAlternativeName) {
    AllergenInfo allergen("Milk", "Dairy product", AllergenSeverity::MEDIUM, true);

    allergen.addAlternativeName("Dairy");
    allergen.addAlternativeName("Lactose");

    const auto& alternatives = allergen.getAlternativeNames();
            CHECK_EQUAL(2, alternatives.size());
            CHECK(alternatives[0] == "Dairy");
            CHECK(alternatives[1] == "Lactose");
            CHECK(allergen.hasAlternative("Dairy"));
            CHECK(allergen.hasAlternative("Lactose"));
            CHECK(!allergen.hasAlternative("Nonexistent"));
}

TEST(AllergenInfo_SeverityChecks) {
    AllergenInfo lowAllergen("Low", "", AllergenSeverity::LOW, false);
    AllergenInfo mediumAllergen("Medium", "", AllergenSeverity::MEDIUM, false);
    AllergenInfo highAllergen("High", "", AllergenSeverity::HIGH, false);

            CHECK(!lowAllergen.isSevere());
            CHECK(!mediumAllergen.isSevere());
            CHECK(highAllergen.isSevere());

            CHECK(lowAllergen.isMoreSevereThan(AllergenSeverity::LOW) == false);
            CHECK(mediumAllergen.isMoreSevereThan(AllergenSeverity::LOW) == true);
            CHECK(highAllergen.isMoreSevereThan(AllergenSeverity::MEDIUM) == true);
}

TEST(AllergenInfo_GetSeverityString) {
    AllergenInfo low("Low", "", AllergenSeverity::LOW, false);
    AllergenInfo medium("Medium", "", AllergenSeverity::MEDIUM, false);
    AllergenInfo high("High", "", AllergenSeverity::HIGH, false);

            CHECK_EQUAL("Low", low.getSeverityString());
            CHECK_EQUAL("Medium", medium.getSeverityString());
            CHECK_EQUAL("High", high.getSeverityString());
}

TEST(AllergenInfo_Setters) {
    AllergenInfo allergen("Original", "Original description", AllergenSeverity::LOW, false);

    allergen.setSeverity(AllergenSeverity::HIGH);
            CHECK(AllergenSeverity::HIGH == allergen.getSeverity());

    allergen.setDescription("New description");
            CHECK_EQUAL("New description", allergen.getDescription());
}

TEST(AllergenInfo_CommonStatus) {
    AllergenInfo common("Common", "", AllergenSeverity::MEDIUM, true);
    AllergenInfo uncommon("Uncommon", "", AllergenSeverity::MEDIUM, false);

            CHECK(common.getIsCommon());
            CHECK(!uncommon.getIsCommon());
}

TEST(AllergenInfo_DuplicateAlternatives) {
    AllergenInfo allergen("Test", "", AllergenSeverity::LOW, false);

    allergen.addAlternativeName("Alt1");
    allergen.addAlternativeName("Alt1");
    allergen.addAlternativeName("Alt2");

    const auto& alternatives = allergen.getAlternativeNames();
            CHECK_EQUAL(3, alternatives.size());
            CHECK(alternatives[0] == "Alt1");
            CHECK(alternatives[1] == "Alt1");
            CHECK(alternatives[2] == "Alt2");
}