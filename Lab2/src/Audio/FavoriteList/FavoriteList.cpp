#include "FavoriteList.h"

void FavoriteList::addToFavorites(const std::shared_ptr<Audio>& audio) {
    tracks.push_back(audio);
}

void FavoriteList::removeFromFavorites(const std::shared_ptr<Audio>& audio) {
    auto it = std::find(tracks.begin(), tracks.end(), audio);
    if (it != tracks.end()) {
        tracks.erase(it);
    }
}

const std::vector<std::shared_ptr<Audio>>& FavoriteList::getTracks() const {
    return tracks;
}