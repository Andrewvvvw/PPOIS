#include "Radio.h"
#include <limits>

Radio::Radio(std::string genre,
             std::string station,
             std::shared_ptr<RadioHost> host,
          const std::string& title,
          const std::string& description,
          unsigned long long coverID) :
        Audio(std::numeric_limits<unsigned long long>::max(),title, coverID),
        genre(genre),
        station(station),
        host(host) {}

void Radio::setGenre(const std::string& genre) {
    this->genre = genre;
}

void Radio::setStation(const std::string& station) {
    this->station = station;
}

void Radio::setHost(const std::shared_ptr<RadioHost> &host) {
    this->host = host;
}

std::string Radio::getGenre() const {
    return genre;
}

std::string Radio::getStation() const {
    return station;
}

std::shared_ptr<RadioHost> Radio::getHost() const {
    return host;
}

void Radio::changeStation(const std::string newStation) {
    station = newStation;
}