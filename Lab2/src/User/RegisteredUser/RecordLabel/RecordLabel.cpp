#include "RecordLabel.h"

RecordLabel::RecordLabel(const std::string& name) : name(name) {}

void RecordLabel::addArtist(const std::shared_ptr<Artist>& artist) {
    artists.push_back(artist);
}

void RecordLabel::removeArtist(const std::shared_ptr<Artist>& artist) {
    artists.erase(std::remove(artists.begin(), artists.end(), artist), artists.end());
}

std::vector<std::shared_ptr<Artist>> RecordLabel::getArtists() const {
    return artists;
}
