#ifndef LAB2_AUTHORIZATIONMANAGER_H
#define LAB2_AUTHORIZATIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "../../User/RegisteredUser/RegisteredUser.h"

class AuthorizationManager {
private:
    std::map<std::string, std::string> userCredentials;
    int maxLoginAttempts;
    bool isLoggedIn;

public:
    AuthorizationManager(int attempts);
    bool login(const std::string& email, const std::string& password);
    bool registerUser(const RegisteredUser& user);
};

#endif //LAB2_AUTHORIZATIONMANAGER_H