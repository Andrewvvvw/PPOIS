#ifndef PLAYER_HISTORY_H
#define PLAYER_HISTORY_H

#include <deque>
#include "../../Audio/Audio.h"

class PlayerHistory {
private:
    std::deque<Audio> history;
    size_t maxHistorySize;
    size_t currentPosition;
    bool isTrackingEnabled;

public:
    PlayerHistory();

    void addToHistory(const Audio& audio);
    Audio getPrevious();
    Audio getNext();
    void clearHistory();
};

#endif // PLAYER_HISTORY_H
