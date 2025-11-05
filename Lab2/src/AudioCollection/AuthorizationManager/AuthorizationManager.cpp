#include "AuthorizationManager.h"

AuthorizationManager::AuthorizationManager(int attempts) : maxLoginAttempts(attempts), isLoggedIn(false) {
}

bool AuthorizationManager::login(const std::string& email, const std::string& password) {
    auto it = userCredentials.find(email);
    if (it != userCredentials.end() && it->second == password) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

bool AuthorizationManager::registerUser(const RegisteredUser& user) {
    std::string email = user.getEmail();
    std::string password = user.getPassword();

    if (userCredentials.find(email) == userCredentials.end()) {
        userCredentials[email] = password;
        return true;
    }
    return false;
}