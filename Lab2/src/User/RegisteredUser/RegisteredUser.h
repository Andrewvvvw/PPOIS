#ifndef REGISTERED_USER_H
#define REGISTERED_USER_H

#include "../User.h"
#include <string>
#include <vector>

class RegisteredUser : public User {
protected:
    std::string email;
    std::string password;
    bool isPremium;
    std::vector<std::string> playlists;

public:
    RegisteredUser(const std::string& id, const std::string& username,
                   const std::string& email, const std::string& password);

    [[nodiscard]] std::string getEmail() const { return email; }
    [[nodiscard]] bool getIsPremium() const { return isPremium; }

    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setPassword(const std::string& newPassword);
    void upgradeToPremium() { isPremium = true; }

    [[nodiscard]] bool canUploadContent() const override { return false; }
    [[nodiscard]] bool canComment() const override { return true; }
    [[nodiscard]] std::string getUserType() const override { return "RegisteredUser"; }

    bool createPlaylist(const std::string& playlistName);
    bool deletePlaylist(const std::string& playlistName);
    [[nodiscard]] const std::vector<std::string>& getPlaylists() const { return playlists; }

    [[nodiscard]] bool verifyPassword(const std::string& inputPassword) const;
};

#endif // REGISTERED_USER_H