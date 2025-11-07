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

    void togglePlayPause();
    void playNext();
    void playPrevious();

    void addToQueue(const std::shared_ptr<Audio>& audio);
    void removeFromQueue(size_t index);

    std::shared_ptr<Audio> getCurrentTrack() const;
    float getPlaybackProgress() const;
    bool isCurrentlyPlaying() const;
};

#endif // AUDIO_PLAYER_H
