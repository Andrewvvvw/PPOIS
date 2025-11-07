#include "UnitTest++.h"
#include "../../../src/User/RegisteredUser/Producer/Producer.h"
#include "../../../src/Audio/Album/MusicTrack/MusicTrack.h"

SUITE(ProducerTest) {
    TEST(Constructor) {
        Producer producer("producer1", "test_producer", "test@example.com", "password123", "Test bio");
                CHECK_EQUAL("producer1", producer.getId());
                CHECK_EQUAL("test_producer", producer.getUsername());
                CHECK_EQUAL("test@example.com", producer.getEmail());
                CHECK_EQUAL("password123", producer.getPassword());
                CHECK(producer.getTracks().empty());
    }

    TEST(AddTrack_Success) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);

        bool result = producer.addTrack(track);

                CHECK_EQUAL(true, result);
                CHECK_EQUAL(1, producer.getTracks().size());
                CHECK_EQUAL(track, producer.getTracks()[0]);
    }

    TEST(AddTrack_NullTrack) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        std::shared_ptr<MusicTrack> nullTrack = nullptr;

        bool result = producer.addTrack(nullTrack);

                CHECK_EQUAL(false, result);
                CHECK(producer.getTracks().empty());
    }

    TEST(AddTrack_DuplicateTrack) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        producer.addTrack(track);

        bool result = producer.addTrack(track);

                CHECK_EQUAL(false, result);
                CHECK_EQUAL(1, producer.getTracks().size());
    }

    TEST(RemoveTrack_Success) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Rock", 2023);
        producer.addTrack(track1);
        producer.addTrack(track2);

        bool result = producer.removeTrack(track1);

                CHECK_EQUAL(true, result);
                CHECK_EQUAL(1, producer.getTracks().size());
                CHECK_EQUAL(track2, producer.getTracks()[0]);
    }

    TEST(RemoveTrack_NullTrack) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        std::shared_ptr<MusicTrack> nullTrack = nullptr;

        bool result = producer.removeTrack(nullTrack);

                CHECK_EQUAL(false, result);
    }

    TEST(RemoveTrack_NotFound) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Rock", 2023);
        producer.addTrack(track1);

        bool result = producer.removeTrack(track2);

                CHECK_EQUAL(false, result);
                CHECK_EQUAL(1, producer.getTracks().size());
    }

    TEST(HasTrack_True) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        producer.addTrack(track);

        bool result = producer.hasTrack(track);

                CHECK_EQUAL(true, result);
    }

    TEST(HasTrack_False) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Rock", 2023);
        producer.addTrack(track1);

        bool result = producer.hasTrack(track2);

                CHECK_EQUAL(false, result);
    }

    TEST(HasTrack_NullTrack) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        std::shared_ptr<MusicTrack> nullTrack = nullptr;

        bool result = producer.hasTrack(nullTrack);

                CHECK_EQUAL(false, result);
    }

    TEST(GetTracks) {
        Producer producer("p1", "user", "test@test.com", "pass", "bio");
        auto track1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);
        auto track2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist", "Rock", 2023);
        producer.addTrack(track1);
        producer.addTrack(track2);

        const auto& tracks = producer.getTracks();

                CHECK_EQUAL(2, tracks.size());
                CHECK_EQUAL(track1, tracks[0]);
                CHECK_EQUAL(track2, tracks[1]);
    }
}