#ifndef LAB2_RADIOHOST_H
#define LAB2_RADIOHOST_H

#include "../RegisteredUser.h"
#include "../../../Audio/Radio/Radio.h"

class RadioHost : public RegisteredUser{
private:
    std::vector<std::shared_ptr<Radio>> hostedRadios;
    std::string favoriteGenre;
    std::string favoriteStation;
public:
    RadioHost(const std::string& id,
              const std::string& username,
              const std::string& email,
              const std::string& password,
              const std::string& favoriteGenre,
              const std::string& favoriteStation);

    void addRadio(std::shared_ptr<Radio> radio);
    void removeRadio(std::shared_ptr<Radio> radio);

    std::vector<std::shared_ptr<Radio>> getHostedRadios() const;
    std::string getFavoriteGenre() const;
    std::string getFavoriteStation() const;

    void setFavoriteGenre(const std::string& genre);
    void setFavoriteStation(const std::string& station);

};

#endif //LAB2_RADIOHOST_H
