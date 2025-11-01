#ifndef WIDGET_PLAYER_H
#define WIDGET_PLAYER_H

#include "../../Audio/Audio.h"

class WidgetPlayer {
private:
    Audio currentAudio;
    bool isPlaying;
    bool isMinimized;
    float volume;

public:
    WidgetPlayer();

    void togglePlayPause();
    void toggleMinimize();
    void setVolume(float newVolume);
};

#endif // WIDGET_PLAYER_H
