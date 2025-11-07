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

    std::string getId() const { return id; }
    std::string getUsername() const { return username; }
    time_t getRegistrationDate() const { return registrationDate; }

    void setUsername(const std::string& newUsername);

    virtual bool canUploadContent() const { return false; }
    virtual bool canComment() const { return false; }
    virtual std::string getUserType() const = 0;
    virtual bool getIsPremium() const { return false; }

    AudioCollection* getAudioCollection() { return audioCollection.get(); }
    const AudioCollection* getAudioCollection() const { return audioCollection.get(); }
};

#endif // USER_H
