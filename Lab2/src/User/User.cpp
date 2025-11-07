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