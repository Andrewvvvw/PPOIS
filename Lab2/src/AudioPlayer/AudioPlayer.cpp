#include "AudioPlayer.h"
#include <stdexcept>

AudioPlayer::AudioPlayer()
        : isPlaying(false), currentProgress(0.0f) {}

void AudioPlayer::togglePlayPause() {
    isPlaying = !isPlaying;
    if (isPlaying) {
        auto current = getCurrentTrack();
        if (!current) {
            playNext();
        }
    }
}

void AudioPlayer::playNext() {
    auto next = queue.getNext();
    if (!next) return;

    auto current = getCurrentTrack();
    if (current) {
        history.addToHistory(current);
    }

    nowPlaying.updateTrackInfo(next);
    currentProgress = 0.0f;
    isPlaying = true;
}

void AudioPlayer::playPrevious() {
    auto prev = history.getPrevious();
    if (!prev) return;

    nowPlaying.updateTrackInfo(prev);
    currentProgress = 0.0f;
    isPlaying = true;
}

void AudioPlayer::addToQueue(const std::shared_ptr<Audio>& audio) {
    if (audio) {
        queue.addToQueue(audio);
    }
}

void AudioPlayer::removeFromQueue(size_t index) {
    queue.removeFromQueue(index);
}

std::shared_ptr<Audio> AudioPlayer::getCurrentTrack() const {
    return nowPlaying.getCurrentTrack();
}

float AudioPlayer::getPlaybackProgress() const {
    return currentProgress;
}