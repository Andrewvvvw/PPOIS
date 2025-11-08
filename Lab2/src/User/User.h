#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
#include <memory>

class AudioCollection;

class User {
protected:
    std::string id;
    std::string username;
    time_t registrationDate;
    std::unique_ptr<AudioCollection> audioCollection;

public:
    User(const std::string& id, const std::string& username);
    virtual ~User();

    std::string getId() const;
    std::string getUsername() const;
    time_t getRegistrationDate() const;

    void setUsername(const std::string& newUsername);

    virtual bool canUploadContent() const;
    virtual bool canComment() const;
    virtual std::string getUserType() const = 0;
    virtual bool getIsPremium() const;

    AudioCollection* getAudioCollection();
};

#endif // USER_H
