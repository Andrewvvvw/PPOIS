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
