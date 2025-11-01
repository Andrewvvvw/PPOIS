#ifndef PLAYING_NOW_PANEL_H
#define PLAYING_NOW_PANEL_H

#include "../../Audio/Audio.h"
#include <string>

class PlayingNowPanel {
private:
    const Audio* currentAudio;
    std::string artistName;
    std::string trackName;
    unsigned long long coverID;
    float progress;

public:
    PlayingNowPanel();

    void updateTrackInfo(const Audio& audio);
    void setProgress(float newProgress);
    const Audio& getCurrentTrack() const;
    float getProgress() const { return progress; }
    std::string getArtistName() const { return artistName; }
    std::string getTrackName() const { return trackName; }
    unsigned long long getCoverID() const { return coverID; }
    std::string getFormattedProgress() const;
};

#endif // PLAYING_NOW_PANEL_H
