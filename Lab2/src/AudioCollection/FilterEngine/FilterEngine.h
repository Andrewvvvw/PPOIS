#ifndef LAB2_FILTERENGINE_H
#define LAB2_FILTERENGINE_H

#include "../AudioCollection.h"
#include <string>
#include <vector>

class FilterEngine {
private:
    const AudioCollection& collection;

    bool filterByPublic = false;
    bool filterByMinTracks = false;

    bool isPublic = true;
    size_t minTracks = 0;

public:
    explicit FilterEngine(const AudioCollection& audioCollection);

    void setPublicFilter(bool isPublic);
    void setMinTracksFilter(size_t minTracks);

    void resetFilters();

    std::vector<Playlist> getFilteredPlaylists() const;
};

#endif //LAB2_FILTERENGINE_H
