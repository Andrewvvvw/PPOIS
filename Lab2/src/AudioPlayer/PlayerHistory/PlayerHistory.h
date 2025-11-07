#ifndef PLAYER_HISTORY_H
#define PLAYER_HISTORY_H

#include <deque>
#include <memory>
#include "../../Audio/Audio.h"

class PlayerHistory {
private:
    std::deque<std::shared_ptr<Audio>> history;
    size_t maxHistorySize;
    size_t currentPosition;
    bool isTrackingEnabled;

public:
    PlayerHistory();

    void addToHistory(const std::shared_ptr<Audio>& audio);
    std::shared_ptr<Audio> getPrevious();
    std::shared_ptr<Audio> getNext();
    void clearHistory();
};

#endif // PLAYER_HISTORY_H
