#include "CollectionStatistics.h"
#include <algorithm>
#include <map>
#include <typeinfo>

CollectionStatistics::CollectionStatistics(const AudioCollection& audioCollection)
    : collection(audioCollection),
      totalPlaylists(0),
      totalTracks(0) {
    const auto& playlists = collection.getPlaylists();
    totalPlaylists = playlists.size();
    for (const auto& playlist : playlists) {
        totalTracks += playlist.getTracks().size();
    }
}

int CollectionStatistics::getTotalDuration() const {
    int duration = 0;
    for (const auto& playlist : collection.getPlaylists()) {
        for (const auto& track : playlist.getTracks()) {
            duration += track->getDuration();
        }
    }
    return duration;
}

std::vector<std::string> CollectionStatistics::getMostCommonAudioTypes(int topN) const {
    std::map<std::string, int> typeCount;

    for (const auto& playlist : collection.getPlaylists()) {
        for (const auto& track : playlist.getTracks()) {
            std::string typeName = typeid(*track).name();
            size_t pos = typeName.find_last_of(" ");
            if (pos != std::string::npos) {
                typeName = typeName.substr(pos + 1);
            }
            typeCount[typeName]++;
        }
    }

    std::vector<std::pair<std::string, int>> sortedTypes(typeCount.begin(), typeCount.end());
    std::sort(sortedTypes.begin(), sortedTypes.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<std::string> result;
    int count = 0;
    for (const auto& [type, _] : sortedTypes) {
        if (count++ >= topN) break;
        result.push_back(type);
    }

    return result;
}

int CollectionStatistics::getNumberOfPlaylists() const {
    return totalPlaylists;
}