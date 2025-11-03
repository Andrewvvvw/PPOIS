#include "UserStatistics.h"
#include "map"
#include "algorithm"

int UserStatistics::getNumberOfPlaylists() {
    return this->user.getPlaylists().size();
}

std::string UserStatistics::getFavoriteCreatorName() {
    std::unordered_map <std::string , int> creatorCounts;

    for(auto playlist : this->user.getPlaylists()){
        std::vector <std::shared_ptr <Audio> > tracks = playlist->getTracks();
        for(auto track : tracks) creatorCounts[track.getAuthor()]++;
    }

    auto maxPair = std::max_element(creatorCounts.begin(), creatorCounts.end());
    return maxPair->first;
}
