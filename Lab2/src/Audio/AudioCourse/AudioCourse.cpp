#include "AudioCourse.h"
#include <algorithm>
#include <numeric>

AudioCourse::AudioCourse(const std::string& title,
                       unsigned long long coverID,
                       const std::shared_ptr<Lecturer>& instructor,
                       const std::string& courseCode,
                       const std::string& description)
    : Audio(0, title, coverID),
      courseInstructor(instructor),
      courseCode(courseCode),
      description(description) {}

std::string AudioCourse::getAuthor() const {
    return courseInstructor ? courseInstructor->getUsername() : "Unknown Instructor";
}

bool AudioCourse::addLecture(const std::shared_ptr<AudioLecture>& lecture) {
    if (!lecture || hasLecture(lecture)) {
        return false;
    }

    if (lecture->getCourseCode() != courseCode) {
        return false;
    }

    lectures.push_back(lecture);
    return true;
}

bool AudioCourse::removeLecture(const std::shared_ptr<AudioLecture>& lecture) {
    if (!lecture) {
        return false;
    }

    auto it = std::find(lectures.begin(), lectures.end(), lecture);
    if (it != lectures.end()) {
        lectures.erase(it);
        return true;
    }
    return false;
}

bool AudioCourse::hasLecture(const std::shared_ptr<AudioLecture>& lecture) const {
    if (!lecture) {
        return false;
    }
    return std::find(lectures.begin(), lectures.end(), lecture) != lectures.end();
}

bool AudioCourse::addLearningObjective(const std::string& objective) {
    if (objective.empty()) {
        return false;
    }

    auto it = std::find(learningObjectives.begin(), learningObjectives.end(), objective);
    if (it == learningObjectives.end()) {
        learningObjectives.push_back(objective);
        return true;
    }
    return false;
}

bool AudioCourse::removeLearningObjective(const std::string& objective) {
    auto it = std::find(learningObjectives.begin(), learningObjectives.end(), objective);
    if (it != learningObjectives.end()) {
        learningObjectives.erase(it);
        return true;
    }
    return false;
}

bool AudioCourse::addPrerequisite(const std::string& prerequisite) {
    if (prerequisite.empty()) {
        return false;
    }

    auto it = std::find(prerequisites.begin(), prerequisites.end(), prerequisite);
    if (it == prerequisites.end()) {
        prerequisites.push_back(prerequisite);
        return true;
    }
    return false;
}

bool AudioCourse::removePrerequisite(const std::string& prerequisite) {
    auto it = std::find(prerequisites.begin(), prerequisites.end(), prerequisite);
    if (it != prerequisites.end()) {
        prerequisites.erase(it);
        return true;
    }
    return false;
}

unsigned long long AudioCourse::getTotalDuration() const {
    return std::accumulate(lectures.begin(), lectures.end(), 0ULL,
        [](unsigned long long sum, const std::shared_ptr<AudioLecture>& lecture) {
            return sum + (lecture ? lecture->getDuration() : 0);
        });
}
