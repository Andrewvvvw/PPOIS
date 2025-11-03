#ifndef LAB2_SOCIALFUNCTIONSMANAGER_H
#define LAB2_SOCIALFUNCTIONSMANAGER_H

#include "../RegisteredUser.h"

class SocialFunctionsManager{
private:
    RegisteredUser* user;

    std::vector <std::shared_ptr<RegisteredUser> > following;
    std::vector <std::shared_ptr<RegisteredUser> > followers;
    std::vector <std::shared_ptr<Audio> > likedAudio;

public:
    SocialFunctionsManager(RegisteredUser* user);

    void followUser(RegisteredUser* user);
    void unfollowUser(RegisteredUser* user);
    void likeAudio(Audio* audio);
    void unlikeAudio(Audio* audio);

    std::vector <std::shared_ptr<RegisteredUser> > getFollowing();
    std::vector <std::shared_ptr<RegisteredUser> > getFollowers();
    std::vector <std::shared_ptr<Audio> > getLikedAudio();
};

#endif //LAB2_SOCIALFUNCTIONSMANAGER_H
