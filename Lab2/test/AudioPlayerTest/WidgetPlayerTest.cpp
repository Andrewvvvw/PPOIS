#include "UnitTest++.h"
#include "../../src/AudioPlayer/WidgetPlayer/WidgetPlayer.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"

SUITE(WidgetPlayerTest) {
    TEST(TestConstructor) {
        WidgetPlayer player;
                CHECK_EQUAL(false, player.getIsPlaying());
                CHECK_EQUAL(false, player.getIsMinimized());
                CHECK_EQUAL(70.0f, player.getVolume());
    }

    TEST(TestTogglePlayPause_FromPaused) {
        WidgetPlayer player;
                CHECK_EQUAL(false, player.getIsPlaying());

        player.togglePlayPause();
                CHECK_EQUAL(true, player.getIsPlaying());
    }

    TEST(TestTogglePlayPause_FromPlaying) {
        WidgetPlayer player;
        player.togglePlayPause();
                CHECK_EQUAL(true, player.getIsPlaying());

        player.togglePlayPause();
                CHECK_EQUAL(false, player.getIsPlaying());
    }

    TEST(TestToggleMinimize_FromMaximized) {
        WidgetPlayer player;
                CHECK_EQUAL(false, player.getIsMinimized());

        player.toggleMinimize();
                CHECK_EQUAL(true, player.getIsMinimized());
    }

    TEST(TestToggleMinimize_FromMinimized) {
        WidgetPlayer player;
        player.toggleMinimize();
                CHECK_EQUAL(true, player.getIsMinimized());

        player.toggleMinimize();
                CHECK_EQUAL(false, player.getIsMinimized());
    }

    TEST(TestSetVolume_ValidValue) {
        WidgetPlayer player;
        player.setVolume(50.0f);
                CHECK_EQUAL(50.0f, player.getVolume());
    }

    TEST(TestSetVolume_MinValue) {
        WidgetPlayer player;
        player.setVolume(0.0f);
                CHECK_EQUAL(0.0f, player.getVolume());
    }

    TEST(TestSetVolume_MaxValue) {
        WidgetPlayer player;
        player.setVolume(100.0f);
                CHECK_EQUAL(100.0f, player.getVolume());
    }

    TEST(TestSetVolume_BelowMin) {
        WidgetPlayer player;
        player.setVolume(70.0f);
        player.setVolume(-10.0f);
                CHECK_EQUAL(70.0f, player.getVolume());
    }

    TEST(TestSetVolume_AboveMax) {
        WidgetPlayer player;
        player.setVolume(70.0f);
        player.setVolume(150.0f);
                CHECK_EQUAL(70.0f, player.getVolume());
    }

    TEST(TestGetCurrentAudio_DefaultConstruction) {
        WidgetPlayer player;
        try {
            player.getCurrentAudio();
                    CHECK(false);
        } catch (const std::exception&) {
                    CHECK(true);
        }
    }

    TEST(TestGetCurrentAudio_AfterSettingAudio) {
        WidgetPlayer player;
        auto testTrack = std::make_shared<MusicTrack>(
                "Test Track",
                180,
                1,
                "Test Artist",
                "Pop",
                2023
        );
        player.setCurrentAudio(testTrack);

        const Audio& currentAudio = player.getCurrentAudio();
                CHECK_EQUAL("Test Track", currentAudio.getName());
                CHECK_EQUAL(180, currentAudio.getDuration());
                CHECK_EQUAL(1, currentAudio.getCoverID());
    }

    TEST(TestGetCurrentAudio_NullAudio) {
        WidgetPlayer player;
        player.setCurrentAudio(nullptr);

        bool exceptionThrown = false;
        try {
            player.getCurrentAudio();
        } catch (const std::runtime_error&) {
            exceptionThrown = true;
        }
                CHECK(exceptionThrown);
    }
}