#include "UserProfile.h"

UserProfile::UserProfile(RegisteredUser *user, std::string bio, std::string profilePictureId,
                         std::string backgroundPictureId) :
                         user(user),
                         bio(bio),
                         profilePictureId(profilePictureId),
                         backgroundPictureId(backgroundPictureId)
                         {}