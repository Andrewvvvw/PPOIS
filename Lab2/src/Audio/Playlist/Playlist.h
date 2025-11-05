#ifndef LAB2_PLAYLIST_H
#define LAB2_PLAYLIST_H

#include <vector>
#include <string>
#include <memory>
#include "../Audio.h"
#include "../../User/RegisteredUser/RegisteredUser.h"

class Playlist {
protected:
    std::string name;
    const RegisteredUser* creator;
    std::vector < std::shared_ptr <Audio> > tracks;
    bool isPublic;
    int currentTrackIndex;

public:
    Playlist(const std::string& name,const RegisteredUser& creator, bool isPublic = true);

    void addTrack(const std::shared_ptr<Audio>& track);
    void removeTrack(const std::shared_ptr<Audio>& track);
    std::shared_ptr<Audio> getCurrentTrack() const;
    std::vector <std::shared_ptr <Audio> > getTracks() const;

    std::string getName() const;
    const RegisteredUser& getCreator() const;
    size_t getTrackCount() const;
    bool getIsPublic() const;

    void setPublic(bool isPublic);
    void clear();
    unsigned long long getTotalDuration() const;

    bool operator==(const Playlist& other) const;
};

#endif //LAB2_PLAYLIST_H
