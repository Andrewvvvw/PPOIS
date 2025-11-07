#include "SocialFunctionsManager.h"
#include "../RegisteredUser.h"

SocialFunctionsManager::SocialFunctionsManager(RegisteredUser* user) : user(user) {}

void SocialFunctionsManager::followUser(std::shared_ptr<RegisteredUser> userToFollow) {
    if (!userToFollow) return;

    auto it = std::find_if(following.begin(), following.end(),
                           [&](const auto& wp) {
                               auto sp = wp.lock();
                               return sp && sp.get() == userToFollow.get();
                           });

    if (it == following.end()) {
        following.emplace_back(userToFollow);
        userToFollow->getSocialFunctionsManager()->followers.emplace_back(user->shared_from_this());
    }
}

void SocialFunctionsManager::unfollowUser(const std::shared_ptr<RegisteredUser>& userToUnfollow) {
    if (!userToUnfollow) return;

    following.erase(
            std::remove_if(following.begin(), following.end(),
                           [&](const auto& wp) {
                               auto sp = wp.lock();
                               return !sp || sp.get() == userToUnfollow.get();
                           }),
            following.end()
    );

    auto& targetFollowers = userToUnfollow->getSocialFunctionsManager()->followers;
    targetFollowers.erase(
            std::remove_if(targetFollowers.begin(), targetFollowers.end(),
                           [this](const auto& wp) {
                               auto sp = wp.lock();
                               return !sp || sp.get() == this->user;
                           }),
            targetFollowers.end()
    );
}

void SocialFunctionsManager::likeAudio(std::shared_ptr<Audio> audio) {
    if (!audio) return;

    auto it = std::find_if(likedAudio.begin(), likedAudio.end(),
                           [&](const auto& wp) {
                               auto sp = wp.lock();
                               return sp && sp == audio;
                           });

    if (it == likedAudio.end()) {
        likedAudio.emplace_back(audio);
    }
}

void SocialFunctionsManager::unlikeAudio(const std::shared_ptr<Audio>& audio) {
    if (!audio) return;

    likedAudio.erase(
            std::remove_if(likedAudio.begin(), likedAudio.end(),
                           [&](const auto& wp) {
                               auto sp = wp.lock();
                               return !sp || sp == audio;
                           }),
            likedAudio.end()
    );
}

std::vector<std::shared_ptr<RegisteredUser>> SocialFunctionsManager::getFollowing() const {
    std::vector<std::shared_ptr<RegisteredUser>> result;
    for (const auto& wp : following) {
        if (auto sp = wp.lock()) {
            result.push_back(sp);
        }
    }
    return result;
}

std::vector<std::shared_ptr<RegisteredUser>> SocialFunctionsManager::getFollowers() const {
    std::vector<std::shared_ptr<RegisteredUser>> result;
    for (const auto& wp : followers) {
        if (auto sp = wp.lock()) {
            result.push_back(sp);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Audio>> SocialFunctionsManager::getLikedAudio() const {
    std::vector<std::shared_ptr<Audio>> result;
    for (const auto& wp : likedAudio) {
        if (auto sp = wp.lock()) {
            result.push_back(sp);
        }
    }
    return result;
}