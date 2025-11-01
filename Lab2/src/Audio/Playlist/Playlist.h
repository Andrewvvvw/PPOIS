#ifndef LAB2_PLAYLIST_H
#define LAB2_PLAYLIST_H

#include <vector>
#include <string>
#include <memory>
#include "../Audio.h"
#include "../../User/RegisteredUser/RegisteredUser.h"

class Playlist {
private:
    std::string name;
    RegisteredUser creator;
    std::vector<std::shared_ptr<Audio>> tracks;
    bool isPublic;
    int currentTrackIndex;

public:
    Playlist(const std::string& name, const RegisteredUser& creator, bool isPublic = true);

    void addTrack(const std::shared_ptr<Audio>& track);
    void removeTrack(size_t index);
    std::shared_ptr<Audio> getCurrentTrack() const;

    std::string getName() const;
    RegisteredUser getCreator() const;
    size_t getTrackCount() const;
    bool getIsPublic() const;

    void setPublic(bool isPublic);
    void clear();
    unsigned long long getTotalDuration() const;
};

#endif //LAB2_PLAYLIST_H
