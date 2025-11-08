#ifndef WIDGET_PLAYER_H
#define WIDGET_PLAYER_H

#include "../../Audio/Audio.h"
#include <memory>
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
    [[nodiscard]] bool getIsPlaying() const;
    [[nodiscard]] bool getIsMinimized() const;
    [[nodiscard]] float getVolume() const;
};

#endif // WIDGET_PLAYER_H
