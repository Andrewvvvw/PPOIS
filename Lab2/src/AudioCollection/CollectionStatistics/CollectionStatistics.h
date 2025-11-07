#ifndef LAB2_COLLECTIONSTATISTICS_H
#define LAB2_COLLECTIONSTATISTICS_H

#include "../AudioCollection.h"
#include <vector>

class CollectionStatistics {
private:
    const AudioCollection& collection;
    int totalPlaylists;
    int totalTracks;

public:
    explicit CollectionStatistics(const AudioCollection& audioCollection);

    int getNumberOfPlaylists() const;
    int getTotalDuration() const;
    std::vector<std::string> getMostCommonAudioTypes(int topN) const;
};

#endif //LAB2_COLLECTIONSTATISTICS_H
