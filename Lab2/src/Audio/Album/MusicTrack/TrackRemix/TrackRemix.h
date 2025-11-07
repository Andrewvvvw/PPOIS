#ifndef TRACK_REMIX_H
#define TRACK_REMIX_H

#include "../MusicTrack.h"
#include <string>

class TrackRemix : public MusicTrack {
private:
    std::string originalTrackId;
    std::string remixArtist;
    std::string remixStyle;

public:
    TrackRemix(const std::string& name,
               unsigned long long duration,
               unsigned long long coverID,
               const std::string& artistName,
               const std::string& genre,
               unsigned int releaseYear,
               const std::string& originalTrackId,
               const std::string& remixStyle);

    std::string getOriginalTrackId() const;
    std::string getRemixStyle() const;
    std::string getRemixArtist() const;

    void updateRemixStyle(const std::string& newStyle);
};

#endif // TRACK_REMIX_H