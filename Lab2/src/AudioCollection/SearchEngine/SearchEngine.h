#ifndef LAB2_SEARCHENGINE_H
#define LAB2_SEARCHENGINE_H

#include "../AudioCollection.h"
#include <vector>
#include <string>
#include <memory>
class SearchEngine {
private:
    const AudioCollection& collection;

public:
    explicit SearchEngine(const AudioCollection& audioCollection);

    std::vector<Playlist> searchPlaylistsByName(const std::string& name) const;
    std::vector<std::shared_ptr<Audio>> searchTracksByName(const std::string& name) const;
};

#endif //LAB2_SEARCHENGINE_H
