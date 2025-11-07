#include "Guest.h"
#include <ctime>

Guest::Guest() : User("guest_" + std::to_string(time(nullptr)), "Guest"), viewLimit(0) {
    sessionStartTime = time(nullptr);
}

time_t Guest::getSessionDuration() const {
    return time(nullptr) - sessionStartTime;
}

bool Guest::canViewContent() const {
    return viewLimit < 10;
}

void Guest::incrementViewCount() {
    if (viewLimit < 10) {
        viewLimit++;
    }
}

bool Guest::getIsPremium() const {
    return false;
}

bool Guest::canComment() const {
    return false;
}

std::string Guest::getUserType() const {
    return "Guest";
}

unsigned int Guest::getViewLimit() const {
    return viewLimit;
}
