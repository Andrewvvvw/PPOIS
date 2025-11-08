#include "RadioHost.h"
#include <memory>
RadioHost::RadioHost(const std::string& id,
                     const std::string& username,
                     const std::string& email,
                     const std::string& password,
                     const std::string& favoriteGenre,
                     const std::string& favoriteStation) :
    RegisteredUser(id, username, email, password),
    favoriteGenre(favoriteGenre),
    favoriteStation(favoriteStation) {}

void RadioHost::addRadio(std::shared_ptr<Radio> radio) {
    hostedRadios.push_back(radio);
}

void RadioHost::removeRadio(std::shared_ptr<Radio> radio) {
    hostedRadios.erase(std::remove(hostedRadios.begin(), hostedRadios.end(), radio), hostedRadios.end());
}

std::vector<std::shared_ptr<Radio>> RadioHost::getHostedRadios() const {
    return hostedRadios;
}

std::string RadioHost::getFavoriteGenre() const {
    return favoriteGenre;
}

std::string RadioHost::getFavoriteStation() const {
    return favoriteStation;
}

void RadioHost::setFavoriteGenre(const std::string& genre) {
    favoriteGenre = genre;
}

void RadioHost::setFavoriteStation(const std::string& station) {
    favoriteStation = station;
}