#include "Artist.h"
#include <algorithm>

Artist::Artist(const std::string& id,
               const std::string& username,
               const std::string& email,
               const std::string& password,
               const std::string& artistName)
        : RegisteredUser(id, username, email, password),
          artistName(artistName),
          monthlyListeners(0) {}

void Artist::updateBiography(const std::string& newBio) {
    biography = newBio;
}

void Artist::updateMonthlyListeners(int change) {
    if (change > 0) {
        monthlyListeners += static_cast<unsigned int>(change);
    } else if (monthlyListeners >= static_cast<unsigned int>(-change)) {
        monthlyListeners -= static_cast<unsigned int>(-change);
    } else {
        monthlyListeners = 0;
    }
}

bool Artist::createAlbum(const std::string& title,
                         unsigned int releaseYear,
                         unsigned long long coverId) {
    for (const auto& album : albums) {
        if (album->getTitle() == title) {
            return false;
        }
    }

    albums.push_back(std::make_shared<Album>(title,
                                             artistName,
                                             releaseYear,
                                             coverId));
    return true;
}

bool Artist::addTrackToAlbum(const std::string& albumTitle,
                             const std::shared_ptr<MusicTrack>& track) {
    if (!track) return false;

    for (auto& album : albums) {
        if (album->getTitle() == albumTitle) {
            album->addTrack(track);
            return true;
        }
    }

    return false;
}

bool Artist::addRemixToAlbum(const std::string& albumTitle,
                             const std::shared_ptr<TrackRemix>& remix) {
    if (!remix) return false;

    for (auto& album : albums) {
        if (album->getTitle() == albumTitle) {
            album->addRemix(remix);
            return true;
        }
    }

    return false;
}

std::vector<std::string> Artist::getAlbumTitles() const {
    std::vector<std::string> titles;
    for (const auto& album : albums) {
        titles.push_back(album->getTitle());
    }
    return titles;
}

std::shared_ptr<Album> Artist::getAlbum(const std::string& title) const {
    for (const auto& album : albums) {
        if (album->getTitle() == title) {
            return album;
        }
    }
    return nullptr;
}