#include "UnitTest++.h"

#include "../../src/AudioCollection/AdManager/AdManager.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/Exceptions/Exceptions.h"

SUITE(AdManagerTest) {
    TEST(Constructor_InitializesWithUser) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

                CHECK_EQUAL(0, manager.getAdvertisements().size());
    }

    TEST(AddAdvertisement_AddsAdvertisementToCollection) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        Advertisement ad("ad1", "Test ad content", 30);

        manager.addAdvertisement(ad);

        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(1, ads.size());
                CHECK_EQUAL("ad1", ads[0].getId());
                CHECK_EQUAL("Test ad content", ads[0].getContent());
                CHECK_EQUAL(30, ads[0].getDuration());
    }

    TEST(RemoveAdvertisement_RemovesExistingAdvertisement) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        Advertisement ad1("ad1", "Ad 1", 10);
        Advertisement ad2("ad2", "Ad 2", 20);

        manager.addAdvertisement(ad1);
        manager.addAdvertisement(ad2);

        manager.removeAdvertisement(ad1);

        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(1, ads.size());
                CHECK_EQUAL("ad2", ads[0].getId());
    }

    TEST(RemoveAdvertisement_DoesNothingWhenAdvertisementNotFound) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        Advertisement ad1("ad1", "Ad 1", 10);
        Advertisement ad2("ad2", "Ad 2", 20);

        manager.addAdvertisement(ad1);

        manager.removeAdvertisement(ad2);

        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(1, ads.size());
                CHECK_EQUAL("ad1", ads[0].getId());
    }

    TEST(ShowAd_ThrowsExceptionForInvalidIndex) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

                CHECK_THROW(manager.showAd(-1), std::runtime_error);
                CHECK_THROW(manager.showAd(0), std::runtime_error);

        Advertisement ad("ad1", "Test ad content", 30);
        manager.addAdvertisement(ad);

                CHECK_THROW(manager.showAd(1), std::runtime_error);
    }

    TEST(GetAdvertisements_ReturnsCopyOfAdvertisements) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        Advertisement ad1("ad1", "Ad 1", 10);
        Advertisement ad2("ad2", "Ad 2", 20);

        manager.addAdvertisement(ad1);
        auto ads1 = manager.getAdvertisements();

        manager.addAdvertisement(ad2);
        auto ads2 = manager.getAdvertisements();

                CHECK_EQUAL(1, ads1.size());
                CHECK_EQUAL(2, ads2.size());
    }
    TEST(AddAdvertisement_AddsMultipleAdvertisements) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

        // Add multiple advertisements
        for (int i = 0; i < 5; ++i) {
            Advertisement ad("ad" + std::to_string(i), "Content " + std::to_string(i), i * 10);
            manager.addAdvertisement(ad);
        }

        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(5, ads.size());
        for (int i = 0; i < 5; ++i) {
                    CHECK_EQUAL("ad" + std::to_string(i), ads[i].getId());
                    CHECK_EQUAL("Content " + std::to_string(i), ads[i].getContent());
                    CHECK_EQUAL(i * 10, ads[i].getDuration());
        }
    }

    TEST(RemoveAdvertisement_RemovesMultipleAdvertisements) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        std::vector<Advertisement> testAds = {
                {"ad1", "Ad 1", 10},
                {"ad2", "Ad 2", 20},
                {"ad3", "Ad 3", 30},
                {"ad4", "Ad 4", 40}
        };

        for (const auto& ad : testAds) {
            manager.addAdvertisement(ad);
        }

        // Remove some ads
        manager.removeAdvertisement(testAds[1]);
        manager.removeAdvertisement(testAds[3]);

        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(2, ads.size());
                CHECK_EQUAL("ad1", ads[0].getId());
                CHECK_EQUAL("ad3", ads[1].getId());
    }

    TEST(ShowAd_ReturnsCorrectContent) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        std::vector<Advertisement> testAds = {
                {"ad1", "First ad", 10},
                {"ad2", "Second ad", 20},
                {"ad3", "Third ad", 30}
        };

        for (const auto& ad : testAds) {
            manager.addAdvertisement(ad);
        }

                CHECK_EQUAL("Second ad", manager.showAd(1));
    }

    TEST(ShowAd_ThrowsExceptionForNegativeIndex) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        manager.addAdvertisement({"ad1", "Test", 10});

                CHECK_THROW(manager.showAd(-1), std::runtime_error);
    }

    TEST(ShowAd_ThrowsExceptionForIndexOutOfBounds) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);
        manager.addAdvertisement({"ad1", "Test", 10});

                CHECK_THROW(manager.showAd(1), std::runtime_error);
                CHECK_THROW(manager.showAd(100), std::runtime_error);
    }

    TEST(GetAdvertisements_ReturnsEmptyVectorWhenNoAds) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

        auto ads = manager.getAdvertisements();
                CHECK(ads.empty());
    }

    TEST(AddRemoveCombination_VerifiesCorrectState) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

        // Initial state
                CHECK(manager.getAdvertisements().empty());

        // Add ads
        Advertisement ad1("ad1", "Ad 1", 10);
        Advertisement ad2("ad2", "Ad 2", 20);
        manager.addAdvertisement(ad1);
        manager.addAdvertisement(ad2);

        // Verify addition
        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(2, ads.size());

        // Remove and verify
        manager.removeAdvertisement(ad1);
        ads = manager.getAdvertisements();
                CHECK_EQUAL(1, ads.size());
                CHECK_EQUAL("ad2", ads[0].getId());

        // Add more
        Advertisement ad3("ad3", "Ad 3", 30);
        manager.addAdvertisement(ad3);
        ads = manager.getAdvertisements();
                CHECK_EQUAL(2, ads.size());
    }

    TEST(RemoveNonExistentAdvertisement_DoesNotAffectCollection) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

        // Add some ads
        Advertisement ad1("ad1", "Ad 1", 10);
        Advertisement ad2("ad2", "Ad 2", 20);
        manager.addAdvertisement(ad1);

        // Try to remove non-existent ad
        manager.removeAdvertisement(ad2);

        // Verify only ad1 remains
        auto ads = manager.getAdvertisements();
                CHECK_EQUAL(1, ads.size());
                CHECK_EQUAL("ad1", ads[0].getId());
    }

    TEST(ShowAd_WithMultipleAdsReturnsCorrectContent) {
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        AdManager manager(user);

        // Add multiple ads
        std::vector<std::string> contents = {"First", "Second", "Third", "Fourth"};
        for (size_t i = 0; i < contents.size(); ++i) {
            manager.addAdvertisement({"ad" + std::to_string(i+1), contents[i], static_cast<int>((i+1)*10)});
        }

        // Verify each ad's content
        for (size_t i = 0; i < contents.size(); ++i) {
                    CHECK_EQUAL(contents[i], manager.showAd(static_cast<int>(i)));
        }
    }
}