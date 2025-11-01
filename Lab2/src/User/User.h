#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

class User {
protected:
    std::string id;
    std::string username;
    time_t registrationDate;

public:
    User(const std::string& id, const std::string& username);
    virtual ~User() = default;

    std::string getId() const { return id; }
    std::string getUsername() const { return username; }
    time_t getRegistrationDate() const { return registrationDate; }

    void setUsername(const std::string& newUsername) { username = newUsername; }

    virtual bool canUploadContent() const { return false; }
    virtual bool canComment() const { return false; }
    virtual std::string getUserType() const = 0;
};

#endif // USER_H
