#include "UnitTest++.h"
#include "../../src/AudioCollection/AudioUploader/AudioUploader.h"
#include "../../src/Audio/AudioFile/AudioFile.h"

SUITE(AudioUploaderTest) {
    TEST(ConstructorInitialization) {
        std::vector<std::string> formats = {"mp3", "wav", "aac"};
        AudioUploader uploader("/uploads", 1024, formats);

                CHECK_EQUAL("/uploads", uploader.getUploadDirectory());
                CHECK_EQUAL(1024, uploader.getMaxFileSizeKB());
                CHECK_EQUAL(3, uploader.getAllowedFormats().size());
    }

    TEST(ValidateFileWithValidFormatAndSize) {
        std::vector<std::string> formats = {"mp3", "wav", "aac"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.mp3", 512, "mp3");

                CHECK(uploader.validateFile(file));
    }

    TEST(ValidateFileWithInvalidFormat) {
        std::vector<std::string> formats = {"mp3", "wav", "aac"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.ogg", 512, "ogg");

                CHECK(!uploader.validateFile(file));
    }

    TEST(ValidateFileWithExactMaxSize) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.mp3", 1024, "mp3");

                CHECK(uploader.validateFile(file));
    }

    TEST(ValidateFileExceedingMaxSize) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.mp3", 2048, "mp3");

                CHECK(!uploader.validateFile(file));
    }

    TEST(UploadValidAudioFile) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.mp3", 512, "mp3");

                CHECK(uploader.uploadAudio(file));
    }

    TEST(UploadInvalidAudioFile) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.ogg", 512, "ogg");

                CHECK(!uploader.uploadAudio(file));
    }

    TEST(EmptyFormatsList) {
        std::vector<std::string> formats;
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.mp3", 512, "mp3");

                CHECK(!uploader.validateFile(file));
    }

    TEST(FileWithNoExtension) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test", 512, "");

                CHECK(!uploader.validateFile(file));
    }

    TEST(ZeroMaxSize) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 0, formats);
        AudioFile file("test.mp3", 1, "mp3");

                CHECK(!uploader.validateFile(file));
    }

    TEST(FileWithMultipleDotsInName) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.file.mp3", 512, "mp3");

                CHECK(uploader.validateFile(file));
    }

    TEST(FileWithUppercaseExtension) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file("test.MP3", 512, "MP3");

                CHECK(!uploader.validateFile(file));
    }

    TEST(FileWithDifferentCaseFormat) {
        std::vector<std::string> formats = {"Mp3", "WAV"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file1("test.mp3", 512, "mp3");
        AudioFile file2("test.wav", 512, "WAV");

                CHECK(!uploader.validateFile(file1));
                CHECK(!uploader.validateFile(file2));
    }

    TEST(FileWithLeadingDot) {
        std::vector<std::string> formats = {"mp3"};
        AudioUploader uploader("/uploads", 1024, formats);
        AudioFile file(".mp3", 512, "mp3");

                CHECK(uploader.validateFile(file));
    }
}