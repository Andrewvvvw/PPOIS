#include "PlayStatistics.h"
#include <ctime>

PlayStatistics::PlayStatistics() : totalPlays(0) {}

void PlayStatistics::recordPlay(const Audio& audio) {
    unsigned long long audioID = audio.coverID; // Using coverID as unique identifier
    playCounts[audioID]++;
    lastPlayed[audioID] = std::time(nullptr);
    totalPlays++;
}

unsigned int PlayStatistics::getPlayCount(unsigned long long audioID) const {
    auto it = playCounts.find(audioID);
    return (it != playCounts.end()) ? it->second : 0;
}

time_t PlayStatistics::getLastPlayed(unsigned long long audioID) const {
    auto it = lastPlayed.find(audioID);
    return (it != lastPlayed.end()) ? it->second : 0;
}

unsigned int PlayStatistics::getTotalPlays() const {
    return totalPlays;
}
