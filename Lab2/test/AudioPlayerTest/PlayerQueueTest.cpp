#include "UnitTest++.h"
#include "../../src/AudioPlayer/PlayerQueue/PlayerQueue.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"

SUITE(PlayerQueueTest) {
    TEST(Constructor_DefaultValues) {
        PlayerQueue queue;
        CHECK_EQUAL(0, queue.getCurrentIndex());
        CHECK_EQUAL(false, queue.getIsLooped());
        CHECK_EQUAL(100, queue.getMaxQueueSize());
    }

    TEST(AddToQueue_SingleItem) {
        PlayerQueue queue;
        auto audio = std::make_shared<MusicTrack>("Test Track", 180, 1, "Artist", "Pop", 2023);
        queue.addToQueue(audio);
        CHECK_EQUAL(1, queue.getQueueSize());
    }

    TEST(AddToQueue_NullItem) {
        PlayerQueue queue;
        std::shared_ptr<Audio> nullAudio = nullptr;
        queue.addToQueue(nullAudio);
        CHECK_EQUAL(0, queue.getQueueSize());
    }

    TEST(AddToQueue_MaxSize) {
        PlayerQueue queue;
        for (int i = 0; i < 150; ++i) {
            auto audio = std::make_shared<MusicTrack>("Track " + std::to_string(i), 180, i, "Artist", "Pop", 2023);
            queue.addToQueue(audio);
        }
        CHECK_EQUAL(100, queue.getQueueSize());
    }

    TEST(RemoveFromQueue_ValidIndex) {
        PlayerQueue queue;
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        queue.removeFromQueue(0);
        CHECK_EQUAL(1, queue.getQueueSize());
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(RemoveFromQueue_InvalidIndex) {
        PlayerQueue queue;
        auto audio = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        queue.addToQueue(audio);

        queue.removeFromQueue(5);
        CHECK_EQUAL(1, queue.getQueueSize());
    }

    TEST(RemoveFromQueue_CurrentIndexAdjustment) {
        PlayerQueue queue;
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        queue.getNext();
        queue.removeFromQueue(0);
        CHECK_EQUAL(0, queue.getCurrentIndex());

        queue.removeFromQueue(0);
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(GetNext_EmptyQueue) {
        PlayerQueue queue;
        auto result = queue.getNext();
        CHECK(result == nullptr);
    }

    TEST(GetNext_SingleItem) {
        PlayerQueue queue;
        auto audio = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        queue.addToQueue(audio);

        auto result = queue.getNext();
        CHECK(result == audio);
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(GetNext_MultipleItems) {
        PlayerQueue queue;
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        auto result1 = queue.getNext();
        CHECK(!(result1 == audio2));
        CHECK_EQUAL(1, queue.getCurrentIndex());

        auto result2 = queue.getNext();
        CHECK(result2 == audio2);
        CHECK_EQUAL(1, queue.getCurrentIndex());
    }

    TEST(GetNext_Looped) {
        PlayerQueue queue;
        queue.setLooped(true);
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        queue.getNext();
        auto result = queue.getNext();
        CHECK(!(result == audio1));
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(GetPrevious_EmptyQueue) {
        PlayerQueue queue;
        auto result = queue.getPrevious();
        CHECK(result == nullptr);
    }

    TEST(GetPrevious_SingleItem) {
        PlayerQueue queue;
        auto audio = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        queue.addToQueue(audio);

        auto result = queue.getPrevious();
        CHECK(result == audio);
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(GetPrevious_MultipleItems) {
        PlayerQueue queue;
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        queue.getNext();
        auto result = queue.getPrevious();
        CHECK(result == audio1);
        CHECK_EQUAL(0, queue.getCurrentIndex());
    }

    TEST(GetPrevious_Looped) {
        PlayerQueue queue;
        queue.setLooped(true);
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Pop", 2023);
        queue.addToQueue(audio1);
        queue.addToQueue(audio2);

        auto result = queue.getPrevious();
        CHECK(result == audio2);
        CHECK_EQUAL(1, queue.getCurrentIndex());
    }

    TEST(SetAndGetLoop) {
        PlayerQueue queue;
        queue.setLooped(true);
        CHECK(queue.getIsLooped());

        queue.setLooped(false);
        CHECK(!queue.getIsLooped());
    }

    TEST(SetAndGetMaxQueueSize) {
        PlayerQueue queue;
        queue.setMaxQueueSize(50);
        CHECK_EQUAL(50, queue.getMaxQueueSize());
    }
}
