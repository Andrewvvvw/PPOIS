#ifndef SURVEY_H
#define SURVEY_H

#include <string>
#include <vector>
#include <map>
#include <chrono>

class Survey {
private:
    int id;
    std::string title;
    std::map<int, std::string> questions;
    std::map<int, std::map<int, int>> responses;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    bool isActive;

public:
    Survey(int id, const std::string& title, int durationDays = 7);

    bool addQuestion(int questionId, const std::string& questionText);
    bool submitResponse(int questionId, int optionId);
    void endSurvey();
    std::map<int, double> getResults() const;
    bool isOngoing() const;

    int getId() const;
    std::string getTitle() const;
    std::string getStatus() const;
};

#endif // SURVEY_H
