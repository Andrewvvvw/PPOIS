#ifndef LAB2_USERPROFILE_H
#define LAB2_USERPROFILE_H

#include <string>
//#include "../RegisteredUser.h"
class RegisteredUser;


class UserProfile{
private:
    RegisteredUser* user;
    std::string bio;
    std::string profilePictureId;
    std::string backgroundPictureId;
public:
    UserProfile(RegisteredUser* user, std::string bio, std::string profilePictureId, std::string backgroundPictureId);

    void setBio(std::string bio){ this->bio = bio; }
    void setProfilePictureId(std::string profilePictureId){ this->profilePictureId = profilePictureId; }
    void setBackgroundPictureId(std::string backgroundPictureId){ this->backgroundPictureId = backgroundPictureId; }

    std::string getBio(){ return bio; }
    std::string getProfilePictureId(){ return profilePictureId; }
    std::string getBackgroundPictureId(){ return backgroundPictureId; }
};

#endif //LAB2_USERPROFILE_H
