#include "AudioPlayer.h"
#include <stdexcept>

AudioPlayer::AudioPlayer()
        : isPlaying(false), currentProgress(0.0f) {}

void AudioPlayer::togglePlayPause() {
    isPlaying = !isPlaying;
    if (isPlaying) {
        if (getCurrentTrack().name.empty()) {
            playNext();
        }
    }
}

void AudioPlayer::playNext() {
    Audio next = queue.getNext();
    if (next.name.empty()) return;

    const Audio& current = getCurrentTrack();
    if (!current.name.empty()) {
        history.addToHistory(current);
    }

    nowPlaying.updateTrackInfo(next);
    currentProgress = 0.0f;
    isPlaying = true;
}

void AudioPlayer::playPrevious() {
    Audio prev = history.getPrevious();
    if (prev.name.empty()) return;

    nowPlaying.updateTrackInfo(prev);
    currentProgress = 0.0f;
    isPlaying = true;
}

void AudioPlayer::addToQueue(const Audio& audio) {
    queue.addToQueue(audio);
}

void AudioPlayer::removeFromQueue(size_t index) {
    queue.removeFromQueue(index);
}

const Audio& AudioPlayer::getCurrentTrack() const {
    return nowPlaying.getCurrentTrack();
}

float AudioPlayer::getPlaybackProgress() const {
    return currentProgress;
}