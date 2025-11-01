#ifndef MUSIC_TRACK_H
#define MUSIC_TRACK_H

#include "../../Audio.h"
#include <string>

class MusicTrack : public Audio {
private:
    std::string artistName;
    std::string genre;
    unsigned int releaseYear;

public:
    MusicTrack(const std::string& name,
               unsigned long long duration,
               unsigned long long coverID,
               const std::string& artistName,
               const std::string& genre,
               unsigned int releaseYear);

    std::string getAuthor() const override { return artistName; }
    std::string getGenre() const { return genre; }
    unsigned int getReleaseYear() const { return releaseYear; }

    void updateGenre(const std::string& newGenre);
    bool isClassic() const;
};

#endif // MUSIC_TRACK_H