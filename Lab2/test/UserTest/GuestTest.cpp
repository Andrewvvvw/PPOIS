#include "UnitTest++.h"
#include "../../src/User/Guest/Guest.h"
#include <thread>

SUITE(GuestTests) {
    TEST(TestGuestInitialization) {
        Guest guest;
        CHECK_EQUAL("guest", guest.getId().substr(0, 5));
        CHECK_EQUAL("Guest", guest.getUsername());
        CHECK(guest.getRegistrationDate() <= time(nullptr));
    }

    TEST(TestGetUserType) {
        Guest guest;
        CHECK_EQUAL("Guest", guest.getUserType());
    }

    TEST(TestCanComment) {
        Guest guest;
        CHECK(!guest.canComment());
    }

    TEST(TestGetIsPremium) {
        Guest guest;
        CHECK(!guest.getIsPremium());
    }

    TEST(TestCanUploadContent) {
        Guest guest;
        CHECK(!guest.canUploadContent());
    }

    TEST(TestGetViewLimitInitial) {
        Guest guest;
        CHECK_EQUAL(0, guest.getViewLimit());
    }

    TEST(TestCanViewContentInitially) {
        Guest guest;
        CHECK(guest.canViewContent());
    }

    TEST(TestIncrementViewCount) {
        Guest guest;
        for (int i = 0; i < 10; ++i) {
            CHECK(guest.canViewContent());
            guest.incrementViewCount();
            CHECK_EQUAL(i + 1, guest.getViewLimit());
        }

        CHECK(!guest.canViewContent());

        guest.incrementViewCount();
        CHECK_EQUAL(10, guest.getViewLimit());
        CHECK(!guest.canViewContent());
    }

    TEST(TestGetSessionDuration) {
        Guest guest;
        auto start = guest.getSessionDuration();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto duration = guest.getSessionDuration();
        CHECK(duration >= 1);
        CHECK(duration >= start);
    }

    TEST(TestSetUsername) {
        Guest guest;
        guest.setUsername("NewGuestName");
        CHECK_EQUAL("NewGuestName", guest.getUsername());
    }

    TEST(TestAudioCollectionAccess) {
        Guest guest;
        CHECK(guest.getAudioCollection() != nullptr);
        CHECK(guest.getAudioCollection() == guest.getAudioCollection());
    }
}
