#include "Producer.h"
#include <memory>
Producer::Producer(const std::string& id, const std::string& username,
                   const std::string& email, const std::string& password,
                   const std::string& bio)
    : RegisteredUser(id, username, email, password), bio(bio) {}

bool Producer::addTrack(const std::shared_ptr<MusicTrack> &track) {
    if (!track || hasTrack(track)) {
        return false;
    }
    tracks.push_back(track);
    return true;
}

bool Producer::removeTrack(const std::shared_ptr<MusicTrack> &track) {
    if (!track) {
        return false;
    }

    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end()) {
        tracks.erase(it);
        return true;
    }
    return false;
}

bool Producer::hasTrack(const std::shared_ptr<MusicTrack> &track) const {
    if (!track) {
        return false;
    }
    return std::find(tracks.begin(), tracks.end(), track) != tracks.end();
}

const std::vector<std::shared_ptr<MusicTrack>>& Producer::getTracks() const {
    return tracks;
}