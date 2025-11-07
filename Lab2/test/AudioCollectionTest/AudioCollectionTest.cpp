#include "UnitTest++.h"
#include "../../src/AudioCollection/AudioCollection.h"
#include "../../src/User/User.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/Audio/Playlist/Playlist.h"
#include "../../src/Audio/Audio.h"

SUITE(AudioCollectionTest) {
    TEST(Constructor) {
        RegisteredUser user("1", "testuser", "test@example.com", "password");
        AudioCollection collection(user);

                CHECK_EQUAL(0, collection.getPlaylists().size());
    }

    TEST(AddAndGetPlaylist) {
        RegisteredUser user1("1", "user1", "user1@example.com", "pass1");
        RegisteredUser user2("2", "user2", "user2@example.com", "pass2");

        AudioCollection collection(user1);
        Playlist playlist1("My Playlist", user1);

        collection.addPlaylist(playlist1);
        auto playlists = collection.getPlaylists();

                CHECK_EQUAL(1, playlists.size());
                CHECK_EQUAL("My Playlist", playlists[0].getName());
                CHECK_EQUAL("1", playlists[0].getCreator().getId());
    }

    TEST(AddMultiplePlaylists) {
        RegisteredUser user("1", "user", "user@example.com", "pass");
        AudioCollection collection(user);

        Playlist playlist1("Playlist 1", user);
        Playlist playlist2("Playlist 2", user);

        collection.addPlaylist(playlist1);
        collection.addPlaylist(playlist2);

        auto playlists = collection.getPlaylists();
                CHECK_EQUAL(2, playlists.size());
    }

    TEST(RemoveExistingPlaylist) {
        RegisteredUser user("1", "user", "user@example.com", "pass");
        AudioCollection collection(user);
        Playlist playlist("My Playlist", user);

        collection.addPlaylist(playlist);
                CHECK_EQUAL(1, collection.getPlaylists().size());

        collection.removePlaylist(playlist);
                CHECK_EQUAL(0, collection.getPlaylists().size());
    }

    TEST(RemoveNonExistentPlaylist) {
        RegisteredUser user("1", "user", "user@example.com", "pass");
        AudioCollection collection(user);

        Playlist playlist1("Playlist 1", user);
        Playlist playlist2("Playlist 2", user);

        collection.addPlaylist(playlist1);
        collection.removePlaylist(playlist2);

                CHECK_EQUAL(1, collection.getPlaylists().size());
    }

    TEST(RemovePlaylistDifferentUser) {
        RegisteredUser user1("1", "user1", "user1@example.com", "pass1");
        RegisteredUser user2("2", "user2", "user2@example.com", "pass2");

        AudioCollection collection(user1);
        Playlist playlist1("Playlist 1", user1);
        Playlist playlist2("Playlist 2", user2);

        collection.addPlaylist(playlist1);
        collection.addPlaylist(playlist2);

        collection.removePlaylist(playlist1);

        auto playlists = collection.getPlaylists();
                CHECK_EQUAL(1, playlists.size());
                CHECK_EQUAL("Playlist 2", playlists[0].getName());
    }

    TEST(GetPlaylistsReturnsCopy) {
        RegisteredUser user("1", "user", "user@example.com", "pass");
        AudioCollection collection(user);

        Playlist playlist1("Playlist 1", user);
        collection.addPlaylist(playlist1);

        auto playlists1 = collection.getPlaylists();
        auto playlists2 = collection.getPlaylists();

                CHECK(playlists1[0].getName() == playlists2[0].getName());

        playlists1[0].setPublic(false);

                CHECK(playlists1[0].getIsPublic() != playlists2[0].getIsPublic());
    }
}