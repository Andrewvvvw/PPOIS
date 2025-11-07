#include "RegisteredUser.h"
#include "../../Exceptions/Exceptions.h"
#include "SocialFunctions/SocialFunctionsManager.h"


#include "SubscriptionManager/SubscriptionManager.h"
#include "SubscriptionManager/UserWallet/UserWallet.h"
#include "UserProfile/UserProfile.h"
#include "UserStatistics/UserStatistics.h"
#include "../../Audio/FavoriteList/FavoriteList.h"
#include <memory>

RegisteredUser::RegisteredUser(const std::string& id, const std::string& username,
                               const std::string& email, const std::string& password)
        : User(id, username),
        email(email),
        password(password),
        socialFunctions(this),
        favoriteList(),
        userProfile(std::make_unique <UserProfile> (this, "", "", ""))
{
    auto wallet = std::make_unique<UserWallet>(this, 0.0);
    subscriptionManager = std::make_unique<SubscriptionManager>(this, std::move(wallet));
}

RegisteredUser::~RegisteredUser() = default;

void RegisteredUser::setPassword(const std::string& newPassword) {
    if(newPassword.empty())
        throw ExceptionIncorrectPassword("Password can't be empty");
    password = newPassword;
}

bool RegisteredUser::getIsPremium() const {
    return this->subscriptionManager->checkForPremium();
}

void RegisteredUser::setPremium(bool premium) {
    premium ? this->subscriptionManager->getPremium() : this->subscriptionManager->cancelPremium();
}

void RegisteredUser::setEmail(const std::string &newEmail) {
    if(newEmail.empty())
        throw ExceptionIncorrectEmail("Email can't be empty");
    email = newEmail;
}

std::string RegisteredUser::getPassword() const {
    return password;
}

std::string RegisteredUser::getEmail() const {
    return email;
}

bool RegisteredUser::canUploadContent() const {
    return false;
}

bool RegisteredUser::canComment() const {
    return true;
}

std::string RegisteredUser::getUserType() const {
    return "RegisteredUser";
}

SocialFunctionsManager* RegisteredUser::getSocialFunctionsManager() {
    return &socialFunctions;
}

std::vector <std::shared_ptr<Audio> > RegisteredUser::getFavoriteTracks() {
    return this->favoriteList.getTracks();
}

void RegisteredUser::addToFavorites(const std::shared_ptr<Audio>& audio) {
    this->favoriteList.addToFavorites(audio);
}

void RegisteredUser::removeFromFavorites(const std::shared_ptr<Audio>& audio) {
    this->favoriteList.removeFromFavorites(audio);
}
