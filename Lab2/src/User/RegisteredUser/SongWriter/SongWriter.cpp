#include "SongWriter.h"
#include "../../../Audio/Album/MusicTrack/MusicTrack.h"
#include <memory>
SongWriter::SongWriter(const std::string &id,
                       const std::string &username,
                       const std::string &email,
                       const std::string &password,
                       const std::string &newBio) :
                       RegisteredUser(id, username, email, password),
                        bio(newBio) {}

bool SongWriter::addTrack(const std::shared_ptr<MusicTrack> &track) {
    if (track == nullptr) {
        return false;
    }
    tracks.push_back(track);
    return true;
}

bool SongWriter::removeTrack(const std::shared_ptr<MusicTrack> &track) {
    if (track == nullptr) {
        return false;
    }
    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end()) {
        tracks.erase(it);
        return true;
    }
    return false;
}

bool SongWriter::hasTrack(const std::shared_ptr<MusicTrack> &track) const {
    if (!track) {
        return false;
    }
    return std::find(tracks.begin(), tracks.end(), track) != tracks.end();
}

const std::vector <std::shared_ptr<MusicTrack>> &SongWriter::getTracks() const {
    return tracks;
}
