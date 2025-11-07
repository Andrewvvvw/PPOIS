#include "UnitTest++.h"
#include "../../src/AudioPlayer/AudioSettings/AudioSettings.h"

SUITE(AudioSettingsTest) {
    TEST(Constructor_DefaultValues) {
        AudioSettings settings;

                CHECK_EQUAL(70, settings.getVolume());
                CHECK_CLOSE(1.0f, settings.getPlaybackSpeed(), 0.001f);
                CHECK_EQUAL(false, settings.getRepeatOn());
                CHECK_EQUAL(false, settings.getMuted());
    }

    TEST(SetVolume_ValidRange) {
        AudioSettings settings;

        settings.setVolume(50);
                CHECK_EQUAL(50, settings.getVolume());

        settings.setVolume(0);
                CHECK_EQUAL(0, settings.getVolume());

        settings.setVolume(100);
                CHECK_EQUAL(100, settings.getVolume());
    }

    TEST(SetVolume_InvalidRange) {
        AudioSettings settings;

        settings.setVolume(101);
                CHECK_EQUAL(70, settings.getVolume());

        settings.setVolume(-1);
                CHECK_EQUAL(70, settings.getVolume());
    }

    TEST(ToggleMute) {
        AudioSettings settings;

        settings.toggleMute();
                CHECK_EQUAL(true, settings.getMuted());

        settings.toggleMute();
                CHECK_EQUAL(false, settings.getMuted());
    }

    TEST(ToggleRepeat) {
        AudioSettings settings;

        settings.toggleRepeat();
                CHECK_EQUAL(true, settings.getRepeatOn());

        settings.toggleRepeat();
                CHECK_EQUAL(false, settings.getRepeatOn());
    }

    TEST(SetPlaybackSpeed_ValidRange) {
        AudioSettings settings;

        settings.setPlaybackSpeed(0.5f);
                CHECK_CLOSE(0.5f, settings.getPlaybackSpeed(), 0.001f);

        settings.setPlaybackSpeed(2.0f);
                CHECK_CLOSE(2.0f, settings.getPlaybackSpeed(), 0.001f);
    }

    TEST(SetPlaybackSpeed_InvalidRange) {
        AudioSettings settings;

        settings.setPlaybackSpeed(-0.1f);
                CHECK_CLOSE(1.0f, settings.getPlaybackSpeed(), 0.001f);

        settings.setPlaybackSpeed(3.1f);
                CHECK_CLOSE(1.0f, settings.getPlaybackSpeed(), 0.001f);
    }
}
