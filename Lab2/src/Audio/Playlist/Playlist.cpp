#include "Playlist.h"
#include <algorithm>
#include <memory>
Playlist::Playlist(const std::string& name, const RegisteredUser& creator, bool isPublic)
        : name(name), creator(&creator), isPublic(isPublic), currentTrackIndex(0) {}

void Playlist::addTrack(const std::shared_ptr<Audio>& track) {
        tracks.push_back(track);
}

void Playlist::removeTrack(const std::shared_ptr<Audio>& audio) {
    auto it = std::find(tracks.begin(), tracks.end(), audio);
    if (it != tracks.end()) {
        size_t index = std::distance(tracks.begin(), it);
        tracks.erase(it);
        if (currentTrackIndex >= index && currentTrackIndex > 0) {
            currentTrackIndex--;
        }
    }
}

std::shared_ptr<Audio> Playlist::getCurrentTrack() const {
    if (tracks.empty()) return nullptr;
    return tracks[currentTrackIndex];
}

std::string Playlist::getName() const {
    return name;
}

const RegisteredUser& Playlist::getCreator() const {
    return *creator;
}

size_t Playlist::getTrackCount() const {
    return tracks.size();
}

bool Playlist::getIsPublic() const {
    return isPublic;
}

void Playlist::setPublic(bool isPublic) {
    this->isPublic = isPublic;
}

void Playlist::clear() {
    tracks.clear();
    currentTrackIndex = 0;
}

unsigned long long Playlist::getTotalDuration() const {
    unsigned long long total = 0;
    for (const auto& track : tracks) {
        if (track) {
            total += track->getDuration();
        }
    }
    return total;
}

std::vector <std::shared_ptr <Audio> > Playlist::getTracks() const {
    return tracks;
}

bool Playlist::operator==(const Playlist& other) const {
    return name == other.name && creator == other.creator;
}
