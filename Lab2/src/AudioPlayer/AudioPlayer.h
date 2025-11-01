#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "../Audio/Audio.h"
#include "AudioSettings/AudioSettings.h"
#include "PlayerQueue/PlayerQueue.h"
#include "PlayerHistory/PlayerHistory.h"
#include "PlayingNowPanel/PlayingNowPanel.h"

class AudioPlayer {
private:
    PlayerQueue queue;
    PlayerHistory history;
    PlayingNowPanel nowPlaying;
    AudioSettings settings;
    bool isPlaying;
    float currentProgress;

public:
    AudioPlayer();

    // Core playback control
    void togglePlayPause();
    void playNext();
    void playPrevious();

    // Queue management
    void addToQueue(const Audio& audio);
    void removeFromQueue(size_t index);

    // Player state
    const Audio& getCurrentTrack() const;
    float getPlaybackProgress() const;
    bool isCurrentlyPlaying() const { return isPlaying; }
};

#endif // AUDIO_PLAYER_H
