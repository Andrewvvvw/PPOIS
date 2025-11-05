#include "AudioCollection.h"

AudioCollection::AudioCollection(User& owner) : owner(owner), adManager(owner) {}

void AudioCollection::addPlaylist(const Playlist& playlist) {
    playlists.push_back(playlist);
}

void AudioCollection::removePlaylist(const Playlist& playlist) {
    auto it = std::find_if(playlists.begin(), playlists.end(),
                           [&](const Playlist& p) {
                               return p.getName() == playlist.getName() &&
                                      &p.getCreator() == &playlist.getCreator();
                           });

    if (it != playlists.end()) {
        playlists.erase(it);
    }
}

std::vector<Playlist> AudioCollection::getPlaylists() const {
    return playlists;
}
