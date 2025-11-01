#include "AudioSettings.h"

AudioSettings::AudioSettings()
    : volume(70), playbackSpeed(1.0f), isRepeatOn(false), isMuted(false) {}

void AudioSettings::setVolume(int newVolume) {
    if (newVolume >= 0 && newVolume <= 100) {
        volume = newVolume;
    }
}

void AudioSettings::toggleMute() {
    isMuted = !isMuted;
}

void AudioSettings::toggleRepeat() {
    isRepeatOn = !isRepeatOn;
}
