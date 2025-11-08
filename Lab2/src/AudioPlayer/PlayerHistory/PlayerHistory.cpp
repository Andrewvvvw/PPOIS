#include "PlayerHistory.h"
#include <memory>
PlayerHistory::PlayerHistory()
    : maxHistorySize(100), currentPosition(0), isTrackingEnabled(true) {}

void PlayerHistory::addToHistory(const std::shared_ptr<Audio>& audio) {
    if (!isTrackingEnabled || !audio) return;

    if (currentPosition < history.size()) {
        history.erase(history.begin() + currentPosition, history.end());
    }

    history.push_back(audio);
    currentPosition = history.size();

    if (history.size() > maxHistorySize) {
        history.pop_front();
        if (currentPosition > 0) currentPosition--;
    }
}

std::shared_ptr<Audio> PlayerHistory::getPrevious() {

    if (currentPosition == 0 || history.empty()) {
        return nullptr;
    }
    currentPosition--;
    return history[currentPosition];
}

std::shared_ptr<Audio> PlayerHistory::getNext() {

    if (currentPosition >= history.size() - 1 || history.empty()) {
        return nullptr;
    }
    currentPosition++;
    return history[currentPosition];
}

void PlayerHistory::clearHistory() {
    history.clear();
    currentPosition = 0;
}
