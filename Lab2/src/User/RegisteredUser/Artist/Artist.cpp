#include "Artist.h"
#include <algorithm>
#include "../../../Exceptions/Exceptions.h"
#include "../../../Audio/Album/MusicTrack/MusicTrack.h"
#include "../RegisteredUser.h"
#include "../../../Audio/Album/Album.h"

Artist::Artist(const std::string& id,
               const std::string& username,
               const std::string& email,
               const std::string& password,
               const std::string& artistName)
        : RegisteredUser(id, username, email, password),
          monthlyListeners(0) {
    if(artistName.empty())
        throw ExceptionIncorrectArtistName("ArtistName can't be empty");
    this->artistName = artistName;
}

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

void Artist::createAlbum(const std::string& title,
                         unsigned int releaseYear,
                         unsigned long long coverId) {
    if(releaseYear > 2025 || releaseYear < 1950)
        throw ExceptionIncorrectYear("Incorrect release year");

    for (const auto& album : albums) {
        if (album->getTitle() == title) {
            throw ExceptionIncorrectAlbumTitle("Album with this title already exists");
        }
    }

    if(title.empty())
        throw ExceptionIncorrectAlbumTitle("Album title can't be empty");

    albums.push_back(std::make_shared<Album>(title,
                                             artistName,
                                             releaseYear,
                                             coverId));
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
    std::vector <std::string> titles;
    for (const auto& album : albums) {
        titles.push_back(album->getTitle());
    }
    return titles;
}

std::shared_ptr <Album> Artist::getAlbum(const std::string& title) const {
    for (const auto& album : albums) {
        if (album->getTitle() == title) {
            return album;
        }
    }
    return nullptr;
}

std::string Artist::getUserType() const {
    return "Artist";
}

bool Artist::canUploadContent() const {
    return true;
}

std::string Artist::getArtistName() const {
    return artistName;
}

std::string Artist::getBiography() const {
    return biography;
}

unsigned int Artist::getMonthlyListeners() const {
    return monthlyListeners;
}
