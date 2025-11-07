#ifndef LAB2_SOCIALFUNCTIONSMANAGER_H
#define LAB2_SOCIALFUNCTIONSMANAGER_H

#include <vector>
#include <memory>

class RegisteredUser;
class Audio;

class SocialFunctionsManager{
private:
    RegisteredUser* user;

    std::vector <std::weak_ptr<RegisteredUser> > following;
    std::vector <std::weak_ptr<RegisteredUser> > followers;
    std::vector <std::weak_ptr<Audio> > likedAudio;

public:
    explicit SocialFunctionsManager(RegisteredUser* user);

    void followUser(std::shared_ptr<RegisteredUser> userToFollow);
    void unfollowUser(const std::shared_ptr<RegisteredUser>& userToUnfollow);
    void likeAudio(std::shared_ptr<Audio> audio);
    void unlikeAudio(const std::shared_ptr<Audio>& audio);

    std::vector<std::shared_ptr<RegisteredUser>> getFollowing() const;
    std::vector<std::shared_ptr<RegisteredUser>> getFollowers() const;
    std::vector<std::shared_ptr<Audio>> getLikedAudio() const;
};

#endif //LAB2_SOCIALFUNCTIONSMANAGER_H
