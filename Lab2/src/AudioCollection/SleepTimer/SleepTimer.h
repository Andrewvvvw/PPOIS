#ifndef SLEEPTIMER_H
#define SLEEPTIMER_H

#include <chrono>

class SleepTimer {
private:
    std::chrono::seconds duration_;
    std::chrono::time_point <std::chrono::steady_clock> startTime_;
    bool isActive_;

public:
    SleepTimer();
    void setDuration(int seconds);
    void start();
    void stop();
    bool isExpired() const;
    int getRemainingTime() const;
    void pause();
    void reset();
};

#endif // SLEEPTIMER_H