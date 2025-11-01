#ifndef FULLSCREEN_PLAYER_H
#define FULLSCREEN_PLAYER_H

#include "../../Audio/Audio.h"

class FullScreenPlayer {
private:
    Audio currentAudio;
    bool isPlaying;
    bool isFullScreen;
    float playbackProgress;
    bool isLyricsVisible;

public:
    FullScreenPlayer();

    void togglePlayPause();
    void toggleLyrics();
    void seek(float position);
};

#endif // FULLSCREEN_PLAYER_H
