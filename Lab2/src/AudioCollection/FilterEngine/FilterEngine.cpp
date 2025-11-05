#include "FilterEngine.h"

FilterEngine::FilterEngine(const AudioCollection& audioCollection)
    : collection(audioCollection) {}

void FilterEngine::setPublicFilter(bool isPublic) {
    this->isPublic = isPublic;
    filterByPublic = true;
}

void FilterEngine::setMinTracksFilter(size_t minTracks) {
    this->minTracks = minTracks;
    filterByMinTracks = true;
}

void FilterEngine::resetFilters() {
    filterByPublic = false;
    filterByMinTracks = false;
    isPublic = true;
    minTracks = 0;
}

std::vector<Playlist> FilterEngine::getFilteredPlaylists() const {
    std::vector<Playlist> result;
    const auto& playlists = collection.getPlaylists();

    for (const auto& playlist : playlists) {
        bool matches = true;

        if (filterByPublic && playlist.getIsPublic() != isPublic) {
            matches = false;
        }

        if (matches && filterByMinTracks && playlist.getTracks().size() < minTracks) {
            matches = false;
        }

        if (matches) {
            result.push_back(playlist);
        }
    }

    return result;
}
