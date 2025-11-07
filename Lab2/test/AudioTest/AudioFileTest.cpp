#include "UnitTest++.h"

#include "../../src/Audio/AudioFile/AudioFile.h"

SUITE(AudioFileTest) {
    TEST(ConstructorAndGetters) {
        AudioFile file("test.mp3", 1024, "MP3");
                CHECK_EQUAL("test.mp3", file.getFilePath());
                CHECK_EQUAL(1024, file.getFileSize());
                CHECK_EQUAL("MP3", file.getFormat());
    }

    TEST(ValidateWithZeroSize) {
        AudioFile file("test.mp3", 0, "MP3");
                CHECK(!file.validate());
    }

    TEST(ValidateWithUnsupportedFormat) {
        AudioFile file("test.ogg", 1024, "OGG");
                CHECK(!file.validate());
    }

    TEST(ValidateWithSupportedFormats) {
        AudioFile mp3File("test.mp3", 1024, "MP3");
                CHECK(mp3File.validate());

        AudioFile wavFile("test.wav", 2048, "WAV");
                CHECK(wavFile.validate());

        AudioFile aacFile("test.aac", 3072, "AAC");
                CHECK(aacFile.validate());

        AudioFile flacFile("test.flac", 4096, "FLAC");
                CHECK(flacFile.validate());
    }

    TEST(ValidateWithEmptyFormat) {
        AudioFile file("test.none", 1024, "");
                CHECK(!file.validate());
    }

    TEST(ValidateWithMixedCaseFormat) {
        AudioFile file1("test1.mp3", 1024, "mp3");
                CHECK(!file1.validate());

        AudioFile file2("test2.mp3", 1024, "Mp3");
                CHECK(!file2.validate());
    }

    TEST(ValidateWithSpecialCharactersInPath) {
        AudioFile file1("C:\\\\music\\\\test file.mp3", 1024, "MP3");
                CHECK(file1.validate());

        AudioFile file2("/home/user/music/test-file.mp3", 1024, "MP3");
                CHECK(file2.validate());
    }
}