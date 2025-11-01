#include "RegisteredUser.h"
#include <algorithm>
#include <string>

RegisteredUser::RegisteredUser(const std::string& id, const std::string& username,
                               const std::string& email, const std::string& password)
        : User(id, username), email(email), isPremium(false) {
    setPassword(password);
}

void RegisteredUser::setPassword(const std::string& newPassword) {
    password = newPassword;
}

bool RegisteredUser::verifyPassword(const std::string& inputPassword) const {
    return this->password == inputPassword;
}

bool RegisteredUser::createPlaylist(const std::string& playlistName) {
    // Check if playlist already exists
    if (std::find(playlists.begin(), playlists.end(), playlistName) != playlists.end()) {
        return false;
    }
    playlists.push_back(playlistName);
    return true;
}

bool RegisteredUser::deletePlaylist(const std::string& playlistName) {
    auto it = std::find(playlists.begin(), playlists.end(), playlistName);
    if (it != playlists.end()) {
        playlists.erase(it);
        return true;
    }
    return false;
}