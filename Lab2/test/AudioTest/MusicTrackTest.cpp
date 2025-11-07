#include "UnitTest++.h"
#include "../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/User/RegisteredUser/SongWriter/SongWriter.h"
#include "../../src/Exceptions/Exceptions.h"
#include <memory>

SUITE(MusicTrackTest) {
    TEST(ConstructorAndGetters) {
        MusicTrack track("Test Track", 180, 1, "Test Artist", "Rock", 2020);

        CHECK_EQUAL("Test Track", track.getName());
        CHECK_EQUAL(180, track.getDuration());
        CHECK_EQUAL(1, track.getCoverID());
        CHECK_EQUAL("Test Artist", track.getAuthor());
        CHECK_EQUAL("Rock", track.getGenre());
        CHECK_EQUAL(2020, track.getReleaseYear());
        CHECK(!track.getSongWriter());
    }

    TEST(UpdateGenre) {
        MusicTrack track("Test Track", 180, 1, "Test Artist", "Rock", 2020);

        track.updateGenre("Pop");
        CHECK_EQUAL("Pop", track.getGenre());

        track.updateGenre("Jazz");
        CHECK_EQUAL("Jazz", track.getGenre());

        track.updateGenre("");
        CHECK_EQUAL("", track.getGenre());
    }

    TEST(IsClassic) {
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        int currentYear = timeinfo->tm_year + 1900;

        MusicTrack oldTrack("Old Track", 180, 1, "Old Artist", "Classic Rock", currentYear - 30);
        CHECK(oldTrack.isClassic());

        MusicTrack newTrack("New Track", 180, 2, "New Artist", "Pop", currentYear - 10);
        CHECK(!newTrack.isClassic());

        MusicTrack boundaryTrack("Boundary Track", 180, 3, "Boundary Artist", "Jazz", currentYear - 25);
        CHECK(boundaryTrack.isClassic());
    }

    TEST(EdgeCases) {
        CHECK_THROW(MusicTrack minValues("", 0, 0, "", "", 1900),ExceptionIncorrectAudioName);
    }

    TEST(EmptyData) {
        MusicTrack minValues("track1", 0, 0, "", "", 1900);
        CHECK_EQUAL("track1", minValues.getName());
        CHECK_EQUAL(0, minValues.getDuration());
        CHECK_EQUAL(0, minValues.getCoverID());
        CHECK_EQUAL("", minValues.getAuthor());
        CHECK_EQUAL("", minValues.getGenre());
        CHECK_EQUAL(1900, minValues.getReleaseYear());
    }

    TEST(SongWriterAssociation) {
        auto writer = std::make_shared<SongWriter>("user123", "johndoe", "john@example.com", "password123", "Professional musician");

        auto track = std::make_shared<MusicTrack>("Test Track", 180, 1, "Test Artist", "Rock", 2020);

        bool addResult = writer->addTrack(track);
        CHECK(addResult);

        bool hasTrack = writer->hasTrack(track);
        CHECK(hasTrack);

        const auto& writerTracks = writer->getTracks();
        CHECK_EQUAL(1, writerTracks.size());
        if (!writerTracks.empty()) {
            CHECK_EQUAL("Test Track", writerTracks[0]->getName());
            CHECK_EQUAL("Test Artist", writerTracks[0]->getAuthor());
        }
    }
}
