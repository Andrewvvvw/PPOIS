#include "UnitTest++.h"
#include "../../src/Exceptions/Exceptions.h"

SUITE(ExceptionTests) {
    TEST(TestBaseException) {
        Exception ex("Test message");
        CHECK_EQUAL("Test message", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectYear) {
        ExceptionIncorrectYear ex("Invalid year");
        CHECK_EQUAL("Invalid year", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectDuration) {
        ExceptionIncorrectDuration ex("Invalid duration");
        CHECK_EQUAL("Invalid duration", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectPassword) {
        ExceptionIncorrectPassword ex("Invalid password");
        CHECK_EQUAL("Invalid password", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectEmail) {
        ExceptionIncorrectEmail ex("Invalid email");
        CHECK_EQUAL("Invalid email", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectUsername) {
        ExceptionIncorrectUsername ex("Invalid username");
        CHECK_EQUAL("Invalid username", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectAudioName) {
        ExceptionIncorrectAudioName ex("Invalid audio name");
        CHECK_EQUAL("Invalid audio name", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectArtistName) {
        ExceptionIncorrectArtistName ex("Invalid artist name");
        CHECK_EQUAL("Invalid artist name", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectAlbumTitle) {
        ExceptionIncorrectAlbumTitle ex("Invalid album title");
        CHECK_EQUAL("Invalid album title", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectTrack) {
        ExceptionIncorrectTrack ex("Invalid track");
        CHECK_EQUAL("Invalid track", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectChapterNumber) {
        ExceptionIncorrectChapterNumber ex("Invalid chapter number");
        CHECK_EQUAL("Invalid chapter number", std::string(ex.what()));
    }

    TEST(TestExceptionIncorrectAudioBookChapters) {
        ExceptionIncorrectAudioBookChapters ex("Invalid audiobook chapters");
        CHECK_EQUAL("Invalid audiobook chapters", std::string(ex.what()));
    }

    TEST(TestExceptionNotEnoughMoney) {
        ExceptionNotEnoughMoney ex("Not enough money");
        CHECK_EQUAL("Not enough money", std::string(ex.what()));
    }

    TEST(TestExceptionMessageCopy) {
        Exception ex1("Original message");
        Exception ex2 = ex1;
        CHECK_EQUAL(std::string(ex1.what()), std::string(ex2.what()));
    }

    TEST(TestExceptionDerivedClassMessage) {
        ExceptionIncorrectYear yearEx("Year error");
        std::exception& baseEx = yearEx;
        CHECK_EQUAL("Year error", std::string(baseEx.what()));
    }
}
