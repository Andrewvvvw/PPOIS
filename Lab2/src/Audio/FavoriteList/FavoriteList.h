#ifndef LAB2_FAVORITELIST_H
#define LAB2_FAVORITELIST_H

#include "../Audio.h"

class Audio;

class FavoriteList {
private:
    std::vector < std::shared_ptr <Audio> > tracks;
public:

    void addToFavorites(const std::shared_ptr <Audio>& audio);
    void removeFromFavorites(const std::shared_ptr<Audio>& audio);
    [[nodiscard]] const std::vector < std::shared_ptr <Audio> > &getTracks() const { return tracks; }

};

#endif //LAB2_FAVORITELIST_H
