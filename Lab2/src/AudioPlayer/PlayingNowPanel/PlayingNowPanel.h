#ifndef PLAYING_NOW_PANEL_H
#define PLAYING_NOW_PANEL_H

#include "../../Audio/Audio.h"
#include <string>
#include <memory>

class PlayingNowPanel {
private:
    std::shared_ptr<Audio> currentAudio;
    std::string artistName;
    std::string trackName;
    unsigned long long coverID;
    float progress;

public:
    PlayingNowPanel();

    void updateTrackInfo(const std::shared_ptr<Audio>& audio);
    void setProgress(float newProgress);
    std::shared_ptr<Audio> getCurrentTrack() const;
    float getProgress() const;
    std::string getArtistName() const;
    std::string getTrackName() const;
    unsigned long long getCoverID() const;
    std::string getFormattedProgress() const;
};

#endif // PLAYING_NOW_PANEL_H
