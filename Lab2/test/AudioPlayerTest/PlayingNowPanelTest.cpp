#include "UnitTest++.h"
#include "../../src/AudioPlayer/PlayingNowPanel/PlayingNowPanel.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"

SUITE(PlayingNowPanelTest) {
    TEST(Constructor_DefaultValues) {
        PlayingNowPanel panel;
                CHECK(panel.getCurrentTrack() == nullptr);
                CHECK_EQUAL(0.0f, panel.getProgress());
                CHECK(panel.getArtistName().empty());
                CHECK(panel.getTrackName().empty());
                CHECK_EQUAL(0, panel.getCoverID());
    }

    TEST(UpdateTrackInfo_ValidTrack) {
        PlayingNowPanel panel;
        auto track = std::make_shared<MusicTrack>("Test Track", 183, 1, "Test Artist", "Pop", 2023);

        panel.updateTrackInfo(track);

        auto currentTrack = panel.getCurrentTrack();
                CHECK(currentTrack != nullptr);
                CHECK_EQUAL("Test Track", panel.getTrackName());
                CHECK_EQUAL("Test Artist", panel.getArtistName());
                CHECK_EQUAL(1, panel.getCoverID());
    }

    TEST(UpdateTrackInfo_NullTrack) {
        PlayingNowPanel panel;
        auto track = std::make_shared<MusicTrack>("Test Track", 183, 1, "Test Artist", "Pop", 2023);
        panel.updateTrackInfo(track);

        panel.updateTrackInfo(nullptr);

                CHECK(panel.getCurrentTrack() == nullptr);
                CHECK(panel.getTrackName().empty());
                CHECK(panel.getArtistName().empty());
                CHECK_EQUAL(0, panel.getCoverID());
    }

    TEST(SetProgress_ValidValues) {
        PlayingNowPanel panel;

        panel.setProgress(0.0f);
                CHECK_EQUAL(0.0f, panel.getProgress());

        panel.setProgress(0.5f);
                CHECK_EQUAL(0.5f, panel.getProgress());

        panel.setProgress(1.0f);
                CHECK_EQUAL(1.0f, panel.getProgress());
    }

    TEST(SetProgress_InvalidValues) {
        PlayingNowPanel panel;

        panel.setProgress(-0.1f);
                CHECK_EQUAL(0.0f, panel.getProgress());

        panel.setProgress(1.1f);
                CHECK_EQUAL(0.0f, panel.getProgress());

        panel.setProgress(0.5f);
        panel.setProgress(-1.0f);
                CHECK_EQUAL(0.5f, panel.getProgress());

        panel.setProgress(2.0f);
                CHECK_EQUAL(0.5f, panel.getProgress());
    }

    TEST(GetFormattedProgress_NoTrack) {
        PlayingNowPanel panel;
                CHECK_THROW(panel.getFormattedProgress(), std::runtime_error);
    }

    TEST(GetFormattedProgress_ValidTrack) {
        PlayingNowPanel panel;
        auto track = std::make_shared<MusicTrack>("Test Track", 125, 1, "Test Artist", "Pop", 2023);
        panel.updateTrackInfo(track);

        panel.setProgress(0.0f);
                CHECK_EQUAL("00:00 / 02:05", panel.getFormattedProgress());

        panel.setProgress(0.5f);
                CHECK_EQUAL("01:02 / 02:05", panel.getFormattedProgress());

        panel.setProgress(1.0f);
                CHECK_EQUAL("02:05 / 02:05", panel.getFormattedProgress());
    }

    TEST(GetFormattedProgress_EdgeCases) {
        PlayingNowPanel panel;
        auto track = std::make_shared<MusicTrack>("Test Track", 0, 1, "Test Artist", "Pop", 2023);
        panel.updateTrackInfo(track);

        panel.setProgress(0.0f);
                CHECK_EQUAL("00:00 / 00:00", panel.getFormattedProgress());

        track = std::make_shared<MusicTrack>("Test Track", 3599, 1, "Test Artist", "Pop", 2023);
        panel.updateTrackInfo(track);
        panel.setProgress(0.5f);
                CHECK_EQUAL("29:59 / 59:59", panel.getFormattedProgress());
    }

    TEST(GetCurrentTrack) {
        PlayingNowPanel panel;
        auto track = std::make_shared<MusicTrack>("Test Track", 180, 1, "Test Artist", "Pop", 2023);

        panel.updateTrackInfo(track);
        auto currentTrack = panel.getCurrentTrack();

                CHECK(currentTrack != nullptr);
                CHECK_EQUAL("Test Track", currentTrack->getName());

        panel.updateTrackInfo(nullptr);
                CHECK(panel.getCurrentTrack() == nullptr);
    }
}