#include "../../src/AudioCollection/SearchEngine/SearchEngine.h"
#include "../../src/Audio/Playlist/Playlist.h"
#include "../../src/User/User.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/Audio/Audio.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "UnitTest++.h"

SUITE(SearchEngineTest) {
    TEST(TestConstructor) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        SearchEngine engine(collection);
    }

    TEST(TestSearchPlaylistsByName_EmptyCollection) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        SearchEngine engine(collection);

        auto result = engine.searchPlaylistsByName("test");
                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchPlaylistsByName_NoMatch) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Rock Playlist", user);
        Playlist p2("Jazz Collection", user);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        SearchEngine engine(collection);
        auto result = engine.searchPlaylistsByName("Classical");

                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchPlaylistsByName_SingleMatch) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Rock Playlist", user);
        Playlist p2("Jazz Collection", user);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        SearchEngine engine(collection);
        auto result = engine.searchPlaylistsByName("Rock");

                CHECK_EQUAL(1, result.size());
                CHECK_EQUAL("Rock Playlist", result[0].getName());
    }

    TEST(TestSearchPlaylistsByName_MultipleMatches) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Rock Playlist", user);
        Playlist p2("Rock Collection", user);
        Playlist p3("Jazz Collection", user);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);
        collection.addPlaylist(p3);

        SearchEngine engine(collection);
        auto result = engine.searchPlaylistsByName("Collection");

                CHECK_EQUAL(2, result.size());

        std::vector<std::string> expectedNames = {"Rock Collection", "Jazz Collection"};
        for (const auto& playlist : result) {
                    CHECK(std::find(expectedNames.begin(), expectedNames.end(), playlist.getName()) != expectedNames.end());
        }
    }

    TEST(TestSearchPlaylistsByName_CaseInsensitive) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Rock Playlist", user);
        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchPlaylistsByName("rock");

                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchTracksByName_EmptyCollection) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        SearchEngine engine(collection);

        auto result = engine.searchTracksByName("test");
                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchTracksByName_NoMatch) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Rock", 2020);
        p1.addTrack(track1);

        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchTracksByName("Nonexistent");

                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchTracksByName_SingleMatch) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        auto track1 = std::make_shared<MusicTrack>("Rock Song", 180, 1, "Artist 1", "Rock", 2020);
        auto track2 = std::make_shared<MusicTrack>("Jazz Song", 200, 2, "Artist 2", "Jazz", 2021);
        p1.addTrack(track1);
        p1.addTrack(track2);

        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchTracksByName("Rock");

                CHECK_EQUAL(1, result.size());
                CHECK_EQUAL("Rock Song", result[0]->getName());
    }

    TEST(TestSearchTracksByName_MultipleMatches) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        auto track1 = std::make_shared<MusicTrack>("Rock Song", 180, 1, "Artist 1", "Rock", 2020);
        auto track2 = std::make_shared<MusicTrack>("Rock Anthem", 200, 2, "Artist 2", "Rock", 2020);
        auto track3 = std::make_shared<MusicTrack>("Jazz Song", 220, 3, "Artist 3", "Jazz", 2021);
        p1.addTrack(track1);
        p1.addTrack(track2);
        p1.addTrack(track3);

        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchTracksByName("Rock");

                CHECK_EQUAL(2, result.size());

        std::vector<std::string> expectedNames = {"Rock Song", "Rock Anthem"};
        for (const auto& track : result) {
                    CHECK(std::find(expectedNames.begin(), expectedNames.end(), track->getName()) != expectedNames.end());
        }
    }

    TEST(TestSearchTracksByName_CaseInsensitive) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        auto track1 = std::make_shared<MusicTrack>("Rock Song", 180, 1, "Artist 1", "Rock", 2020);
        p1.addTrack(track1);

        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchTracksByName("rock");

                CHECK_EQUAL(0, result.size());
    }

    TEST(TestSearchTracksByName_PartialMatch) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        auto track1 = std::make_shared<MusicTrack>("Sweet Child O' Mine", 180, 1, "Guns N' Roses", "Rock", 1987);
        p1.addTrack(track1);

        collection.addPlaylist(p1);

        SearchEngine engine(collection);
        auto result = engine.searchTracksByName("Child");

                CHECK_EQUAL(1, result.size());
                CHECK_EQUAL("Sweet Child O' Mine", result[0]->getName());
    }
}