#ifndef LAB2_USERSTATISTICS_H
#define LAB2_USERSTATISTICS_H

#include "../RegisteredUser.h"

class UserStatistics{
public:
    UserStatistics();
    std::string getFavoriteCreatorName(const RegisteredUser& user, const AudioCollection& audioCollection);
};

#endif //LAB2_USERSTATISTICS_H
