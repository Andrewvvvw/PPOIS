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

    void setVolume(int newVolume);
    void toggleMute();
    void toggleRepeat();
};

#endif // AUDIO_SETTINGS_H
