#include "UnitTest++.h"
#include "../../src/AudioCollection/CollectionStatistics/CollectionStatistics.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/Audio/AudioBook/AudioBook.h"
#include "../../src/Audio/AudioCourse/AudioCourse.h"
#include "../../src/Audio/Podcast/Podcast.h"
#include "../../src/User/RegisteredUser/Podcaster/Podcaster.h"

TEST(CollectionStatistics_EmptyCollection) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);
    CollectionStatistics stats(collection);

    CHECK_EQUAL(0, stats.getNumberOfPlaylists());
    CHECK_EQUAL(0, stats.getTotalDuration());

    auto commonTypes = stats.getMostCommonAudioTypes(3);
    CHECK(commonTypes.empty());
}

TEST(CollectionStatistics_SinglePlaylistSingleTrack) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);
    Playlist playlist("My Playlist", user, true);

    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Genre 1", 2023);
    playlist.addTrack(track1);

    collection.addPlaylist(playlist);
    CollectionStatistics stats(collection);

    CHECK_EQUAL(1, stats.getNumberOfPlaylists());
    CHECK_EQUAL(180, stats.getTotalDuration());

    auto commonTypes = stats.getMostCommonAudioTypes(3);
    CHECK_EQUAL(1, commonTypes.size());
}

TEST(CollectionStatistics_MultiplePlaylistsMultipleTracks) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);

    Playlist playlist1("Playlist 1", user, true);
    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Genre 1", 2023);
    auto author = std::make_shared<BookAuthor>("auth1", "Author Name", "author@example.com", "password123");
    auto narrator = std::make_shared<Broadcaster>("narr1", "narrator_username", "narrator@example.com", "password123", "Narrator Name");
    auto track2 = std::make_shared<AudioBook>("Book 1", 240, 2, author, narrator);
    playlist1.addTrack(track1);
    playlist1.addTrack(track2);

    Playlist playlist2("Playlist 2", user, true);
    auto track3 = std::make_shared<AudioCourse>("Course 1", 300,"CS101", "Course Description");
    auto podcaster = std::make_shared<Podcaster>("pod1", "podcaster_username", "podcaster@example.com", "password123");
    auto track4 = std::make_shared<Podcast>("Podcast 1", "Description", podcaster.get(), "Technology", 4, 120);

    playlist2.addTrack(track3);
    playlist2.addTrack(track4);

    collection.addPlaylist(playlist1);
    collection.addPlaylist(playlist2);

    CollectionStatistics stats(collection);

    CHECK_EQUAL(2, stats.getNumberOfPlaylists());
    CHECK_EQUAL(540, stats.getTotalDuration());

    auto commonTypes = stats.getMostCommonAudioTypes(5);
    CHECK_EQUAL(4, commonTypes.size());
}

TEST(CollectionStatistics_MostCommonAudioTypes) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);
    Playlist playlist("Test Playlist", user, true);

    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Genre 1", 2023);
    auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Genre 1", 2023);
    auto author1 = std::make_shared<BookAuthor>("auth1", "Author 1", "author1@example.com", "password123");
    auto author2 = std::make_shared<BookAuthor>("auth2", "Author 2", "author2@example.com", "password123");
    auto narrator1 = std::make_shared<Broadcaster>("narr1", "narrator1_username", "narrator1@example.com", "password123", "Narrator 1");
    auto narrator2 = std::make_shared<Broadcaster>("narr2", "narrator2_username", "narrator2@example.com", "password123", "Narrator 2");
    auto track3 = std::make_shared<AudioBook>("Book 1", 300, 3, author1, narrator1);
    auto track4 = std::make_shared<AudioBook>("Book 2", 250, 4, author2, narrator2);
    auto track5 = std::make_shared<AudioCourse>("Course 1", 400, "CS101", "Course Description");

    playlist.addTrack(track1);
    playlist.addTrack(track2);
    playlist.addTrack(track3);
    playlist.addTrack(track4);
    playlist.addTrack(track5);

    collection.addPlaylist(playlist);
    CollectionStatistics stats(collection);

    auto top1 = stats.getMostCommonAudioTypes(1);
    CHECK_EQUAL(1, top1.size());

    auto top2 = stats.getMostCommonAudioTypes(2);
    CHECK_EQUAL(2, top2.size());

    auto top5 = stats.getMostCommonAudioTypes(5);
    CHECK_EQUAL(3, top5.size());
}

TEST(CollectionStatistics_EmptyPlaylists) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);

    Playlist playlist1("Empty Playlist 1", user, true);
    Playlist playlist2("Empty Playlist 2", user, true);

    collection.addPlaylist(playlist1);
    collection.addPlaylist(playlist2);

    CollectionStatistics stats(collection);

    CHECK_EQUAL(2, stats.getNumberOfPlaylists());
    CHECK_EQUAL(0, stats.getTotalDuration());

    auto commonTypes = stats.getMostCommonAudioTypes(3);
    CHECK(commonTypes.empty());
}

TEST(CollectionStatistics_SingleTrackMultipleTimes) {
    RegisteredUser user("user1", "testuser", "test@example.com", "password");
    AudioCollection collection(user);
    Playlist playlist("Single Track Playlist", user, true);

    auto track = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Genre 1", 2023);
    playlist.addTrack(track);
    playlist.addTrack(track);
    playlist.addTrack(track);

    collection.addPlaylist(playlist);
    CollectionStatistics stats(collection);

            CHECK_EQUAL(1, stats.getNumberOfPlaylists());
            CHECK_EQUAL(540, stats.getTotalDuration());

    auto commonTypes = stats.getMostCommonAudioTypes(3);
            CHECK_EQUAL(1, commonTypes.size());
}