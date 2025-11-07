#include "WidgetPlayer.h"

WidgetPlayer::WidgetPlayer()
    : isPlaying(false), isMinimized(false), volume(70.0f) {}

void WidgetPlayer::togglePlayPause() {
    isPlaying = !isPlaying;
}

void WidgetPlayer::toggleMinimize() {
    isMinimized = !isMinimized;
}

void WidgetPlayer::setVolume(float newVolume) {
    if (newVolume >= 0.0f && newVolume <= 100.0f) {
        volume = newVolume;
    }
}

void WidgetPlayer::setCurrentAudio(std::shared_ptr<Audio> audio) {
    currentAudio = std::move(audio);
}

const Audio& WidgetPlayer::getCurrentAudio() const {
    if (!currentAudio) {
        throw std::runtime_error("No audio is currently set");
    }
    return *currentAudio;
}


