#include "UnitTest++.h"
#include "../../src/Audio/Radio/Radio.h"
#include "../../src/User/RegisteredUser/RadioHost/RadioHost.h"

SUITE(RadioTest) {
    TEST(TestRadioConstructorAndGetters) {
        auto host = std::make_shared<RadioHost>("host1", "DJ Test", "dj@test.com", "password123", "Rock", "Rock FM");
        Radio radio("Rock", "Rock FM", host, "Morning Show", "Best morning show ever!", 12345);

                CHECK_EQUAL("Rock", radio.getGenre());
                CHECK_EQUAL("Rock FM", radio.getStation());
                CHECK_EQUAL(host, radio.getHost());
                CHECK_EQUAL("Morning Show", radio.getName());
                CHECK_EQUAL(18000, radio.getDuration());
                CHECK_EQUAL(12345, radio.getCoverID());
                CHECK_EQUAL("DJ Test", radio.getAuthor());
    }

    TEST(TestSetters) {
        auto host1 = std::make_shared<RadioHost>("host1", "DJ One", "one@test.com", "pass1", "Pop", "Pop FM");
        auto host2 = std::make_shared<RadioHost>("host2", "DJ Two", "two@test.com", "pass2", "Jazz", "Jazz FM");

        Radio radio("Pop", "Pop FM", host1, "Pop Hits", "Top 40", 111);

        radio.setGenre("Jazz");
                CHECK_EQUAL("Jazz", radio.getGenre());

        radio.setStation("Jazz FM");
                CHECK_EQUAL("Jazz FM", radio.getStation());

        radio.setHost(host2);
                CHECK_EQUAL(host2, radio.getHost());
                CHECK_EQUAL("DJ Two", radio.getAuthor());
    }

    TEST(TestChangeStation) {
        auto host = std::make_shared<RadioHost>("host1", "DJ Test", "test@example.com", "password123", "News", "News FM");
        Radio radio("News", "News FM", host, "Morning News", "Latest updates", 222);

        radio.changeStation("News 24/7");
                CHECK_EQUAL("News 24/7", radio.getStation());
    }

    TEST(TestEmptyValues) {
        auto host = std::make_shared<RadioHost>("host1", "DJ Empty", "empty@example.com", "pass123", "", "");
        Radio radio("", "", host, "empty", "", 0);

                CHECK(radio.getGenre().empty());
                CHECK(radio.getStation().empty());
                CHECK(!radio.getName().empty());
                CHECK_EQUAL(0, radio.getCoverID());
    }

    TEST(TestHostChange) {
        auto host1 = std::make_shared<RadioHost>("host1", "Original Host", "original@example.com", "pass1", "Genre", "Station");
        auto host2 = std::make_shared<RadioHost>("host2", "New Host", "new@example.com", "pass2", "New Genre", "New Station");

        Radio radio("Genre", "Station", host1, "Show", "Description", 1);

                CHECK_EQUAL("Original Host", radio.getAuthor());

        radio.setHost(host2);
                CHECK_EQUAL("New Host", radio.getAuthor());
    }

    TEST(TestMaxValues) {
        auto host = std::make_shared<RadioHost>(
                "host1",
                std::string(100, 'a'),
                std::string(100, 'b') + "@example.com",
                std::string(100, 'c'),
                std::string(100, 'd'),
                std::string(100, 'e')
        );

        Radio radio(
                std::string(1000, 'a'),
                std::string(1000, 'b'),
                host,
                std::string(1000, 'c'),
                std::string(1000, 'd'),
                ULLONG_MAX
        );

                CHECK_EQUAL(1000, radio.getGenre().length());
                CHECK_EQUAL(1000, radio.getStation().length());
                CHECK_EQUAL(1000, radio.getName().length());
                CHECK_EQUAL(ULLONG_MAX, radio.getCoverID());
    }
}