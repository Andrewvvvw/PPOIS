#include "UserStatistics.h"
#include "map"
#include "algorithm"
#include "../Artist/Artist.h"

std::string UserStatistics::getFavoriteCreatorName(const RegisteredUser& user, const AudioCollection& audioCollection) {
    std::unordered_map<std::string, int> creatorCounts;
    auto playlists = audioCollection.getPlaylists();

    for (const auto& playlist : playlists) {
        auto tracks = playlist.getTracks();
        for (const auto& track : tracks) {
            if (track) {
                creatorCounts[track->getAuthor()]++;
            }
        }
    }
    if (creatorCounts.empty()) {
        return "";
    }

    auto maxPair = std::max_element(
            creatorCounts.begin(),
            creatorCounts.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            }
    );

    return maxPair->first;
}

UserStatistics::UserStatistics() = default;