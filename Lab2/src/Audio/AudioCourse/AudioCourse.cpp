#include "AudioCourse.h"
#include "AudioLecture/AudioLecture.h"
#include <algorithm>
#include <numeric>

AudioCourse::AudioCourse(const std::string& title,
                       unsigned long long coverID,
                       const std::string& courseCode,
                       const std::string& description)
    : Audio(0, title, coverID),
      courseCode(courseCode),
      description(description) {}

std::string AudioCourse::getAuthor() const {
    if (lectures.empty()) {
        return "No authors";
    }
    return lectures[0]->getAuthor();
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

const std::string& AudioCourse::getCourseCode() const {
    return courseCode;
}

const std::string& AudioCourse::getDescription() const {
    return description;
}

const std::vector<std::string>& AudioCourse::getLearningObjectives() const {
    return learningObjectives;
}

const std::vector<std::string>& AudioCourse::getPrerequisites() const {
    return prerequisites;
}

std::vector <std::shared_ptr <AudioLecture> > AudioCourse::getLectures() const {
    return lectures;
}
