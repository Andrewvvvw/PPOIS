#include "../../src/AudioCollection/SleepTimer/SleepTimer.h"
#include "UnitTest++.h"
#include <thread>

SUITE(SleepTimerTest) {
    TEST(TestConstructor) {
        SleepTimer timer;
                CHECK_EQUAL(0, timer.getRemainingTime());
                CHECK(!timer.isExpired());
    }

    TEST(TestSetDuration) {
        SleepTimer timer;
        timer.setDuration(1);
                CHECK_EQUAL(0, timer.getRemainingTime());
    }

    TEST(TestStartAndIsActive) {
        SleepTimer timer;
        timer.setDuration(1); // 1 second
        timer.start();
                CHECK(timer.getRemainingTime() > 0);
    }

    TEST(TestIsExpired) {
        SleepTimer timer;
        timer.setDuration(1); // 1 second
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1100)); // 1.1 seconds
                CHECK(timer.isExpired());
    }

    TEST(TestStop) {
        SleepTimer timer;
        timer.setDuration(10); // 10 seconds
        timer.start();
        timer.stop();
                CHECK_EQUAL(0, timer.getRemainingTime());
                CHECK(!timer.isExpired());
    }

    TEST(TestGetRemainingTime) {
        SleepTimer timer;
        timer.setDuration(2); // 2 seconds
        timer.start();
        int remaining = timer.getRemainingTime();
                CHECK(remaining > 0 && remaining <= 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(1100)); // 1.1 seconds
        int newRemaining = timer.getRemainingTime();
                CHECK(newRemaining < remaining);
    }

    TEST(TestPause) {
        SleepTimer timer;
        timer.setDuration(10); // 10 seconds
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 0.1 seconds
        timer.pause();
        int remainingAfterPause = timer.getRemainingTime();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                CHECK_EQUAL(remainingAfterPause, timer.getRemainingTime());
    }

    TEST(TestReset) {
        SleepTimer timer;
        timer.setDuration(5);
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int remainingBeforeReset = timer.getRemainingTime();
        timer.reset();
        int remainingAfterReset = timer.getRemainingTime();
                CHECK(remainingAfterReset >= remainingBeforeReset);
    }

    TEST(TestExpiredTimer) {
        SleepTimer timer;
        timer.setDuration(1);
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
                CHECK(timer.isExpired());
                CHECK_EQUAL(0, timer.getRemainingTime());
    }
}