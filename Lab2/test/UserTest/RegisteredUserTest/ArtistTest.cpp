#include "../../src/User/RegisteredUser/Artist/Artist.h"
#include "../../src/Audio/Album/Album.h"
#include "../../src/Exceptions/Exceptions.h"
#include <UnitTest++.h>
#include <memory>

using namespace std;

SUITE(ArtistTest) {
    TEST(TestConstructorAndGetters) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");

                CHECK_EQUAL("Test Artist", artist->getArtistName());
                CHECK(artist->getBiography().empty());
                CHECK_EQUAL(0, artist->getMonthlyListeners());
                CHECK_EQUAL("Artist", artist->getUserType());
                CHECK(artist->canUploadContent());
    }

    TEST(TestUpdateBiography) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string bio = "A talented musician";

        artist->updateBiography(bio);
                CHECK_EQUAL(bio, artist->getBiography());
    }

    TEST(TestUpdateMonthlyListeners) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");

        artist->updateMonthlyListeners(100);
                CHECK_EQUAL(100, artist->getMonthlyListeners());

        artist->updateMonthlyListeners(-50);
                CHECK_EQUAL(50, artist->getMonthlyListeners());

        artist->updateMonthlyListeners(-100);
                CHECK_EQUAL(0, artist->getMonthlyListeners());
    }

    TEST(TestCreateAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Test Album";
        const unsigned int releaseYear = 2023;
        const unsigned long long coverId = 1;

        artist->createAlbum(albumTitle, releaseYear, coverId);

        auto albumTitles = artist->getAlbumTitles();
                CHECK_EQUAL(1, albumTitles.size());
                CHECK_EQUAL(albumTitle, albumTitles[0]);

        auto album = artist->getAlbum(albumTitle);
                CHECK(album != nullptr);
                CHECK_EQUAL(albumTitle, album->getTitle());
                CHECK_EQUAL(releaseYear, album->getReleaseYear());
    }

    TEST(TestAddTrackToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Test Album";
        artist->createAlbum(albumTitle, 2023, 1);

        auto track = make_shared<MusicTrack>("Track 1", 180, 1, "Test Artist", "Pop", 2023);
        bool result = artist->addTrackToAlbum(albumTitle, track);

                CHECK(result);

        auto album = artist->getAlbum(albumTitle);
        auto trackList = album->getTrackList();
                CHECK_EQUAL(1, trackList.size());
                CHECK_EQUAL("Track 1", trackList[0]);
    }

    TEST(TestAddTrackToNonExistentAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        auto track = make_shared<MusicTrack>("Track 1", 180, 1, "Test Artist", "Pop", 2023);

        bool result = artist->addTrackToAlbum("Nonexistent Album", track);
                CHECK(!result);
    }

    TEST(TestAddRemixToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Remix Album";
        artist->createAlbum(albumTitle, 2023, 2);

        auto originalTrack = make_shared<MusicTrack>("Original", 180, 1, "Test Artist", "Pop", 2023);
        auto remix = make_shared<TrackRemix>(
                "Remix", 200, 2, "Test Artist", "Electronic", 2023,
                originalTrack->getName(), "Dance Remix"
        );

        bool result = artist->addRemixToAlbum(albumTitle, remix);
                CHECK(result);

        auto album = artist->getAlbum(albumTitle);
        auto trackList = album->getTrackList();
                CHECK_EQUAL(1, trackList.size());
                CHECK_EQUAL("Remix (Remix)", trackList[0]);
    }

    TEST(TestGetNonExistentAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        auto album = artist->getAlbum("Nonexistent Album");
                CHECK(album == nullptr);
    }

    TEST(TestGetAlbumTitles) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->createAlbum("Album 1", 2023, 1);
        artist->createAlbum("Album 2", 2023, 2);

        auto titles = artist->getAlbumTitles();
                CHECK_EQUAL(2, titles.size());
                CHECK(std::find(titles.begin(), titles.end(), "Album 1") != titles.end());
                CHECK(std::find(titles.begin(), titles.end(), "Album 2") != titles.end());
    }

    TEST(TestAddDuplicateTrackToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Test Album";
        artist->createAlbum(albumTitle, 2023, 1);
        auto track = make_shared<MusicTrack>("Track 1", 180, 1, "Test Artist", "Pop", 2023);

        bool result1 = artist->addTrackToAlbum(albumTitle, track);
        bool result2 = artist->addTrackToAlbum(albumTitle, track);

                CHECK(result1);
                CHECK(result2);
    }

    TEST(TestAddNullTrackToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Test Album";
        artist->createAlbum(albumTitle, 2023, 1);

        bool result = artist->addTrackToAlbum(albumTitle, nullptr);
                CHECK(!result);
    }

    TEST(TestCreateAlbumWithEmptyTitle) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
                CHECK_THROW(artist->createAlbum("", 2023, 1), ExceptionIncorrectAlbumTitle);
    }

    TEST(TestGetTracksFromEmptyAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Empty Album";
        artist->createAlbum(albumTitle, 2023, 1);

        auto album = artist->getAlbum(albumTitle);
        auto tracks = album->getTrackList();
                CHECK(tracks.empty());
    }

    TEST(TestUpdateBiographyWithEmptyString) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->updateBiography("");
                CHECK(artist->getBiography().empty());
    }

    TEST(TestUpdateMonthlyListenersWithLargeNegative) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->updateMonthlyListeners(100);
        artist->updateMonthlyListeners(-200);
                CHECK_EQUAL(0, artist->getMonthlyListeners());
    }

    TEST(TestCreateDuplicateAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Duplicate Album";
        artist->createAlbum(albumTitle, 2023, 1);
                CHECK_THROW(artist->createAlbum(albumTitle, 2023, 2), ExceptionIncorrectAlbumTitle);
    }

    TEST(TestAddRemixWithNonexistentOriginal) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Remix Album";
        artist->createAlbum(albumTitle, 2023, 2);

        auto remix = make_shared<TrackRemix>(
                "Remix", 200, 2, "Test Artist", "Electronic", 2023,
                "nonexistent", "Dance Remix"
        );

        bool result = artist->addRemixToAlbum(albumTitle, remix);
                CHECK(result);
    }

    TEST(TestCreateArtistWithEmptyName) {
                CHECK_THROW(
                make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", ""),
                ExceptionIncorrectArtistName
        );
    }

    TEST(TestUpdateMonthlyListenersPositive) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->updateMonthlyListeners(50);
                CHECK_EQUAL(50, artist->getMonthlyListeners());
    }

    TEST(TestUpdateMonthlyListenersNegativeWithinLimit) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->updateMonthlyListeners(100);
        artist->updateMonthlyListeners(-30);
                CHECK_EQUAL(70, artist->getMonthlyListeners());
    }

    TEST(TestUpdateMonthlyListenersNegativeBelowZero) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->updateMonthlyListeners(20);
        artist->updateMonthlyListeners(-30);
                CHECK_EQUAL(0, artist->getMonthlyListeners());
    }

    TEST(TestCreateAlbumWithInvalidYear) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
                CHECK_THROW(artist->createAlbum("Old Album", 1949, 1), ExceptionIncorrectYear);
                CHECK_THROW(artist->createAlbum("Future Album", 2026, 1), ExceptionIncorrectYear);
    }

    TEST(TestAddNullRemixToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        artist->createAlbum("Remix Album", 2023, 2);
        bool result = artist->addRemixToAlbum("Remix Album", nullptr);
                CHECK(!result);
    }

    TEST(TestGetAlbumTitlesWhenNoAlbums) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        auto titles = artist->getAlbumTitles();
                CHECK(titles.empty());
    }

    TEST(TestAddMultipleTracksToAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        const string albumTitle = "Multi-Track Album";
        artist->createAlbum(albumTitle, 2023, 1);

        auto track1 = make_shared<MusicTrack>("Track 1", 180, 1, "Test Artist", "Pop", 2023);
        auto track2 = make_shared<MusicTrack>("Track 2", 200, 2, "Test Artist", "Pop", 2023);

                CHECK(artist->addTrackToAlbum(albumTitle, track1));
                CHECK(artist->addTrackToAlbum(albumTitle, track2));

        auto album = artist->getAlbum(albumTitle);
        auto trackList = album->getTrackList();
                CHECK_EQUAL(2, trackList.size());
    }

    TEST(TestAddRemixToNonExistentAlbum) {
        shared_ptr<Artist> artist = make_shared<Artist>("id1", "testuser", "test@test.com", "pass123", "Test Artist");
        auto originalTrack = make_shared<MusicTrack>("Original", 180, 1, "Test Artist", "Pop", 2023);
        auto remix = make_shared<TrackRemix>(
                "Remix", 200, 2, "Test Artist", "Electronic", 2023,
                originalTrack->getName(), "Dance Remix"
        );

        bool result = artist->addRemixToAlbum("Nonexistent Album", remix);
                CHECK(!result);
    }
}