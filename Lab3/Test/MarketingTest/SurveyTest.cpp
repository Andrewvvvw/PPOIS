#include "UnitTest++.h"
#include "../../Source/Marketing/Survey/Survey.h"
#include <chrono>

using namespace std::chrono_literals;

TEST(Survey_Constructor) {
    Survey survey(1, "Customer Satisfaction", 7);

            CHECK_EQUAL(1, survey.getId());
            CHECK_EQUAL("Customer Satisfaction", survey.getTitle());
            CHECK_EQUAL("Active", survey.getStatus());
            CHECK(survey.isOngoing());
}

TEST(Survey_AddQuestion) {
    Survey survey(1, "Product Feedback");

            CHECK(survey.addQuestion(1, "How would you rate our product?"));
            CHECK(survey.addQuestion(2, "How likely are you to recommend us?"));
            CHECK(!survey.addQuestion(1, "Duplicate ID"));
}

TEST(Survey_SubmitResponse) {
    Survey survey(1, "Product Feedback");
    survey.addQuestion(1, "How would you rate our product?");
    survey.addQuestion(2, "How likely are you to recommend us?");

            CHECK(survey.submitResponse(1, 5));
            CHECK(survey.submitResponse(1, 4));
            CHECK(survey.submitResponse(2, 3));
            CHECK(!survey.submitResponse(3, 5));
}

TEST(Survey_GetResults) {
    Survey survey(1, "Product Feedback");
    survey.addQuestion(1, "How would you rate our product?");

    survey.submitResponse(1, 5);
    survey.submitResponse(1, 4);
    survey.submitResponse(1, 5);
    survey.submitResponse(1, 3);

    auto results = survey.getResults();
            CHECK_EQUAL(1, results.size());
            CHECK_CLOSE(4.25, results[1], 0.01);
}

TEST(Survey_EndSurvey) {
    Survey survey(1, "Ending Soon");

            CHECK(survey.isOngoing());
    survey.endSurvey();
            CHECK(!survey.isOngoing());
            CHECK_EQUAL("Completed", survey.getStatus());

    survey.addQuestion(1, "Test question");
            CHECK(!survey.submitResponse(1, 5));
}

TEST(Survey_IsOngoing) {
    auto now = std::chrono::system_clock::now();
    auto past = now - 24h;
    auto future = now + 24h;

    Survey activeSurvey(1, "Active Survey");
            CHECK(activeSurvey.isOngoing());

    activeSurvey.endSurvey();
            CHECK(!activeSurvey.isOngoing());
}

TEST(Survey_GetStatus) {
    Survey survey(1, "Status Test");

            CHECK_EQUAL("Active", survey.getStatus());
    survey.endSurvey();
            CHECK_EQUAL("Completed", survey.getStatus());
}

TEST(Survey_MultipleResponses) {
    Survey survey(1, "Multiple Responses");
    survey.addQuestion(1, "Rate our service");

    for (int i = 0; i < 5; i++) {
                CHECK(survey.submitResponse(1, 5));
    }

    survey.submitResponse(1, 4);
    survey.submitResponse(1, 3);

    auto results = survey.getResults();
            CHECK_CLOSE(4.57, results[1], 0.01);
}

TEST(Survey_NoResponses) {
    Survey survey(1, "No Responses");
    survey.addQuestion(1, "Unanswered question");

    auto results = survey.getResults();
            CHECK_EQUAL(1, results.size());
            CHECK_EQUAL(0.0, results[1]);
}

TEST(Survey_QuestionManagement) {
    Survey survey(1, "Question Management");

            CHECK(survey.addQuestion(1, "Question 1"));
            CHECK(survey.addQuestion(2, "Question 2"));

            CHECK(!survey.addQuestion(1, "Duplicate Question"));

            CHECK(survey.submitResponse(1, 5));
            CHECK(survey.submitResponse(2, 3));

    auto results = survey.getResults();
            CHECK_EQUAL(2, results.size());
            CHECK_EQUAL(5.0, results[1]);
            CHECK_EQUAL(3.0, results[2]);
}