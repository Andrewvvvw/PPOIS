#include "Podcaster.h"

Podcaster::Podcaster(const std::string& id, const std::string& username,
                     const std::string& email, const std::string& password)
    : RegisteredUser(id, username, email, password) {}

bool Podcaster::addPodcast(const std::shared_ptr<Podcast> &podcast) {
    podcasts.push_back(podcast);
    return true;
}

bool Podcaster::removePodcast(const std::shared_ptr<Podcast> &podcast) {
    auto it = std::find(podcasts.begin(), podcasts.end(), podcast);
    if (it != podcasts.end()) {
        podcasts.erase(it);
        return true;
    }
    return false;
}

bool Podcaster::hasPodcast(const std::shared_ptr<Podcast> &podcast) const {
    return std::find(podcasts.begin(), podcasts.end(), podcast) != podcasts.end();
}

