#include "Lecturer.h"
#include <memory>
Lecturer::Lecturer(const std::string& id,
                   const std::string& username,
                   const std::string& email,
                   const std::string& password,
                   const std::string& institution,
                   const std::string& department)
    : RegisteredUser(id, username, email, password),
      institution(institution),
      department(department) {}

bool Lecturer::addLecture(const std::shared_ptr<AudioLecture>& lecture) {
    if (!lecture || hasLecture(lecture)) {
        return false;
    }
    lectures.push_back(lecture);
    return true;
}

bool Lecturer::removeLecture(const std::shared_ptr<AudioLecture>& lecture) {
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

bool Lecturer::hasLecture(const std::shared_ptr<AudioLecture>& lecture) const {
    if (!lecture) {
        return false;
    }
    return std::find(lectures.begin(), lectures.end(), lecture) != lectures.end();
}

const std::string& Lecturer::getInstitution() const {
    return institution;
}

const std::string& Lecturer::getDepartment() const {
    return department;
}

const std::vector<std::shared_ptr<AudioLecture>>& Lecturer::getLectures() const {
    return lectures;
}
