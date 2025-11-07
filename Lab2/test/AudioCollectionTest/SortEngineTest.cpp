#include "UnitTest++.h"
#include "../../src/AudioCollection/SortEngine/SortEngine.h"
#include "../../src/User/User.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include <memory>
#include "../../src/User/RegisteredUser/Artist/Artist.h"

SUITE(SortEngineTest) {
    TEST(TestSortEngine) {
        Artist user("testuser", "test@example.com", "password123", "Test Artist", "Test Bio");

        AudioCollection collection(user);

        Playlist p1("Playlist B", user);
        Playlist p2("Playlist A", user);
        Playlist p3("Playlist C", user);

        auto song1 = std::make_shared<MusicTrack>("Song 1", 100, 1, "Artist 1", "Pop", 2020);
        auto song2 = std::make_shared<MusicTrack>("Song 2", 200, 2, "Artist 2", "Rock", 2021); p1.addTrack(song1);
        p2.addTrack(song1);
        p2.addTrack(song2);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);
        collection.addPlaylist(p3);

        {
            SortEngine engine(collection);
            engine.setSortCriteria(SortEngine::SortBy::NAME_ASC);
            auto result = engine.getSortedPlaylists();
                    CHECK_EQUAL(3, result.size());
                    CHECK_EQUAL("Playlist A", result[0].getName());
                    CHECK_EQUAL("Playlist B", result[1].getName());
                    CHECK_EQUAL("Playlist C", result[2].getName());
        }

        {
            SortEngine engine(collection);
            engine.setSortCriteria(SortEngine::SortBy::NAME_DESC);
            auto result = engine.getSortedPlaylists();
                    CHECK_EQUAL(3, result.size());
                    CHECK_EQUAL("Playlist C", result[0].getName());
                    CHECK_EQUAL("Playlist B", result[1].getName());
                    CHECK_EQUAL("Playlist A", result[2].getName());
        }

        {
            SortEngine engine(collection);
            engine.setSortCriteria(SortEngine::SortBy::TRACK_COUNT);
            auto result = engine.getSortedPlaylists();
                    CHECK_EQUAL(3, result.size());
                    CHECK_EQUAL(0, result[0].getTracks().size());
                    CHECK_EQUAL(1, result[1].getTracks().size());
                    CHECK_EQUAL(2, result[2].getTracks().size());
        }

        {
            SortEngine engine(collection);
            engine.setSortCriteria(SortEngine::SortBy::DURATION);
            auto result = engine.getSortedPlaylists();
                    CHECK_EQUAL(3, result.size());

            unsigned long long prevDuration = 0;
            for (const auto& playlist : result) {
                unsigned long long duration = 0;
                for (const auto& track : playlist.getTracks()) {
                    duration += track->getDuration();
                }
                        CHECK(duration >= prevDuration);
                prevDuration = duration;
            }
        }
    }
}