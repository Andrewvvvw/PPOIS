#ifndef MUSIC_TRACK_H
#define MUSIC_TRACK_H

#include "../../Audio.h"
#include <string>

class SongWriter;

class MusicTrack : public Audio {
private:
    std::string artistName;
    std::string genre;
    unsigned int releaseYear;
    std::shared_ptr<SongWriter> songWriter;

public:
    MusicTrack(const std::string& name,
               unsigned long long duration,
               unsigned long long coverID,
               const std::string& artistName,
               const std::string& genre,
               unsigned int releaseYear);

    std::string getAuthor() const override;
    std::string getGenre() const;
    unsigned int getReleaseYear() const;
    std::shared_ptr<SongWriter> getSongWriter() const;

    void updateGenre(const std::string& newGenre);
    bool isClassic() const;
};

#endif // MUSIC_TRACK_H