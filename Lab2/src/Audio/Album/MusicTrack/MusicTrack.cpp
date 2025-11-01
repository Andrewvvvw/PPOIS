#include "MusicTrack.h"
#include <ctime>

MusicTrack::MusicTrack(const std::string& name,
                       unsigned long long duration,
                       unsigned long long coverID,
                       const std::string& artistName,
                       const std::string& genre,
                       unsigned int releaseYear)
        : Audio(duration, name, coverID),
          artistName(artistName),
          genre(genre),
          releaseYear(releaseYear) {}

void MusicTrack::updateGenre(const std::string& newGenre) {
    genre = newGenre;
}

bool MusicTrack::isClassic() const {
    const int CLASSIC_YEAR_THRESHOLD = 25;
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    int currentYear = timeinfo->tm_year + 1900;

    return (currentYear - releaseYear) >= CLASSIC_YEAR_THRESHOLD;
}