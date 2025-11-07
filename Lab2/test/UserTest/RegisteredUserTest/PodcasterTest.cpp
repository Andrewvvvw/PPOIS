#include "UnitTest++.h"
#include "../../src/User/RegisteredUser/Podcaster/Podcaster.h"

using namespace std;

SUITE(PodcasterTest) {
    TEST(TestPodcasterCreation) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
                CHECK_EQUAL("user123", podcaster.getId());
                CHECK_EQUAL("testuser", podcaster.getUsername());
                CHECK_EQUAL("test@example.com", podcaster.getEmail());
                CHECK_EQUAL("password123", podcaster.getPassword());
                CHECK_EQUAL("RegisteredUser", podcaster.getUserType());
                CHECK(!podcaster.getIsPremium());
    }

    TEST(TestAddPodcast) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
        auto podcast1 = make_shared<Podcast>("Podcast 1", "Description 1", &podcaster, "category1", 1, 3600);
        auto podcast2 = make_shared<Podcast>("Podcast 2", "Description 2", &podcaster, "category2", 2, 1800);

                CHECK(podcaster.addPodcast(podcast1));
                CHECK_EQUAL(1, podcaster.getPodcasts().size());
                CHECK(podcaster.hasPodcast(podcast1));

                CHECK(podcaster.addPodcast(podcast2));
                CHECK_EQUAL(2, podcaster.getPodcasts().size());
                CHECK(podcaster.hasPodcast(podcast2));
    }

    TEST(TestRemovePodcast) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
        auto podcast1 = make_shared<Podcast>("Podcast 1", "Description 1", &podcaster, "category1", 1, 3600);
        auto podcast2 = make_shared<Podcast>("Podcast 2", "Description 2", &podcaster, "category2", 2, 1800);

        podcaster.addPodcast(podcast1);
        podcaster.addPodcast(podcast2);

                CHECK(podcaster.removePodcast(podcast1));
                CHECK_EQUAL(1, podcaster.getPodcasts().size());
                CHECK(!podcaster.hasPodcast(podcast1));
                CHECK(podcaster.hasPodcast(podcast2));

                CHECK(podcaster.removePodcast(podcast2));
                CHECK_EQUAL(0, podcaster.getPodcasts().size());
                CHECK(!podcaster.hasPodcast(podcast2));
    }

    TEST(TestRemoveNonExistentPodcast) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
        auto podcast1 = make_shared<Podcast>("Podcast 1", "Description 1", &podcaster, "category1", 1, 3600);
        auto podcast2 = make_shared<Podcast>("Podcast 2", "Description 2", &podcaster, "category2", 2, 1800);

        podcaster.addPodcast(podcast1);

                CHECK(!podcaster.removePodcast(podcast2));
                CHECK_EQUAL(1, podcaster.getPodcasts().size());
                CHECK(podcaster.hasPodcast(podcast1));
    }

    TEST(TestHasPodcast) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
        auto podcast1 = make_shared<Podcast>("Podcast 1", "Description 1", &podcaster, "category1", 1, 3600);
        auto podcast2 = make_shared<Podcast>("Podcast 2", "Description 2", &podcaster, "category2", 2, 1800);

                CHECK(!podcaster.hasPodcast(podcast1));
        podcaster.addPodcast(podcast1);
                CHECK(podcaster.hasPodcast(podcast1));
                CHECK(!podcaster.hasPodcast(podcast2));
    }

    TEST(TestGetPodcasts) {
        Podcaster podcaster("user123", "testuser", "test@example.com", "password123");
        auto podcast1 = make_shared<Podcast>("Podcast 1", "Description 1", &podcaster, "category1", 1, 3600);
        auto podcast2 = make_shared<Podcast>("Podcast 2", "Description 2", &podcaster, "category2", 2, 1800);

        podcaster.addPodcast(podcast1);
        podcaster.addPodcast(podcast2);

        const auto& podcasts = podcaster.getPodcasts();
                CHECK_EQUAL(2, podcasts.size());
                CHECK(podcaster.hasPodcast(podcast1));
                CHECK(podcaster.hasPodcast(podcast2));
    }
}