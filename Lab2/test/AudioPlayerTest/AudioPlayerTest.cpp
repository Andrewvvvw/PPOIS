#include "UnitTest++.h"
#include "../../src/AudioPlayer/AudioPlayer.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include <memory>

TEST(AudioPlayer_defaultConstructor) {
    AudioPlayer player;
    CHECK_EQUAL(false, player.isCurrentlyPlaying());
    CHECK_EQUAL(0.0f, player.getPlaybackProgress());
    CHECK(nullptr == player.getCurrentTrack());
}

TEST(AudioPlayer_TogglePlayPause) {
    AudioPlayer player;

    player.togglePlayPause();
    CHECK_EQUAL(true, player.isCurrentlyPlaying());

    player.togglePlayPause();
    CHECK_EQUAL(false, player.isCurrentlyPlaying());
}

TEST(AudioPlayer_AddToQueue) {
    AudioPlayer player;
    auto track = std::make_shared<MusicTrack>("Test Track", 180, 1, "Test Artist", "Pop", 2023);

    player.addToQueue(track);
    CHECK(nullptr == player.getCurrentTrack());
}

TEST(AudioPlayer_PlayNextEmptyQueue) {
    AudioPlayer player;
    player.playNext();
    CHECK(nullptr == player.getCurrentTrack());
}

TEST(AudioPlayer_PlayPreviousEmptyHistory) {
    AudioPlayer player;
    player.playPrevious();
    CHECK(nullptr == player.getCurrentTrack());
}

TEST(AudioPlayer_PlayNextWithQueue) {
    AudioPlayer player;
    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
    auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2023);

    player.addToQueue(track1);
    player.addToQueue(track2);

    player.playNext();
    auto firstTrack = player.getCurrentTrack();
            CHECK(firstTrack != nullptr);
    if (firstTrack) {
                CHECK_EQUAL("Track 1", firstTrack->getName());
    }

    player.playNext();
    auto secondTrack = player.getCurrentTrack();
            CHECK(secondTrack != nullptr);
    if (secondTrack) {
                CHECK_EQUAL("Track 2", secondTrack->getName());
    }

    player.playNext();
    auto stillSecondTrack = player.getCurrentTrack();
            CHECK(stillSecondTrack != nullptr);
    if (stillSecondTrack) {
                CHECK_EQUAL("Track 2", stillSecondTrack->getName());
    }
}

TEST(AudioPlayer_PlayPreviousWithHistory) {
    AudioPlayer player;
    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
    auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2023);

    player.addToQueue(track1);
    player.addToQueue(track2);

    player.playNext();
    auto firstTrack = player.getCurrentTrack();
            CHECK(firstTrack != nullptr);
    if (firstTrack) {
                CHECK_EQUAL("Track 1", firstTrack->getName());
    }

    player.playNext();
    auto secondTrack = player.getCurrentTrack();
            CHECK(secondTrack != nullptr);
    if (secondTrack) {
                CHECK_EQUAL("Track 2", secondTrack->getName());
    }

    player.playPrevious();
    auto previousTrack = player.getCurrentTrack();
            CHECK(previousTrack != nullptr);
    if (previousTrack) {
                CHECK_EQUAL("Track 1", previousTrack->getName());
    }

    player.playPrevious();
    auto stillFirstTrack = player.getCurrentTrack();
            CHECK(stillFirstTrack != nullptr);
    if (stillFirstTrack) {
                CHECK_EQUAL("Track 1", stillFirstTrack->getName());
    }
}

TEST(AudioPlayer_RemoveFromQueue) {
    AudioPlayer player;
    auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
    auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2023);

    player.addToQueue(track1);
    player.addToQueue(track2);
    player.playNext();
    auto firstTrack = player.getCurrentTrack();
            CHECK(firstTrack != nullptr);
    if (firstTrack) {
                CHECK_EQUAL("Track 1", firstTrack->getName());
    }

    player.removeFromQueue(0);

    auto currentTrack = player.getCurrentTrack();
            CHECK(currentTrack != nullptr);
    if (currentTrack) {
                CHECK_EQUAL("Track 1", currentTrack->getName());
    }
}

TEST(AudioPlayer_RemoveFromQueueInvalidIndex) {
    AudioPlayer player;
    auto track = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
    player.addToQueue(track);

    bool exceptionThrown = false;
    try {
        player.removeFromQueue(1);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    CHECK(!exceptionThrown);
}

TEST(AudioPlayer_GetPlaybackProgress) {
    AudioPlayer player;
    auto track = std::make_shared<MusicTrack>("Test Track", 200, 1, "Test Artist", "Pop", 2023);
    player.addToQueue(track);

    player.playNext();

    player.togglePlayPause();
    float progress = player.getPlaybackProgress();

    CHECK_EQUAL(0.0f, progress);
}