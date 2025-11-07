#ifndef LAB2_RADIO_H
#define LAB2_RADIO_H

#include "../Audio.h"
#include "../../User/RegisteredUser/RadioHost/RadioHost.h"
#include <string>

class Radio: public Audio {
private:
    std::string genre;
    std::string station;
    std::shared_ptr<RadioHost> host;
public:
    Radio(std::string genre,
          std::string station,
          std::shared_ptr<RadioHost> host,
          const std::string& title,
          const std::string& description,
          unsigned long long coverID);

    std::string getAuthor() const override;

    void setGenre(const std::string& genre);
    void setStation(const std::string& station);
    void setHost(const std::shared_ptr<RadioHost>& host);

    std::string getGenre() const;
    std::string getStation() const;
    std::shared_ptr<RadioHost> getHost() const;

    void changeStation(const std::string newStation);
};

#endif //LAB2_RADIO_H
