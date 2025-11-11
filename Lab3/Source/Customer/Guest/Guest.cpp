#include "Guest.h"

Guest::Guest(const std::string& name, int id, const std::string& email)
    : Customer(name, id), email(email), visitCount(0), newsletterSubscribed(false) {}

void Guest::incrementVisitCount() {
    visitCount++;
}

void Guest::subscribeToNewsletter() {
    newsletterSubscribed = true;
}

void Guest::addPreference(const std::string& preference) {
    preferences.push_back(preference);
}

bool Guest::hasPreference(const std::string& preference) const {
    return std::find(preferences.begin(), preferences.end(), preference) != preferences.end();
}
