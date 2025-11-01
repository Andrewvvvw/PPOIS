#include "PlayerQueue.h"

PlayerQueue::PlayerQueue()
    : currentIndex(0), isLooped(false), maxQueueSize(100) {}

void PlayerQueue::addToQueue(const Audio& audio) {
    if (queue.size() < maxQueueSize) {
        queue.push_back(audio);
    }
}

void PlayerQueue::removeFromQueue(size_t index) {
    if (index < queue.size()) {
        queue.erase(queue.begin() + index);
        if (index <= currentIndex && currentIndex > 0) {
            currentIndex--;
        }
    }
}

Audio PlayerQueue::getNext() {
    if (queue.empty()) {
        return Audio();
    }

    currentIndex++;
    if (currentIndex >= queue.size()) {
        currentIndex = isLooped ? 0 : queue.size() - 1;
    }

    return queue[currentIndex];
}

Audio PlayerQueue::getPrevious() {
    if (queue.empty()) {
        return Audio();
    }

    if (currentIndex > 0) {
        currentIndex--;
    } else if (isLooped) {
        currentIndex = queue.size() - 1;
    }

    return queue[currentIndex];
}
