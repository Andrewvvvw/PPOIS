#ifndef LAB2_USERSTATISTICS_H
#define LAB2_USERSTATISTICS_H

#include "../RegisteredUser.h"
#include "../Artist/Artist.h"

class UserStatistics{
private:
    RegisteredUser user;
public:
    UserStatistics(RegisteredUser user) : user(user) {};

    int getNumberOfPlaylists();
    std::string getFavoriteCreatorName();
};

#endif //LAB2_USERSTATISTICS_H
