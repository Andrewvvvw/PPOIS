#include "SortEngine.h"
#include <algorithm>

SortEngine::SortEngine(const AudioCollection& audioCollection)
    : collection(audioCollection) {}

void SortEngine::setSortCriteria(SortBy criteria) {
    currentSort = criteria;
}

std::vector<Playlist> SortEngine::getSortedPlaylists() const {
    auto playlists = collection.getPlaylists();

    switch (currentSort) {
        case SortBy::NAME_ASC:
            std::sort(playlists.begin(),
                      playlists.end(),
                      compareByNameAsc);
            break;

        case SortBy::NAME_DESC:
            std::sort(playlists.begin(),
                      playlists.end(),
                     [](const Playlist& a, const Playlist& b) {
                         return !compareByNameAsc(a, b);
                     });
            break;

        case SortBy::TRACK_COUNT:
            std::sort(playlists.begin(),
                      playlists.end(),
                      compareByTrackCount);
            break;

        case SortBy::DURATION:
            std::sort(playlists.begin(),
                      playlists.end(),
                      compareByDuration);
            break;
    }

    return playlists;
}

bool SortEngine::compareByNameAsc(const Playlist& a, const Playlist& b) {
    return a.getName() < b.getName();
}

bool SortEngine::compareByTrackCount(const Playlist& a, const Playlist& b) {
    return a.getTracks().size() < b.getTracks().size();
}

bool SortEngine::compareByDuration(const Playlist& a, const Playlist& b) {
    size_t durationA = 0;
    for (const auto& track : a.getTracks()) {
        durationA += track->getDuration();
    }

    size_t durationB = 0;
    for (const auto& track : b.getTracks()) {
        durationB += track->getDuration();
    }

    return durationA < durationB;
}
