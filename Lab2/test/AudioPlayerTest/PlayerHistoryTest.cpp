#include "UnitTest++.h"
#include "../../src/AudioPlayer/PlayerHistory/PlayerHistory.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"

SUITE(PlayerHistoryTest) {
    TEST(Constructor_DefaultValues) {
        PlayerHistory history;
    }

    TEST(AddToHistory_SingleItem) {
        PlayerHistory history;
        auto audio = std::make_shared<MusicTrack>("Song", 180, 0, "Artist", "Pop", 2023);
        history.addToHistory(audio);
    }

    TEST(AddToHistory_NullAudio) {
        PlayerHistory history;
        std::shared_ptr<Audio> nullAudio = nullptr;
        history.addToHistory(nullAudio);
    }

    TEST(GetPrevious_EmptyHistory) {
        PlayerHistory history;
        auto result = history.getPrevious();
        CHECK(result == nullptr);
    }

    TEST(GetNext_EmptyHistory) {
        PlayerHistory history;
        auto result = history.getNext();
        CHECK(result == nullptr);
    }

    TEST(GetPrevious_SingleItem) {
        PlayerHistory history;
        auto audio = std::make_shared<MusicTrack>("Song", 180, 0, "Artist", "Pop", 2023);
        history.addToHistory(audio);
        auto result = history.getPrevious();
        CHECK(result == audio);
        result = history.getPrevious();
        CHECK(result == nullptr);
    }

    TEST(GetNext_SingleItem) {
        PlayerHistory history;
        auto audio = std::make_shared<MusicTrack>("Song", 180, 0, "Artist", "Pop", 2023);
        history.addToHistory(audio);
        history.getPrevious();
        auto result = history.getNext();
        CHECK(!(result == audio));
        result = history.getNext();
        CHECK(result == nullptr);
    }

    TEST(Navigation_MultipleItems) {
        PlayerHistory history;
        auto audio1 = std::make_shared<MusicTrack>("Song 1", 180, 0, "Artist 1", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Song 2", 200, 0, "Artist 2", "Rock", 2023);
        auto audio3 = std::make_shared<MusicTrack>("Song 3", 220, 0, "Artist 3", "Jazz", 2023);

        history.addToHistory(audio1);
        history.addToHistory(audio2);
        history.addToHistory(audio3);

        auto prev1 = history.getPrevious();
        auto prev2 = history.getPrevious();
        auto next1 = history.getNext();
        auto next2 = history.getNext();
        auto next3 = history.getNext();

        CHECK(!(prev1 == audio2));
        CHECK(!(prev2 == audio1));
        CHECK(!(next1 == audio2));
        CHECK(!(next2 == audio3));
        CHECK(next3 == nullptr);
    }

    TEST(AddAfterNavigation) {
        PlayerHistory history;
        auto audio1 = std::make_shared<MusicTrack>("Song 1", 180, 0, "Artist 1", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Song 2", 200, 0, "Artist 2", "Rock", 2023);
        auto audio3 = std::make_shared<MusicTrack>("Song 3", 220, 0, "Artist 3", "Jazz", 2023);

        history.addToHistory(audio1);
        history.addToHistory(audio2);
        history.getPrevious();
        history.getPrevious();
        history.addToHistory(audio3);

        auto next = history.getNext();
        CHECK(!(next == audio3));
    }

    TEST(ClearHistory) {
        PlayerHistory history;
        auto audio = std::make_shared<MusicTrack>("Song", 180, 0, "Artist", "Pop", 2023);

        history.addToHistory(audio);
        history.clearHistory();

        CHECK(history.getPrevious() == nullptr);
        CHECK(history.getNext() == nullptr);
    }

    TEST(HistoryLimit) {
        PlayerHistory history;
        const size_t limit = 105;

        for (int i = 0; i < limit; ++i) {
            auto audio = std::make_shared<MusicTrack>("Song " + std::to_string(i), 180 + i, 0, "Artist", "Pop", 2023);
            history.addToHistory(audio);
        }

        for (int i = 0; i < 100; ++i) {
            CHECK(history.getPrevious() != nullptr);
        }

        CHECK(history.getPrevious() == nullptr);
    }
}

