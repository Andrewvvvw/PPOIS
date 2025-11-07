#ifndef REGISTERED_USER_H
#define REGISTERED_USER_H

#include "../User.h"
#include <string>
#include <vector>
#include <memory>

#include "SocialFunctions/SocialFunctionsManager.h"
#include "SubscriptionManager/UserWallet/UserWallet.h"
#include "UserStatistics/UserStatistics.h"
#include "../../AudioCollection/AudioCollection.h"
#include "../../Audio/FavoriteList/FavoriteList.h"

class SocialFunctionsManager;
class SubscriptionManager;
class UserProfile;

class RegisteredUser : public User, public std::enable_shared_from_this<RegisteredUser> {
protected:
    std::string email;
    std::string password;
    SocialFunctionsManager socialFunctions;
    std::unique_ptr<SubscriptionManager> subscriptionManager;
    std::unique_ptr<UserProfile> userProfile;
    FavoriteList favoriteList;

public:
    RegisteredUser(const std::string& id, const std::string& username,
                   const std::string& email, const std::string& password);
    ~RegisteredUser();

    [[nodiscard]] std::string getPassword() const;
    [[nodiscard]] std::string getEmail() const;
    void setEmail(const std::string& newEmail);
    void setPassword(const std::string& newPassword);

    [[nodiscard]] bool canUploadContent() const override;
    [[nodiscard]] bool canComment() const override;
    [[nodiscard]] std::string getUserType() const override;

    [[nodiscard]] SocialFunctionsManager* getSocialFunctionsManager();

    [[nodiscard]] virtual bool getIsPremium() const override;
    void setPremium(bool premium);

    std::vector <std::shared_ptr<Audio> > getFavoriteTracks();
    void addToFavorites(const std::shared_ptr<Audio>& audio);
    void removeFromFavorites(const std::shared_ptr<Audio>& audio);
};

#endif // REGISTERED_USER_H