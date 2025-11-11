#include "Survey.h"

Survey::Survey(int id, const std::string& title, int durationDays)
    : id(id), title(title), isActive(true) {
    startDate = std::chrono::system_clock::now();
    endDate = startDate + std::chrono::hours(24 * durationDays);
}

bool Survey::addQuestion(int questionId, const std::string& questionText) {
    if (questions.find(questionId) != questions.end()) {
        return false;
    }
    questions[questionId] = questionText;
    responses[questionId] = std::map<int, int>();
    return true;
}

bool Survey::submitResponse(int questionId, int optionId) {
    if (!isOngoing() || questions.find(questionId) == questions.end()) {
        return false;
    }
    responses[questionId][optionId]++;
    return true;
}

void Survey::endSurvey() {
    isActive = false;
    endDate = std::chrono::system_clock::now();
}

std::map<int, double> Survey::getResults() const {
    std::map<int, double> results;
    for (const auto& question : questions) {
        int totalResponses = 0;
        for (const auto& response : responses.at(question.first)) {
            totalResponses += response.second;
        }

        double average = 0.0;
        if (totalResponses > 0) {
            double sum = 0.0;
            for (const auto& response : responses.at(question.first)) {
                sum += response.first * response.second;
            }
            average = sum / totalResponses;
        }
        results[question.first] = average;
    }
    return results;
}

bool Survey::isOngoing() const {
    auto now = std::chrono::system_clock::now();
    return isActive && now >= startDate && now <= endDate;
}

int Survey::getId() const {
    return id;
}

std::string Survey::getTitle() const {
    return title;
}

std::string Survey::getStatus() const {
    if (!isActive) return "Completed";
    auto now = std::chrono::system_clock::now();
    if (now < startDate) return "Scheduled";
    if (now > endDate) return "Expired";
    return "Active";
}
