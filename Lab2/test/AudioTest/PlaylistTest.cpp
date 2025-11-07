#include "UnitTest++.h"
#include "../../src/Audio/Playlist/Playlist.h"
#include "../../src/Audio/Audio.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../src/Exceptions/Exceptions.h"

using namespace std;

class MockAudio : public Audio {
public:
    MockAudio(unsigned long long duration, string name, unsigned long long coverID)
            : Audio(duration, name, coverID) {}

    string getAuthor() const override {
        return "MockAuthor";
    }
};

class MockRegisteredUser : public RegisteredUser {
public:
    MockRegisteredUser() : RegisteredUser("test_id", "test_user", "test@example.com", "password123") {}
};

SUITE(PlaylistTest) {
    TEST(Constructor) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user, true);

                CHECK_EQUAL("Test Playlist", playlist.getName());
                CHECK_EQUAL(&user, &playlist.getCreator());
                CHECK_EQUAL(true, playlist.getIsPublic());
                CHECK_EQUAL(0, playlist.getTrackCount());
    }

    TEST(AddAndRemoveTrack) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);
        auto track = make_shared<MockAudio>(180, "Test Track", 1);

        playlist.addTrack(track);
                CHECK_EQUAL(1, playlist.getTrackCount());

        auto tracks = playlist.getTracks();
                CHECK_EQUAL(track.get(), tracks[0].get());

        playlist.removeTrack(track);
                CHECK_EQUAL(0, playlist.getTrackCount());
    }

    TEST(GetCurrentTrack) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

                CHECK(nullptr == playlist.getCurrentTrack());

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
                CHECK_EQUAL(track1.get(), playlist.getCurrentTrack().get());

        playlist.addTrack(track2);
                CHECK_EQUAL(track1.get(), playlist.getCurrentTrack().get());
    }

    TEST(RemoveTrackUpdatesCurrentIndex) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
        playlist.addTrack(track2);

        playlist.removeTrack(track1);
                CHECK_EQUAL(track2.get(), playlist.getCurrentTrack().get());

        playlist.removeTrack(track2);
                CHECK(nullptr == playlist.getCurrentTrack());
    }

    TEST(SetPublic) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user, false);

                CHECK_EQUAL(false, playlist.getIsPublic());

        playlist.setPublic(true);
                CHECK_EQUAL(true, playlist.getIsPublic());
    }

    TEST(Clear) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
        playlist.addTrack(track2);

                CHECK_EQUAL(2, playlist.getTrackCount());

        playlist.clear();
                CHECK_EQUAL(0, playlist.getTrackCount());
                CHECK(nullptr == playlist.getCurrentTrack());
    }

    TEST(GetTotalDuration) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
        playlist.addTrack(track2);

                CHECK_EQUAL(380, playlist.getTotalDuration());
    }

    TEST(EqualityOperator) {
        MockRegisteredUser user1;
        MockRegisteredUser user2;

        Playlist playlist1("Playlist", user1);
        Playlist playlist2("Playlist", user1);
        Playlist playlist3("Different Playlist", user1);
        Playlist playlist4("Playlist", user2);

                CHECK(playlist1 == playlist2);
                CHECK(!(playlist1 == playlist3));
                CHECK(!(playlist1 == playlist4));
    }

    TEST(GetTracks) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
        playlist.addTrack(track2);

        auto tracks = playlist.getTracks();
                CHECK_EQUAL(2, tracks.size());
                CHECK_EQUAL(track1.get(), tracks[0].get());
                CHECK_EQUAL(track2.get(), tracks[1].get());
    }

    TEST(RemoveNonExistentTrack) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track1 = make_shared<MockAudio>(180, "Track 1", 1);
        auto track2 = make_shared<MockAudio>(200, "Track 2", 2);

        playlist.addTrack(track1);
        playlist.removeTrack(track2);

                CHECK_EQUAL(1, playlist.getTrackCount());
    }

    TEST(RemoveFromEmptyPlaylist) {
        MockRegisteredUser user;
        Playlist playlist("Test Playlist", user);

        auto track = make_shared<MockAudio>(180, "Track 1", 1);

        playlist.removeTrack(track);

                CHECK_EQUAL(0, playlist.getTrackCount());
    }
}
