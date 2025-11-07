#include "UnitTest++.h"
#include "../../src/AudioCollection/AdManager/Advertisement/Advertisement.h"
#include "../../src/Exceptions/Exceptions.h"

SUITE(AdvertisementTest) {
    TEST(TestConstructorAndGetters) {
        std::string id = "ad123";
        std::string content = "Check out our new product!";
        int duration = 30;

        Advertisement ad(id, content, duration);

                CHECK_EQUAL(id, ad.getId());
                CHECK_EQUAL(content, ad.getContent());
                CHECK_EQUAL(duration, ad.getDuration());
    }

    TEST(TestEqualityOperatorEqual) {
        Advertisement ad1("ad1", "Content 1", 30);
        Advertisement ad2("ad1", "Content 1", 30);

                CHECK(ad1 == ad2);
    }

    TEST(TestEqualityOperatorDifferentId) {
        Advertisement ad1("ad1", "Content 1", 30);
        Advertisement ad2("ad2", "Content 1", 30);

                CHECK(!(ad1 == ad2));
    }

    TEST(TestEqualityOperatorDifferentContent) {
        Advertisement ad1("ad1", "Content 1", 30);
        Advertisement ad2("ad1", "Content 2", 30);

                CHECK(!(ad1 == ad2));
    }

    TEST(TestEqualityOperatorDifferentDuration) {
        Advertisement ad1("ad1", "Content 1", 30);
        Advertisement ad2("ad1", "Content 1", 45);

                CHECK(!(ad1 == ad2));
    }

    TEST(TestEqualityOperatorSelfComparison) {
        Advertisement ad("ad1", "Content 1", 30);

                CHECK(ad == ad);
    }

    TEST(TestEqualityOperatorDifferentObjectsSameValues) {
        std::string id = "ad123";
        std::string content = "Same content";
        int duration = 30;

        Advertisement ad1(id, content, duration);
        Advertisement ad2(id, content, duration);

                CHECK(ad1 == ad2);
    }
}
