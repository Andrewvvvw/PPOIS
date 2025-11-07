#ifndef PLAYER_QUEUE_H
#define PLAYER_QUEUE_H

#include <vector>
#include <memory>
#include "../../Audio/Audio.h"

class PlayerQueue {
private:
    std::vector<std::shared_ptr<Audio>> queue;
    size_t currentIndex;
    bool isLooped;
    int maxQueueSize;

public:
    PlayerQueue();

    void addToQueue(const std::shared_ptr<Audio>& audio);
    void removeFromQueue(size_t index);
    std::shared_ptr<Audio> getNext();
    std::shared_ptr<Audio> getPrevious();
    void setLooped(bool looped);
    bool getIsLooped() const;
    void setMaxQueueSize(int size);
    int getMaxQueueSize() const;
    size_t getCurrentIndex() const;
    size_t getQueueSize() const;
};

#endif // PLAYER_QUEUE_H
