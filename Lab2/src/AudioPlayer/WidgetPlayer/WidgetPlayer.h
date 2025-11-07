#ifndef WIDGET_PLAYER_H
#define WIDGET_PLAYER_H

#include "../../Audio/Audio.h"

class WidgetPlayer {
private:
    std::shared_ptr<Audio> currentAudio;
    bool isPlaying;
    bool isMinimized;
    float volume;

public:
    WidgetPlayer();

    void togglePlayPause();
    void toggleMinimize();
    void setVolume(float newVolume);
    void setCurrentAudio(std::shared_ptr<Audio> audio);

    [[nodiscard]] const Audio& getCurrentAudio() const;
    [[nodiscard]] bool getIsPlaying() const { return isPlaying; }
    [[nodiscard]] bool getIsMinimized() const { return isMinimized; }
    [[nodiscard]] float getVolume() const { return volume; }
};

#endif // WIDGET_PLAYER_H
