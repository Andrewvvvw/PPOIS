#include "SleepTimer.h"

SleepTimer::SleepTimer() : duration_(0), isActive_(false) {}

void SleepTimer::setDuration(int seconds) {
    duration_ = std::chrono::seconds(seconds);
}

void SleepTimer::start() {
    startTime_ = std::chrono::steady_clock::now();
    isActive_ = true;
}

void SleepTimer::stop() {
    isActive_ = false;
}

bool SleepTimer::isExpired() const {
    if (!isActive_) return false;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            currentTime - startTime_);
    return elapsed >= duration_;
}

int SleepTimer::getRemainingTime() const {
    if (!isActive_) return 0;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            currentTime - startTime_);
    int remaining = (duration_ - elapsed).count();
    return remaining > 0 ? remaining : 0;
}

void SleepTimer::pause() {
    if (isActive_) {
        duration_ = std::chrono::seconds(getRemainingTime());
        isActive_ = false;
    }
}

void SleepTimer::reset() {
    if (isActive_) {
        startTime_ = std::chrono::steady_clock::now();
    }
}