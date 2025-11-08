#include "SearchEngine.h"
#include <algorithm>
#include <memory>
SearchEngine::SearchEngine(const AudioCollection& audioCollection)
    : collection(audioCollection) {}

std::vector<Playlist> SearchEngine::searchPlaylistsByName(const std::string& name) const {
    std::vector <Playlist> result;
    const auto& playlists = collection.getPlaylists();

    for (const auto& playlist : playlists) {
        if (playlist.getName().find(name) != std::string::npos) {
            result.push_back(playlist);
        }
    }

    return result;
}

std::vector<std::shared_ptr<Audio>> SearchEngine::searchTracksByName(const std::string& name) const {
    std::vector<std::shared_ptr<Audio>> result;
    const auto& playlists = collection.getPlaylists();

    for (const auto& playlist : playlists) {
        for (const auto& track : playlist.getTracks()) {
            if (track->getName().find(name) != std::string::npos) {
                if (std::find(result.begin(), result.end(), track) == result.end()) {
                    result.push_back(track);
                }
            }
        }
    }

    return result;
}
