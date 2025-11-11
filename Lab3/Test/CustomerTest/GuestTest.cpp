#include "UnitTest++.h"
#include "Source/Customer/Guest/Guest.h"

SUITE(GuestTest) {
    TEST(ConstructorAndGetters) {
        Guest guest("John Doe", 1, "john@example.com");
        CHECK_EQUAL("John Doe", guest.getName());
        CHECK_EQUAL(1, guest.getId());
        CHECK_EQUAL(0.0, guest.getTotalSpent());
    }

    TEST(NewsletterSubscription) {
        Guest guest("Bob Wilson", 3, "bob@example.com");

        guest.subscribeToNewsletter();

        guest.subscribeToNewsletter();
    }

    TEST(PreferencesManagement) {
        Guest guest("Alice Brown", 4, "alice@example.com");

        CHECK(!guest.hasPreference("vegetarian"));

        guest.addPreference("vegetarian");
        CHECK(guest.hasPreference("vegetarian"));

        guest.addPreference("vegan");
        CHECK(guest.hasPreference("vegan"));

        CHECK(!guest.hasPreference("gluten-free"));
    }

    TEST(TotalSpent) {
        Guest guest("Charlie Davis", 5, "charlie@example.com");

        guest.setTotalSpent(100.0);
        CHECK_EQUAL(100.0, guest.getTotalSpent());

        guest.setTotalSpent(150.0);
        CHECK_EQUAL(150.0, guest.getTotalSpent());
    }

}