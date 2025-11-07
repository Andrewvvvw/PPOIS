#include "UnitTest++.h"
#include "../../src/Audio/FavoriteList/FavoriteList.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/Exceptions/Exceptions.h"
#include <memory>

SUITE(FavoriteListTest) {
    class TestFixture {
    public:
        std::shared_ptr<MusicTrack> track1;
        std::shared_ptr<MusicTrack> track2;
        std::shared_ptr<MusicTrack> track3;
        FavoriteList favoriteList;

        TestFixture() {
            track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Rock", 2020);
            track2 = std::make_shared<MusicTrack>("Track 2", 210, 2, "Artist 2", "Pop", 2021);
            track3 = std::make_shared<MusicTrack>("Track 3", 195, 3, "Artist 3", "Jazz", 2019);
        }
    };

    TEST_FIXTURE(TestFixture, AddToFavorites) {
        CHECK_EQUAL(0, favoriteList.getTracks().size());

        favoriteList.addToFavorites(track1);
        CHECK_EQUAL(1, favoriteList.getTracks().size());
        CHECK_EQUAL(track1, favoriteList.getTracks()[0]);

        favoriteList.addToFavorites(track2);
        CHECK_EQUAL(2, favoriteList.getTracks().size());
        CHECK_EQUAL(track2, favoriteList.getTracks()[1]);
    }

    TEST_FIXTURE(TestFixture, AddSameTrackMultipleTimes) {
        favoriteList.addToFavorites(track1);
        favoriteList.addToFavorites(track1);
        favoriteList.addToFavorites(track1);

        CHECK_EQUAL(3, favoriteList.getTracks().size());
        CHECK_EQUAL(track1, favoriteList.getTracks()[0]);
        CHECK_EQUAL(track1, favoriteList.getTracks()[1]);
        CHECK_EQUAL(track1, favoriteList.getTracks()[2]);
    }

    TEST_FIXTURE(TestFixture, RemoveFromFavorites) {
        favoriteList.addToFavorites(track1);
        favoriteList.addToFavorites(track2);
        favoriteList.addToFavorites(track3);

        favoriteList.removeFromFavorites(track2);
        CHECK_EQUAL(2, favoriteList.getTracks().size());
        CHECK_EQUAL(track1, favoriteList.getTracks()[0]);
        CHECK_EQUAL(track3, favoriteList.getTracks()[1]);

        favoriteList.removeFromFavorites(track1);
        CHECK_EQUAL(1, favoriteList.getTracks().size());
        CHECK_EQUAL(track3, favoriteList.getTracks()[0]);

        favoriteList.removeFromFavorites(track3);
        CHECK_EQUAL(0, favoriteList.getTracks().size());
    }

    TEST_FIXTURE(TestFixture, RemoveNonExistentTrack) {
        favoriteList.addToFavorites(track1);
        favoriteList.removeFromFavorites(track2);

        CHECK_EQUAL(1, favoriteList.getTracks().size());
        CHECK_EQUAL(track1, favoriteList.getTracks()[0]);
    }

    TEST_FIXTURE(TestFixture, RemoveFromEmptyList) {
        favoriteList.removeFromFavorites(track1);
        CHECK_EQUAL(0, favoriteList.getTracks().size());
    }

    TEST_FIXTURE(TestFixture, GetTracksReturnsCopy) {
        favoriteList.addToFavorites(track1);
        auto tracks = favoriteList.getTracks();
        tracks.push_back(track2);

        CHECK_EQUAL(1, favoriteList.getTracks().size());
        CHECK_EQUAL(2, tracks.size());
    }

    TEST_FIXTURE(TestFixture, AddNullptr) {
        std::shared_ptr<MusicTrack> nullTrack = nullptr;
        favoriteList.addToFavorites(nullTrack);

        CHECK_EQUAL(1, favoriteList.getTracks().size());
        CHECK(!favoriteList.getTracks()[0]);
    }

    TEST_FIXTURE(TestFixture, RemoveNullptr) {
        favoriteList.addToFavorites(track1);
        std::shared_ptr<MusicTrack> nullTrack = nullptr;

        favoriteList.removeFromFavorites(nullTrack);
        CHECK_EQUAL(1, favoriteList.getTracks().size());

        favoriteList.addToFavorites(nullTrack);
        favoriteList.removeFromFavorites(nullTrack);
        CHECK_EQUAL(1, favoriteList.getTracks().size());
    }

    TEST_FIXTURE(TestFixture, LargeNumberOfTracks) {
        const int count = 1000;
        for (int i = 0; i < count; ++i) {
            auto track = std::make_shared<MusicTrack>("Track " + std::to_string(i), 180 + i, i, "Artist " + std::to_string(i % 10), "Genre", 2000 + i % 20);
            favoriteList.addToFavorites(track);
        }

        CHECK_EQUAL(count, favoriteList.getTracks().size());

        for (int i = 0; i < count; ++i) {
            auto track = favoriteList.getTracks()[i];
            CHECK_EQUAL("Track " + std::to_string(i), track->getName());
        }
    }
}
