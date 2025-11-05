#ifndef LAB2_SORTENGINE_H
#define LAB2_SORTENGINE_H

#include "../AudioCollection.h"
#include <vector>
#include <functional>

class SortEngine {
public:
    enum class SortBy {
        NAME_ASC,
        NAME_DESC,
        TRACK_COUNT,
        DURATION
    };

    explicit SortEngine(const AudioCollection& audioCollection);

    void setSortCriteria(SortBy criteria);

    std::vector<Playlist> getSortedPlaylists() const;

private:
    const AudioCollection& collection;
    SortBy currentSort = SortBy::NAME_ASC;

    static bool compareByNameAsc(const Playlist& a, const Playlist& b);
    static bool compareByTrackCount(const Playlist& a, const Playlist& b);
    static bool compareByDuration(const Playlist& a, const Playlist& b);
};

#endif //LAB2_SORTENGINE_H
