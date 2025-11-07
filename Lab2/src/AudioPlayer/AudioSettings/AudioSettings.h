#ifndef AUDIO_SETTINGS_H
#define AUDIO_SETTINGS_H

class AudioSettings {
private:
    int volume;
    float playbackSpeed;
    bool isRepeatOn;
    bool isMuted;

public:
    AudioSettings();
    int getVolume() const;
    float getPlaybackSpeed() const;
    bool getRepeatOn() const;
    bool getMuted() const;

    void setVolume(int newVolume);
    void toggleMute();
    void toggleRepeat();
    void setPlaybackSpeed(float newSpeed);
};

#endif // AUDIO_SETTINGS_H
