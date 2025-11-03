#ifndef RECORDLABEL_H
#define RECORDLABEL_H

#include <string>
#include "../Artist/Artist.h"
#include "vector"
#include "memory"

class RecordLabel {
private:
    std::string name;
    std::vector <std::shared_ptr<Artist> > artists;
public:
    RecordLabel(const std::string& name);
    void addArtist(const std::shared_ptr<Artist>& artist);
    void removeArtist(const std::shared_ptr<Artist>& artist);
    std::vector<std::shared_ptr<Artist>> getArtists() const;
};

#endif //RECORDLABEL_H
