#ifndef LAB2_ADMANAGER_H
#define LAB2_ADMANAGER_H

#include "Advertisement/Advertisement.h"
#include "vector"
#include "../../User/User.h"

class User;

class AdManager {
private:
    bool hasPremium;
    std::vector <Advertisement> advertisements;
public:
    AdManager(User& user);

    void addAdvertisement(const Advertisement& advertisement);
    void removeAdvertisement(const Advertisement& advertisement);

    std::vector<Advertisement> getAdvertisements() const;

    std::string showAd(int index);
};

#endif //LAB2_ADMANAGER_H
