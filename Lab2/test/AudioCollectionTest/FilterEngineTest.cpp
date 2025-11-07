#include "../../src/AudioCollection/FilterEngine/FilterEngine.h"
#include "../../src/Audio/Playlist/Playlist.h"
#include "../../src/User/User.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "UnitTest++.h"

SUITE(FilterEngineTest) {
    TEST(TestConstructor) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        FilterEngine engine(collection);
    }

    TEST(TestSetPublicFilter) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        FilterEngine engine(collection);

        engine.setPublicFilter(true);
        engine.setPublicFilter(false);
    }

    TEST(TestSetMinTracksFilter) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        FilterEngine engine(collection);

        engine.setMinTracksFilter(5);
        engine.setMinTracksFilter(10);
    }

    TEST(TestResetFilters) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);
        FilterEngine engine(collection);

        engine.setPublicFilter(true);
        engine.setMinTracksFilter(5);
        engine.resetFilters();
    }

    TEST(TestGetFilteredPlaylists_NoFilters) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        Playlist p2("Playlist2", user);
        p2.setPublic(false);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        FilterEngine engine(collection);
        auto result = engine.getFilteredPlaylists();

                CHECK_EQUAL(2, result.size());
    }

    TEST(TestGetFilteredPlaylists_PublicFilter_True) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("PublicPlaylist", user);
        p1.setPublic(true);

        Playlist p2("PrivatePlaylist", user);
        p2.setPublic(false);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        FilterEngine engine(collection);
        engine.setPublicFilter(true);

        auto result = engine.getFilteredPlaylists();
                CHECK_EQUAL(1, result.size());
                CHECK_EQUAL("PublicPlaylist", result[0].getName());
    }

    TEST(TestGetFilteredPlaylists_PublicFilter_False) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("PublicPlaylist", user);
        p1.setPublic(true);

        Playlist p2("PrivatePlaylist", user);
        p2.setPublic(false);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        FilterEngine engine(collection);
        engine.setPublicFilter(false);

        auto result = engine.getFilteredPlaylists();
                CHECK_EQUAL(1, result.size());
                CHECK_EQUAL("PrivatePlaylist", result[0].getName());
    }

    TEST(TestGetFilteredPlaylists_MinTracksFilter) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        Playlist p2("Playlist2", user);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);

        FilterEngine engine(collection);
        engine.setMinTracksFilter(1);

        auto result = engine.getFilteredPlaylists();
                CHECK_EQUAL(0, result.size());
    }

    TEST(TestGetFilteredPlaylists_CombinedFilters) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("PublicPlaylist1", user);
        p1.setPublic(true);

        Playlist p2("PublicPlaylist2", user);
        p2.setPublic(true);

        Playlist p3("PrivatePlaylist1", user);
        p3.setPublic(false);

        collection.addPlaylist(p1);
        collection.addPlaylist(p2);
        collection.addPlaylist(p3);

        FilterEngine engine(collection);
        engine.setPublicFilter(true);
        engine.setMinTracksFilter(0);

        auto result = engine.getFilteredPlaylists();
                CHECK_EQUAL(2, result.size());

        std::vector<std::string> expectedNames = {"PublicPlaylist1", "PublicPlaylist2"};
        for (const auto& playlist : result) {
                    CHECK(std::find(expectedNames.begin(), expectedNames.end(), playlist.getName()) != expectedNames.end());
        }
    }

    TEST(TestResetFilters_AfterFiltering) {
        RegisteredUser user("test_id", "test_user", "test@test.com", "password");
        AudioCollection collection(user);

        Playlist p1("Playlist1", user);
        collection.addPlaylist(p1);

        FilterEngine engine(collection);
        engine.setPublicFilter(true);
        engine.setMinTracksFilter(1);

        auto filtered = engine.getFilteredPlaylists();
                CHECK_EQUAL(0, filtered.size());

        engine.resetFilters();

        auto all = engine.getFilteredPlaylists();
                CHECK_EQUAL(1, all.size());
    }
}