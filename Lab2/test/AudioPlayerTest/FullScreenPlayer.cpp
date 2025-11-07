#include "UnitTest++.h"
#include "../../src/AudioPlayer/FullScreenPlayer/FullScreenPlayer.h"
#include "../../src/Audio/Audio.h"

SUITE(FullScreenPlayerTest) {
    TEST(Constructor) {
        FullScreenPlayer player;
    }

    TEST(TogglePlayPause) {
        FullScreenPlayer player;
        player.togglePlayPause();
        player.togglePlayPause();
    }

    TEST(ToggleLyrics) {
        FullScreenPlayer player;
        player.toggleLyrics();
        player.toggleLyrics();
    }

    TEST(Seek_ValidPosition) {
        FullScreenPlayer player;
        player.seek(0.5f);
        player.seek(0.0f);
        player.seek(1.0f);
    }

    TEST(Seek_InvalidPosition) {
        FullScreenPlayer player;
        player.seek(-0.1f);
        player.seek(1.1f);
    }
}