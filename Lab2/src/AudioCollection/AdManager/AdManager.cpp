#include "AdManager.h"
#include "algorithm"

AdManager::AdManager(User& user) {
    this->advertisements = std::vector<Advertisement>();
    this->hasPremium = user.getIsPremium();
}

void AdManager::addAdvertisement(const Advertisement& advertisement) {
    this->advertisements.push_back(advertisement);
}

void AdManager::removeAdvertisement(const Advertisement& advertisement) {
    auto ad = std::find(
                    this->advertisements.begin(),
                    this->advertisements.end(),
                    advertisement
                    );
    if(ad != this->advertisements.end()) {
        this->advertisements.erase(ad);
    }
}

std::vector<Advertisement> AdManager::getAdvertisements() const {
    return this->advertisements;
}

std::string AdManager::showAd(int index) {
    if(index < 0 || index >= this->advertisements.size()) {
        throw std::runtime_error("Wrong index");
    }
    if(this->hasPremium)
        throw std::runtime_error("User is not premium");
    else
        return this->advertisements[index].getContent();
}
