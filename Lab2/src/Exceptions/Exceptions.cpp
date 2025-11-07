#include "Exceptions.h"

Exception::Exception(const std::string message) : message(message) {}
const char *Exception::what() const noexcept {
    return this->message.c_str();
}
ExceptionIncorrectArtistName::ExceptionIncorrectArtistName(const std::string message) : Exception(message) {}
ExceptionIncorrectAlbumTitle::ExceptionIncorrectAlbumTitle(const std::string message) : Exception(message) {}
ExceptionIncorrectTrack::ExceptionIncorrectTrack(const std::string message) : Exception(message) {}
ExceptionIncorrectDuration::ExceptionIncorrectDuration(const std::string message) : Exception(message) {}
ExceptionIncorrectYear::ExceptionIncorrectYear(const std::string message) : Exception(message) {}
ExceptionIncorrectAudioName::ExceptionIncorrectAudioName(const std::string message) : Exception(message) {}
ExceptionIncorrectAudioBookChapters::ExceptionIncorrectAudioBookChapters(const std::string message) : Exception(message) {}
ExceptionIncorrectUsername::ExceptionIncorrectUsername(const std::string message) : Exception(message) {}
ExceptionIncorrectPassword::ExceptionIncorrectPassword(const std::string message) : Exception(message) {}
ExceptionNotEnoughMoney::ExceptionNotEnoughMoney(const std::string message) : Exception(message) {}
ExceptionIncorrectEmail::ExceptionIncorrectEmail(const std::string message) : Exception(message) {}
ExceptionIncorrectChapterNumber::ExceptionIncorrectChapterNumber(const std::string message) : Exception(message) {}

