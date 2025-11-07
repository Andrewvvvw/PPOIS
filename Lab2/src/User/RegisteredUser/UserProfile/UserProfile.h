#ifndef LAB2_USERPROFILE_H
#define LAB2_USERPROFILE_H

#include <string>
class RegisteredUser;


class UserProfile{
private:
    RegisteredUser* user;
    std::string bio;
    std::string profilePictureId;
    std::string backgroundPictureId;
public:
    UserProfile(RegisteredUser* user, std::string bio, std::string profilePictureId, std::string backgroundPictureId);

    void setBio(std::string bio);
    void setProfilePictureId(std::string profilePictureId);
    void setBackgroundPictureId(std::string backgroundPictureId);

    std::string getBio();
    std::string getProfilePictureId();
    std::string getBackgroundPictureId();
};

#endif //LAB2_USERPROFILE_H
