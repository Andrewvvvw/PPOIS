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

int AudioSettings::getVolume() const {
    return volume;
}

float AudioSettings::getPlaybackSpeed() const {
    return playbackSpeed;
}

bool AudioSettings::getRepeatOn() const {
    return isRepeatOn;
}

bool AudioSettings::getMuted() const {
    return isMuted;
}

void AudioSettings::setPlaybackSpeed(float newSpeed) {
    if (newSpeed >= 0.5f && newSpeed <= 2.0f) {
        playbackSpeed = newSpeed;
    }
}
