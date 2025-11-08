#include "WidgetPlayer.h"
#include <memory>
#include <stdexcept>

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

bool WidgetPlayer::getIsPlaying() const {
    return isPlaying;
}

bool WidgetPlayer::getIsMinimized() const {
    return isMinimized;
}

float WidgetPlayer::getVolume() const {
    return volume;
}


