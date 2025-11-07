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
    float getProgress() const { return progress; }
    std::string getArtistName() const { return artistName; }
    std::string getTrackName() const { return trackName; }
    unsigned long long getCoverID() const { return coverID; }
    std::string getFormattedProgress() const;
};

#endif // PLAYING_NOW_PANEL_H
