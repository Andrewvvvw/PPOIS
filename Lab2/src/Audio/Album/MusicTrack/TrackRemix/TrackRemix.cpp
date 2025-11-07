#include "TrackRemix.h"

TrackRemix::TrackRemix(const std::string& name,
                       unsigned long long duration,
                       unsigned long long coverID,
                       const std::string& artistName,
                       const std::string& genre,
                       unsigned int releaseYear,
                       const std::string& originalTrackId,
                       const std::string& remixStyle)
        : MusicTrack(name, duration, coverID, artistName, genre, releaseYear),
          originalTrackId(originalTrackId),
          remixArtist(artistName),
          remixStyle(remixStyle) {}

void TrackRemix::updateRemixStyle(const std::string& newStyle) {
    remixStyle = newStyle;
}

std::string TrackRemix::getOriginalTrackId() const {
    return originalTrackId;
}

std::string TrackRemix::getRemixStyle() const {
    return remixStyle;
}

std::string TrackRemix::getRemixArtist() const {
    return remixArtist;
}
