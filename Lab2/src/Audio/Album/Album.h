#ifndef ALBUM_H
#define ALBUM_H

#include "MusicTrack/MusicTrack.h"
#include "MusicTrack/TrackRemix/TrackRemix.h"
#include <vector>
#include <string>
#include <memory>

class Album {
private:
    std::string title;
    std::string artist;
    unsigned int releaseYear;
    std::vector<std::shared_ptr<MusicTrack>> tracks;
    std::vector<std::shared_ptr<TrackRemix>> remixes;
    unsigned long long coverId;

public:
    Album(const std::string& title,
          const std::string& artist,
          unsigned int releaseYear,
          unsigned long long coverId);

    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    unsigned int getReleaseYear() const { return releaseYear; }
    unsigned long long getCoverId() const { return coverId; }

    void addTrack(const std::shared_ptr<MusicTrack>& track);
    void addRemix(const std::shared_ptr<TrackRemix>& remix);
    bool removeTrack(const std::string& trackName);

    unsigned int getTotalTracks() const;
    unsigned long long getTotalDuration() const;
    std::vector<std::string> getTrackList() const;
};

#endif // ALBUM_H