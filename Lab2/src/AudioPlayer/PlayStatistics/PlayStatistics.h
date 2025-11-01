#ifndef PLAY_STATISTICS_H
#define PLAY_STATISTICS_H

#include <map>
#include <string>
#include "../../Audio/Audio.h"

class PlayStatistics {
private:
    std::map<unsigned long long, unsigned int> playCounts; // audioID -> play count
    std::map<unsigned long long, time_t> lastPlayed;       // audioID -> last played timestamp
    unsigned int totalPlays;

public:
    PlayStatistics();

    void recordPlay(const Audio& audio);
    unsigned int getPlayCount(unsigned long long audioID) const;
    time_t getLastPlayed(unsigned long long audioID) const;
    unsigned int getTotalPlays() const;
};

#endif // PLAY_STATISTICS_H
