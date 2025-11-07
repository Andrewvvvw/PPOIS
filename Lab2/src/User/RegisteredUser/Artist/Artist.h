#ifndef ARTIST_H
#define ARTIST_H

#include "../RegisteredUser.h"
#include <vector>
#include <memory>
#include <string>

class Album;
class MusicTrack;
class TrackRemix;
class RegisteredUser;

class Artist : public RegisteredUser {
private:
    std::string artistName;
    std::string biography;
    std::vector <std::shared_ptr <Album> > albums;
    std::vector <std::shared_ptr <MusicTrack> > singles;
    unsigned int monthlyListeners;

public:
    Artist(const std::string& id,
          const std::string& username,
          const std::string& email,
          const std::string& password,
          const std::string& artistName);

    std::string getArtistName() const;
    std::string getBiography() const;
    unsigned int getMonthlyListeners() const;

    void updateBiography(const std::string& newBio);
    void updateMonthlyListeners(int change);

    void createAlbum(const std::string& title,
                    unsigned int releaseYear,
                    unsigned long long coverId);

    bool addTrackToAlbum(const std::string& albumTitle,
                        const std::shared_ptr<MusicTrack>& track);

    bool addRemixToAlbum(const std::string& albumTitle,
                        const std::shared_ptr<TrackRemix>& remix);

    std::vector<std::string> getAlbumTitles() const;
    std::shared_ptr<Album> getAlbum(const std::string& title) const;

    std::string getUserType() const override;
    bool canUploadContent() const override;
};

#endif // ARTIST_H
