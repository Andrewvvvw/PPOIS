#ifndef LAB2_AUDIO_COLLECTION_H
#define LAB2_AUDIO_COLLECTION_H

#include <string>
#include "../User/User.h"
#include "AdManager/AdManager.h"
#include "../Audio/Playlist/Playlist.h"

class AudioCollection {
private:
    User& owner;
    AdManager adManager;
    std::vector <Playlist> playlists;

public:
    AudioCollection(User& owner);

    void addPlaylist(const Playlist& playlist);
    void removePlaylist(const Playlist& playlist);

    std::vector<Playlist> getPlaylists() const;

};
#endif //LAB2_AUDIO_COLLECTION_H
