#ifndef PLAYER_QUEUE_H
#define PLAYER_QUEUE_H

#include <vector>
#include "../../Audio/Audio.h"

class PlayerQueue {
private:
    std::vector<Audio> queue;
    size_t currentIndex;
    bool isLooped;
    int maxQueueSize;

public:
    PlayerQueue();

    void addToQueue(const Audio& audio);
    void removeFromQueue(size_t index);
    Audio getNext();
    Audio getPrevious();
};

#endif // PLAYER_QUEUE_H
