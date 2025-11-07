#include "UnitTest++.h"
#include "../../src/Audio/Album/Album.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/Audio/Album/MusicTrack/TrackRemix/TrackRemix.h"
#include "../../src/Exceptions/Exceptions.h"
#include <memory>

SUITE(AlbumTest) {
    TEST(ConstructorAndGetters) {
        Album album("Test Album", "Test Artist", 2020, 1);

                CHECK_EQUAL("Test Album", album.getTitle());
                CHECK_EQUAL("Test Artist", album.getArtist());
                CHECK_EQUAL(2020, album.getReleaseYear());
                CHECK_EQUAL(1, album.getCoverId());
                CHECK_EQUAL(0, album.getTotalTracks());
                CHECK_EQUAL(0, album.getTotalDuration());
                CHECK(album.getTrackList().empty());
    }

    TEST(ConstructorWithEmptyTitle) {
                CHECK_THROW(Album("", "Test Artist", 2020, 1), ExceptionIncorrectAlbumTitle);
    }

    TEST(AddAndRemoveTracks) {
        Album album("Test Album", "Test Artist", 2020, 1);
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2020);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2020);

        album.addTrack(track1);
                CHECK_EQUAL(1, album.getTotalTracks());
                CHECK_EQUAL(180, album.getTotalDuration());

        album.addTrack(track2);
                CHECK_EQUAL(2, album.getTotalTracks());
                CHECK_EQUAL(380, album.getTotalDuration());

        bool removed = album.removeTrack("Track 1");
                CHECK(removed);
                CHECK_EQUAL(1, album.getTotalTracks());
                CHECK_EQUAL(200, album.getTotalDuration());

        removed = album.removeTrack("Nonexistent Track");
                CHECK(!removed);
    }

    TEST(AddAndRemoveRemixes) {
        Album album("Test Album", "Test Artist", 2020, 1);
        auto originalTrack = std::make_shared<MusicTrack>("Original", 180, 1, "Artist 1", "Pop", 2020);
        auto remix = std::make_shared<TrackRemix>("Remix", 200, 2, "Remixer", "EDM", 2021, "original_track_123","House");

        album.addRemix(remix);
                CHECK_EQUAL(1, album.getTotalTracks());
                CHECK_EQUAL(200, album.getTotalDuration());

        bool removed = album.removeTrack("Remix");
                CHECK(removed);
                CHECK_EQUAL(0, album.getTotalTracks());
                CHECK_EQUAL(0, album.getTotalDuration());
    }

    TEST(AddNullTrack) {
        Album album("Test Album", "Test Artist", 2020, 1);
        std::shared_ptr<MusicTrack> nullTrack = nullptr;

                CHECK_THROW(album.addTrack(nullTrack), ExceptionIncorrectTrack);
    }

    TEST(AddNullRemix) {
        Album album("Test Album", "Test Artist", 2020, 1);
        std::shared_ptr<TrackRemix> nullRemix = nullptr;

                CHECK_THROW(album.addRemix(nullRemix), ExceptionIncorrectTrack);
    }

    TEST(GetTrackList) {
        Album album("Test Album", "Test Artist", 2020, 1);
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2020);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2020);
        auto originalTrack = std::make_shared<MusicTrack>("Original", 180, 1, "Artist 1", "Pop", 2020);
        auto remix = std::make_shared<TrackRemix>("Remix", 200, 2, "Remixer", "EDM", 2021, "original_track_123","House");

        album.addTrack(track1);
        album.addTrack(track2);
        album.addRemix(remix);

        auto trackList = album.getTrackList();
                CHECK_EQUAL(3, trackList.size());
                CHECK_EQUAL("Track 1", trackList[0]);
                CHECK_EQUAL("Track 2", trackList[1]);
                CHECK_EQUAL("Remix (Remix)", trackList[2]);
    }

    TEST(TotalDurationWithEmptyAlbum) {
        Album album("Test Album", "Test Artist", 2020, 1);
                CHECK_EQUAL(0, album.getTotalDuration());
    }

    TEST(RemoveNonexistentTrack) {
        Album album("Test Album", "Test Artist", 2020, 1);
        bool removed = album.removeTrack("Nonexistent Track");
                CHECK(!removed);
    }
}