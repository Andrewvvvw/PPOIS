#include "UnitTest++.h"

#include "../../src/Audio/Podcast/Podcast.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/User/RegisteredUser/Podcaster/Podcaster.h"

TEST(PodcastCreation) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");
    Podcast podcast("Test Podcast", "A test podcast", &host, "Technology", 12345, 3600);

            CHECK_EQUAL("Test Podcast", podcast.getName());
            CHECK_EQUAL(3600, podcast.getDuration());
            CHECK_EQUAL(12345, podcast.getCoverID());
            CHECK_EQUAL(&host, podcast.getHost());
            CHECK_EQUAL("Technology", podcast.getCategory());
}

TEST(PodcastGetHost) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");
    Podcast podcast("Test Podcast", "A test podcast", &host, "Technology", 12345, 3600);

    Podcaster* retrievedHost = podcast.getHost();
            CHECK_EQUAL(&host, retrievedHost);
            CHECK_EQUAL("podcast_host", retrievedHost->getUsername());
}

TEST(PodcastGetCategory) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");

    Podcast podcast1("Podcast 1", "Test", &host, "Technology", 1, 1800);
            CHECK_EQUAL("Technology", podcast1.getCategory());

    Podcast podcast2("Podcast 2", "Test", &host, "Science", 2, 2700);
            CHECK_EQUAL("Science", podcast2.getCategory());
}

TEST(PodcastGetAuthor) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");
    Podcast podcast("Test Podcast", "A test podcast", &host, "Technology", 12345, 3600);

            CHECK_EQUAL("podcast_host", podcast.getAuthor());
}

TEST(PodcastWithDifferentDurations) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");

    Podcast shortPodcast("Short", "Short podcast", &host, "Tech", 1, 60);
            CHECK_EQUAL(60, shortPodcast.getDuration());

    Podcast longPodcast("Long", "Long podcast", &host, "Tech", 2, 7200);
            CHECK_EQUAL(7200, longPodcast.getDuration());
}

TEST(PodcastWithDifferentCovers) {
    Podcaster host("host123", "podcast_host", "host@example.com", "password123");

    Podcast podcast1("Podcast 1", "Test", &host, "Tech", 1, 1800);
            CHECK_EQUAL(1, podcast1.getCoverID());

    Podcast podcast2("Podcast 2", "Test", &host, "Tech", 9999, 1800);
            CHECK_EQUAL(9999, podcast2.getCoverID());
}

TEST(PodcastWithDifferentHosts) {
    Podcaster host1("host1", "host_one", "host1@example.com", "pass123");
    Podcaster host2("host2", "host_two", "host2@example.com", "pass456");

    Podcast podcast1("Podcast 1", "Test", &host1, "Tech", 1, 1800);
            CHECK_EQUAL(&host1, podcast1.getHost());

    Podcast podcast2("Podcast 2", "Test", &host2, "Tech", 2, 1800);
            CHECK_EQUAL(&host2, podcast2.getHost());
}