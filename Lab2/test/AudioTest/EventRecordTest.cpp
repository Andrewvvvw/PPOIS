#include "UnitTest++.h"

#include "../../src/Audio/EventRecord/EventRecord.h"
#include "../../src/User/RegisteredUser/Artist/Artist.h"
#include <memory>

SUITE(EventRecordTest) {
    TEST(TestConstructorAndGetters) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        EventRecord event("Test Event", artist, "2025-12-31");

                CHECK_EQUAL("Test Event", event.getEventName());
                CHECK_EQUAL(artist, event.getArtist());
                CHECK_EQUAL("2025-12-31", event.getDate());
    }

    TEST(TestEmptyEventName) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        EventRecord event("", artist, "2025-12-31");

                CHECK_EQUAL("", event.getEventName());
    }

    TEST(TestEmptyDate) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        EventRecord event("Test Event", artist, "");

                CHECK_EQUAL("", event.getDate());
    }

    TEST(TestNullArtist) {
        std::shared_ptr<Artist> nullArtist = nullptr;
        EventRecord event("Test Event", nullArtist, "2025-12-31");

                CHECK(nullptr == event.getArtist());
    }

    TEST(TestMultipleEventRecords) {
        auto artist1 = std::make_shared<Artist>("1", "artist1", "artist1@example.com", "pass123", "Artist One");
        auto artist2 = std::make_shared<Artist>("2", "artist2", "artist2@example.com", "pass456", "Artist Two");

        EventRecord event1("Event 1", artist1, "2025-01-01");
        EventRecord event2("Event 2", artist2, "2025-02-15");

                CHECK_EQUAL("Event 1", event1.getEventName());
                CHECK_EQUAL(artist1, event1.getArtist());
                CHECK_EQUAL("2025-01-01", event1.getDate());

                CHECK_EQUAL("Event 2", event2.getEventName());
                CHECK_EQUAL(artist2, event2.getArtist());
                CHECK_EQUAL("2025-02-15", event2.getDate());
    }

    TEST(TestGetArtistNameThroughEvent) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        EventRecord event("Test Event", artist, "2025-12-31");

        auto eventArtist = event.getArtist();
                CHECK_EQUAL("Test Artist", eventArtist->getArtistName());
    }

    TEST(TestEventWithSpecialCharacters) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        std::string eventName = "Test Event #123!@#$%^&*()_+{}|:<>?\"";
        std::string date = "2025-12-31 23:59:59";

        EventRecord event(eventName, artist, date);

                CHECK_EQUAL(eventName, event.getEventName());
                CHECK_EQUAL(artist, event.getArtist());
                CHECK_EQUAL(date, event.getDate());
    }

    TEST(TestEventWithMaxLengthStrings) {
        auto artist = std::make_shared<Artist>("1", "testuser", "test@example.com", "password123", "Test Artist");
        std::string longName(1000, 'x');
        std::string longDate(100, '2');

        EventRecord event(longName, artist, longDate);

                CHECK_EQUAL(longName, event.getEventName());
                CHECK_EQUAL(artist, event.getArtist());
                CHECK_EQUAL(longDate, event.getDate());
    }
}
