#include "UnitTest++.h"
#include "../../src/Audio/Album/MusicTrack/TrackRemix/TrackRemix.h"
#include "../../src/Exceptions/Exceptions.h"

SUITE(TrackRemixTest) {
    TEST(TestConstructorAndGetters) {
        std::string name = "Summer Remix";
        unsigned long long duration = 180;
        unsigned long long coverID = 12345;
        std::string artistName = "DJ Test";
        std::string genre = "House";
        unsigned int releaseYear = 2023;
        std::string originalTrackId = "track_123";
        std::string remixStyle = "Deep House";

        TrackRemix track(name, duration, coverID, artistName, genre, releaseYear,
                        originalTrackId, remixStyle);

        CHECK_EQUAL(name, track.getName());
        CHECK_EQUAL(duration, track.getDuration());
        CHECK_EQUAL(coverID, track.getCoverID());
        CHECK_EQUAL(artistName, track.getAuthor());
        CHECK_EQUAL(genre, track.getGenre());
        CHECK_EQUAL(releaseYear, track.getReleaseYear());
        CHECK_EQUAL(originalTrackId, track.getOriginalTrackId());
        CHECK_EQUAL(remixStyle, track.getRemixStyle());
        CHECK_EQUAL(artistName, track.getRemixArtist());
    }

    TEST(TestUpdateRemixStyle) {
        TrackRemix track("Test Track", 180, 12345, "Test Artist", "Pop", 2023,
                        "track_456", "Original Style");
        std::string newStyle = "New Style";

        track.updateRemixStyle(newStyle);

        CHECK_EQUAL(newStyle, track.getRemixStyle());
    }

    TEST(TestThrowException) {
        CHECK_THROW(TrackRemix track("", 0, 0, "", "", 0, "", ""), ExceptionIncorrectAudioName);
    }

    TEST(TestEmptyStrings) {
        TrackRemix track("track1", 0, 0, "", "", 0, "", "");

        CHECK(!track.getName().empty());
        CHECK(track.getAuthor().empty());
        CHECK(track.getGenre().empty());
        CHECK(track.getOriginalTrackId().empty());
        CHECK(track.getRemixStyle().empty());
        CHECK(track.getRemixArtist().empty());
    }

    TEST(TestUpdateRemixStyleWithEmptyString) {
        TrackRemix track("Test", 180, 1, "Artist", "Genre", 2023, "track_789", "Old Style");

        track.updateRemixStyle("");

        CHECK(track.getRemixStyle().empty());
    }

    TEST(TestRemixArtistSameAsArtist) {
        std::string artistName = "Test DJ";
        TrackRemix track("Track", 200, 1, artistName, "EDM", 2023, "track_111", "Progressive");

        CHECK_EQUAL(artistName, track.getRemixArtist());
    }
}
