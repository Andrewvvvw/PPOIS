#include "UnitTest++.h"
#include "../../src/AudioPlayer/PlayStatistics/PlayStatistics.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include <ctime>

SUITE(PlayStatisticsTest) {
    TEST(Constructor_InitializesTotalPlaysToZero) {
        PlayStatistics stats;
        CHECK_EQUAL(0, stats.getTotalPlays());
    }

    TEST(RecordPlay_IncrementsPlayCount) {
        PlayStatistics stats;
        MusicTrack track("Test Track", 180, 12345, "Test Artist", "Pop", 2023);

        stats.recordPlay(track);
        CHECK_EQUAL(1, stats.getPlayCount(track.getCoverID()));
        CHECK_EQUAL(1, stats.getTotalPlays());

        stats.recordPlay(track);
        CHECK_EQUAL(2, stats.getPlayCount(track.getCoverID()));
        CHECK_EQUAL(2, stats.getTotalPlays());
    }

    TEST(RecordPlay_UpdatesLastPlayedTimestamp) {
        PlayStatistics stats;
        MusicTrack track1("Track 1", 180, 1, "Artist 1", "Pop", 2023);
        MusicTrack track2("Track 2", 200, 2, "Artist 2", "Rock", 2023);

        const time_t before = std::time(nullptr);
        stats.recordPlay(track1);
        const time_t after = std::time(nullptr);

        const time_t lastPlayed = stats.getLastPlayed(track1.getCoverID());
        CHECK(before <= lastPlayed && lastPlayed <= after);

        CHECK_EQUAL(0, stats.getLastPlayed(9999));
    }

    TEST(GetPlayCount_ReturnsZeroForUnplayedTracks) {
        PlayStatistics stats;
        MusicTrack track("Test Track", 180, 12345, "Test Artist", "Pop", 2023);

        CHECK_EQUAL(0, stats.getPlayCount(track.getCoverID()));
        CHECK_EQUAL(0, stats.getPlayCount(9999));
    }

    TEST(MultipleTracks_IndependentPlayCounts) {
        PlayStatistics stats;
        MusicTrack track1("Track 1", 180, 1, "Artist 1", "Pop", 2023);
        MusicTrack track2("Track 2", 200, 2, "Artist 2", "Rock", 2023);

        stats.recordPlay(track1);
        stats.recordPlay(track1);
        stats.recordPlay(track2);

        CHECK_EQUAL(2, stats.getPlayCount(track1.getCoverID()));
        CHECK_EQUAL(1, stats.getPlayCount(track2.getCoverID()));
        CHECK_EQUAL(3, stats.getTotalPlays());
    }

    TEST(GetLastPlayed_ReturnsZeroForUnplayedTracks) {
        PlayStatistics stats;
        MusicTrack track("Test Track", 180, 12345, "Test Artist", "Pop", 2023);

        CHECK_EQUAL(0, stats.getLastPlayed(track.getCoverID()));
        CHECK_EQUAL(0, stats.getLastPlayed(9999));
    }

    TEST(GetTotalPlays_ReturnsCorrectCount) {
        PlayStatistics stats;
        MusicTrack track1("Track 1", 180, 1, "Artist 1", "Pop", 2023);
        MusicTrack track2("Track 2", 200, 2, "Artist 2", "Rock", 2023);

        CHECK_EQUAL(0, stats.getTotalPlays());

        stats.recordPlay(track1);
        CHECK_EQUAL(1, stats.getTotalPlays());

        stats.recordPlay(track1);
        CHECK_EQUAL(2, stats.getTotalPlays());

        stats.recordPlay(track2);
        CHECK_EQUAL(3, stats.getTotalPlays());
    }

    TEST(RecordPlay_WithSameTrackMultipleTimes) {
        PlayStatistics stats;
        MusicTrack track("Test Track", 180, 12345, "Test Artist", "Pop", 2023);

        for (int i = 0; i < 10; ++i) {
            stats.recordPlay(track);
            CHECK_EQUAL(i + 1, stats.getPlayCount(track.getCoverID()));
            CHECK_EQUAL(i + 1, stats.getTotalPlays());
        }
    }

    TEST(RecordPlay_WithDifferentTracks) {
        PlayStatistics stats;

        for (int i = 0; i < 10; ++i) {
            MusicTrack track("Track " + std::to_string(i), 180, i, "Artist " + std::to_string(i), "Genre", 2023);
            stats.recordPlay(track);
            CHECK_EQUAL(1, stats.getPlayCount(track.getCoverID()));
            CHECK_EQUAL(i + 1, stats.getTotalPlays());
        }
    }
}
