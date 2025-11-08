#include "User.h"
#include "../Exceptions/Exceptions.h"
#include "../AudioCollection/AudioCollection.h"

User::User(const std::string& id, const std::string& username)
        : id(id), username(username), registrationDate(time(nullptr)) {
    audioCollection = std::make_unique<AudioCollection>(*this);
}

void User::setUsername(const std::string &newUsername) {
    if(newUsername.empty())
        throw ExceptionIncorrectUsername("Username can't be empty");
    username = newUsername;
}

User::~User() = default;

std::string User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

time_t User::getRegistrationDate() const {
    return registrationDate;
}

bool User::canUploadContent() const {
    return false;
}

bool User::canComment() const {
    return false;
}

std::string User::getUserType() const {
    return "User";
}

bool User::getIsPremium() const {
    return false;
}

AudioCollection* User::getAudioCollection() {
    return audioCollection.get();
}

