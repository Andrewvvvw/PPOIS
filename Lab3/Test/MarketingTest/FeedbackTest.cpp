#include "UnitTest++.h"
#include "../../Source/Marketing/Feedback/Feedback.h"
#include <chrono>
#include <thread>

TEST(Feedback_Constructor) {
    Feedback feedback(1, 1001, 5, "Great service!");

            CHECK_EQUAL(1, feedback.getId());
            CHECK_EQUAL(1001, feedback.getCustomerId());
            CHECK_EQUAL(5, feedback.getRating());
            CHECK_EQUAL("Great service!", feedback.getComment());
            CHECK(!feedback.isVerifiedPurchase());
            CHECK(feedback.isRecent());
}

TEST(Feedback_Verify) {
    Feedback feedback(2, 1002, 4, "Good, but could be better");

            CHECK(feedback.verify());
            CHECK(feedback.isVerifiedPurchase());

            CHECK(!feedback.verify());
            CHECK(feedback.isVerifiedPurchase());
}

TEST(Feedback_SetRating) {
    Feedback feedback(3, 1003, 3, "Average");

    feedback.setRating(5);
            CHECK_EQUAL(5, feedback.getRating());

    feedback.setRating(0);
            CHECK_EQUAL(5, feedback.getRating());

    feedback.setRating(6);
            CHECK_EQUAL(5, feedback.getRating());

    feedback.setRating(1);
            CHECK_EQUAL(1, feedback.getRating());
}

TEST(Feedback_IsRecent) {
    Feedback feedback(4, 1004, 5, "Test recent feedback");

            CHECK(feedback.isRecent());
}

TEST(Feedback_GetMethods) {
    Feedback feedback(6, 1006, 4, "Test getters");

            CHECK_EQUAL(6, feedback.getId());
            CHECK_EQUAL(1006, feedback.getCustomerId());
            CHECK_EQUAL(4, feedback.getRating());
            CHECK_EQUAL("Test getters", feedback.getComment());
}

TEST(Feedback_VerifyAfterSetRating) {
    Feedback feedback(7, 1007, 3, "Will be updated");

    feedback.verify();
            CHECK(feedback.isVerifiedPurchase());

    feedback.setRating(5);
            CHECK(feedback.isVerifiedPurchase());
            CHECK_EQUAL(5, feedback.getRating());
}