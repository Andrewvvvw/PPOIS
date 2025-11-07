#include "Album.h"
#include <algorithm>
#include "../../Exceptions/Exceptions.h"

Album::Album(const std::string& title,
             const std::string& artist,
             unsigned int releaseYear,
             unsigned long long coverId) :
        artist(artist),
        releaseYear(releaseYear),
        coverId(coverId) {
    if(title.empty())
        throw ExceptionIncorrectAlbumTitle("Album title can't be empty");
    this->title = title;
}

void Album::addTrack(const std::shared_ptr <MusicTrack>& track) {
    if (track)
        tracks.push_back(track);
    else
        throw ExceptionIncorrectTrack("Track can't be empty");
}

void Album::addRemix(const std::shared_ptr <TrackRemix>& remix) {
    if (remix)
        remixes.push_back(remix);
    else
        throw ExceptionIncorrectTrack("Track can't be empty");
}

bool Album::removeTrack(const std::string& trackName) {
    auto trackIt = std::find_if(tracks.begin(), tracks.end(),
                                [&](const auto& track) { return track->getName() == trackName; });

    if (trackIt != tracks.end()) {
        tracks.erase(trackIt);
        return true;
    }

    auto remixIt = std::find_if(remixes.begin(), remixes.end(),
                                [&](const auto& remix) { return remix->getName() == trackName; });

    if (remixIt != remixes.end()) {
        remixes.erase(remixIt);
        return true;
    }

    return false;
}

unsigned int Album::getTotalTracks() const {
    return static_cast<unsigned int>(tracks.size() + remixes.size());
}

unsigned long long Album::getTotalDuration() const {
    unsigned long long total = 0;

    for (const auto& track : tracks) {
        total += track->getDuration();
    }

    for (const auto& remix : remixes) {
        total += remix->getDuration();
    }

    return total;
}

std::vector<std::string> Album::getTrackList() const {
    std::vector<std::string> trackList;

    for (const auto& track : tracks) {
        trackList.push_back(track->getName());
    }

    for (const auto& remix : remixes) {
        trackList.push_back(remix->getName() + " (Remix)");
    }

    return trackList;
}

std::string Album::getTitle() const {
    return title;
}

std::string Album::getArtist() const {
    return artist;
}

unsigned int Album::getReleaseYear() const {
    return releaseYear;
}

unsigned long long Album::getCoverId() const {
    return coverId;
}
