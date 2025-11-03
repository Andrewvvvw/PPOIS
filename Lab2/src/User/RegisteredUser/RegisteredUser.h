#ifndef REGISTERED_USER_H
#define REGISTERED_USER_H

#include "../User.h"
#include <string>
#include <vector>
#include "SocialFunctions/SocialFunctionsManager.h"
#include "SubscriptionManager/SubscriptionManager.h"
#include "SubscriptionManager/UserWallet/UserWallet.h"
#include "UserProfile/UserProfile.h"
#include "UserStatistics/UserStatistics.h"
#include "../../AudioCollection/AudioCollection.h"

class RegisteredUser : public User {
protected:
    std::string email;
    std::string password;
    SocialFunctionsManager socialFunctions;
    SubscriptionManager subscriptionManager;
    UserProfile userProfile;
    UserStatistics userStatistics;

public:
    RegisteredUser(const std::string& id, const std::string& username,
                   const std::string& email, const std::string& password);

    [[nodiscard]] std::string getEmail() const { return email; }

    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setPassword(const std::string& newPassword);

    [[nodiscard]] bool canUploadContent() const override { return false; }
    [[nodiscard]] bool canComment() const override { return true; }
    [[nodiscard]] std::string getUserType() const override { return "RegisteredUser"; }

    [[nodiscard]] bool verifyPassword(const std::string& inputPassword) const;

    [[nodiscard]] SocialFunctionsManager* getSocialFunctionsManager() { return &socialFunctions; }

    [[nodiscard]] virtual bool getIsPremium() const override;
    void setPremium(bool premium);
};

#endif // REGISTERED_USER_H