#include "PlayerHistory.h"

PlayerHistory::PlayerHistory()
    : maxHistorySize(100), currentPosition(0), isTrackingEnabled(true) {}

void PlayerHistory::addToHistory(const Audio& audio) {
    if (!isTrackingEnabled) return;

    if (currentPosition < history.size()) {
        history.erase(history.begin() + currentPosition, history.end());
    }

    history.push_back(audio);
    currentPosition = history.size();

    if (history.size() > maxHistorySize) {
        history.pop_front();
        currentPosition--;
    }
}

Audio PlayerHistory::getPrevious() {
    if (currentPosition > 0) {
        currentPosition--;
        return history[currentPosition];
    }
    return Audio();
}

Audio PlayerHistory::getNext() {
    if (currentPosition < history.size() - 1) {
        currentPosition++;
        return history[currentPosition];
    }
    return Audio();
}

void PlayerHistory::clearHistory() {
    history.clear();
    currentPosition = 0;
}
