#include "UserProfile.h"

UserProfile::UserProfile(RegisteredUser *user, std::string bio, std::string profilePictureId,
                         std::string backgroundPictureId) :
                         user(user),
                         bio(bio),
                         profilePictureId(profilePictureId),
                         backgroundPictureId(backgroundPictureId)
                         {}

void UserProfile::setBio(std::string bio) {
    this->bio = bio;
}

void UserProfile::setProfilePictureId(std::string profilePictureId) {
    this->profilePictureId = profilePictureId;
}

void UserProfile::setBackgroundPictureId(std::string backgroundPictureId) {
    this->backgroundPictureId = backgroundPictureId;
}

std::string UserProfile::getBio() {
    return bio;
}

std::string UserProfile::getProfilePictureId() {
    return profilePictureId;
}

std::string UserProfile::getBackgroundPictureId() {
    return backgroundPictureId;
}
