#include <UnitTest++.h>
#include "../../src/User/RegisteredUser/UserStatistics/UserStatistics.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/User/User.h"
#include "../../src/AudioCollection/AudioCollection.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/Audio/Playlist/Playlist.h"

using namespace std;

SUITE(UserStatisticsTest) {
    TEST(GetFavoriteCreatorName_SinglePlaylistSingleCreator) {
        RegisteredUser owner("owner1", "testowner", "owner@example.com", "password");
        RegisteredUser user("user1", "testuser", "test@example.com", "password");
        UserStatistics stats;
        AudioCollection audioCollection(owner);

        auto track1 = make_shared<MusicTrack>("Song1", 180, 1, "Artist1", "Rock", 2023);
        auto track2 = make_shared<MusicTrack>("Song2", 200, 1, "Artist1", "Rock", 2023);

        Playlist playlist("Test Playlist", owner);
        playlist.addTrack(track1);
        playlist.addTrack(track2);
        audioCollection.addPlaylist(playlist);

        CHECK_EQUAL("Artist1", stats.getFavoriteCreatorName(user, audioCollection));
    }

    TEST(GetFavoriteCreatorName_MultipleCreators) {
        RegisteredUser owner("owner1", "testowner", "owner@example.com", "password");
        RegisteredUser user("user1", "testuser", "test@example.com", "password");
        UserStatistics stats;
        AudioCollection audioCollection(owner);

        auto track1 = make_shared<MusicTrack>("Song1", 180, 1, "Artist1", "Rock", 2023);
        auto track2 = make_shared<MusicTrack>("Song2", 200, 2, "Artist2", "Pop", 2023);
        auto track3 = make_shared<MusicTrack>("Song3", 220, 1, "Artist1", "Rock", 2023);

        Playlist playlist("Test Playlist", owner);
        playlist.addTrack(track1);
        playlist.addTrack(track2);
        playlist.addTrack(track3);
        audioCollection.addPlaylist(playlist);

        CHECK_EQUAL("Artist1", stats.getFavoriteCreatorName(user, audioCollection));
    }

    TEST(GetFavoriteCreatorName_EmptyPlaylist) {
        RegisteredUser owner("owner1", "testowner", "owner@example.com", "password");
        RegisteredUser user("user1", "testuser", "test@example.com", "password");
        UserStatistics stats;
        AudioCollection audioCollection(owner);

        Playlist playlist("Empty Playlist", owner);
        audioCollection.addPlaylist(playlist);

        CHECK_EQUAL("", stats.getFavoriteCreatorName(user, audioCollection));
    }

    TEST(GetFavoriteCreatorName_MultiplePlaylists) {
        RegisteredUser owner("owner1", "testowner", "owner@example.com", "password");
        RegisteredUser user("user1", "testuser", "test@example.com", "password");
        UserStatistics stats;
        AudioCollection audioCollection(owner);

        auto track1 = make_shared<MusicTrack>("Song1", 180, 1, "Artist1", "Rock", 2023);
        auto track2 = make_shared<MusicTrack>("Song2", 200, 2, "Artist2", "Pop", 2023);
        auto track3 = make_shared<MusicTrack>("Song3", 180, 3, "Artist1", "Rock", 2023);
        auto track4 = make_shared<MusicTrack>("Song4", 200, 4, "Artist1", "Pop", 2023);

        Playlist playlist1("Playlist 1", owner);
        playlist1.addTrack(track1);
        playlist1.addTrack(track2);
        audioCollection.addPlaylist(playlist1);

        Playlist playlist2("Playlist 2", owner);
        playlist2.addTrack(track3);
        playlist2.addTrack(track4);
        audioCollection.addPlaylist(playlist2);

        CHECK_EQUAL("Artist1", stats.getFavoriteCreatorName(user, audioCollection));
    }

    TEST(GetFavoriteCreatorName_SingleTrack) {
        RegisteredUser owner("owner1", "testowner", "owner@example.com", "password");
        RegisteredUser user("user1", "testuser", "test@example.com", "password");
        UserStatistics stats;
        AudioCollection audioCollection(owner);

        auto track = make_shared<MusicTrack>("LonelySong", 300, 1, "SoloArtist", "Blues", 2023);

        Playlist playlist("Single Track Playlist", owner);
        playlist.addTrack(track);
        audioCollection.addPlaylist(playlist);

        CHECK_EQUAL("SoloArtist", stats.getFavoriteCreatorName(user, audioCollection));
    }
}