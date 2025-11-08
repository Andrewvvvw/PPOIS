#include "PlayerQueue.h"
#include <memory>
PlayerQueue::PlayerQueue()
    : currentIndex(0), isLooped(false), maxQueueSize(100) {}

void PlayerQueue::addToQueue(const std::shared_ptr<Audio>& audio) {
    if (queue.size() < maxQueueSize && audio) {
        queue.push_back(audio);
    }
}

void PlayerQueue::removeFromQueue(size_t index) {
    if (index >= queue.size()) {
        return;
    }

    if (index < currentIndex) {
        currentIndex--;
    }
    else if (index == currentIndex && currentIndex == queue.size() - 1 && currentIndex > 0) {
        currentIndex--;
    }

    queue.erase(queue.begin() + index);
}

std::shared_ptr<Audio> PlayerQueue::getNext() {
    if (queue.empty()) {
        return nullptr;
    }
    auto currentTrack = queue[currentIndex];
    currentIndex++;
    if (currentIndex >= queue.size()) {
        currentIndex = isLooped ? 0 : queue.size() - 1;
    }

    return currentTrack;

}

std::shared_ptr<Audio> PlayerQueue::getPrevious() {
    if (queue.empty()) {
        return nullptr;
    }

    if (currentIndex > 0) {
        currentIndex--;
    } else if (isLooped) {
        currentIndex = queue.size() - 1;
    }

    return queue[currentIndex];
}

void PlayerQueue::setLooped(bool looped) {
    isLooped = looped;
}

bool PlayerQueue::getIsLooped() const {
    return isLooped;
}

void PlayerQueue::setMaxQueueSize(int size) {
    maxQueueSize = size;
}

int PlayerQueue::getMaxQueueSize() const {
    return maxQueueSize;
}

size_t PlayerQueue::getCurrentIndex() const {
    return currentIndex;
}

size_t PlayerQueue::getQueueSize() const {
    return queue.size();
}
