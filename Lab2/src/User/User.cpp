#include "User.h"

User::User(const std::string& id, const std::string& username)
    : id(id), username(username) {
    registrationDate = time(nullptr);
}
