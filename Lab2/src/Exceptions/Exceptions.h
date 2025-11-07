#ifndef LAB2_EXCEPTIONS_H
#define LAB2_EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string message;
public:
    [[nodiscard]] const char* what() const noexcept override;
    explicit Exception(std::string message);
};

class ExceptionIncorrectYear : public Exception {
public:
    explicit ExceptionIncorrectYear(std::string message);
};

class ExceptionIncorrectDuration : public Exception {
public:
    explicit ExceptionIncorrectDuration(std::string message);
};

class ExceptionIncorrectPassword : public Exception {
public:
    explicit ExceptionIncorrectPassword(std::string message);
};

class ExceptionIncorrectEmail : public Exception {
public:
    explicit ExceptionIncorrectEmail(std::string message);
};

class ExceptionIncorrectUsername : public Exception {
public:
    explicit ExceptionIncorrectUsername(std::string message);
};

class ExceptionIncorrectAudioName : public Exception {
public:
    explicit ExceptionIncorrectAudioName(std::string message);
};

class ExceptionIncorrectArtistName : public Exception {
public:
    explicit ExceptionIncorrectArtistName(std::string message);
};

class ExceptionIncorrectAlbumTitle : public Exception {
public:
    explicit ExceptionIncorrectAlbumTitle(std::string message);
};

class ExceptionIncorrectTrack : public Exception {
public:
    explicit ExceptionIncorrectTrack(std::string message);
};

class ExceptionIncorrectChapterNumber : public Exception {
public:
    explicit ExceptionIncorrectChapterNumber(std::string message);
};

class ExceptionIncorrectAudioBookChapters : public Exception {
public:
    explicit ExceptionIncorrectAudioBookChapters(std::string message);
};

class ExceptionNotEnoughMoney : public Exception {
public:
    explicit ExceptionNotEnoughMoney(std::string message);
};

#endif //LAB2_EXCEPTIONS_H
