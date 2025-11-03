#include "SocialFunctionsManager.h"

SocialFunctionsManager::SocialFunctionsManager(RegisteredUser* user) : user(user) {}

void SocialFunctionsManager::followUser(RegisteredUser *user) {
    following.push_back(user);
    user->getSocialFunctionsManager()->followers.push_back(user);
}

void SocialFunctionsManager::unfollowUser(RegisteredUser *unfollowingUser) {
    auto itToErase = std::find(following.begin(), following.end(), unfollowingUser);
    if(it != following.end())
        following.erase(it);

    std::vector <std::shared_ptr<RegisteredUser> > unfollowingUserFollowers = unfollowingUser->getSocialFunctionsManager()->getFollowers();
    itToErase = std::find(unfollowingUserFollowers.begin(), unfollowingUserFollowers.end(), this->user);
    if(itToErase != unfollowingUserFollowers.end())
        unfollowingUserFollowers.erase(itToErase);
}

void SocialFunctionsManager::likeAudio(Audio *audio) {
    likedAudio.push_back(audio);
}

void SocialFunctionsManager::unlikeAudio(Audio *audio) {
    likedAudio.erase(std::remove(likedAudio.begin(), likedAudio.end(), audio), likedAudio.end());
}

std::vector <std::shared_ptr<RegisteredUser> > SocialFunctionsManager::getFollowing() {
    return following;
}

std::vector <std::shared_ptr<RegisteredUser> > SocialFunctionsManager::getFollowers() {
    return followers;
}

std::vector <std::shared_ptr<Audio> > SocialFunctionsManager::getLikedAudio() {
    return likedAudio;
}

