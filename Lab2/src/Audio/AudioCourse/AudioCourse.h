#ifndef AUDIO_COURSE_H
#define AUDIO_COURSE_H

#include "../Audio.h"
#include "AudioLecture/AudioLecture.h"
#include "../../User/RegisteredUser/Lecturer/Lecturer.h"
#include <vector>
#include <memory>
#include <string>

class Lecturer;
class AudioLecture;

class AudioCourse : public Audio {
private:
    std::vector<std::shared_ptr<AudioLecture>> lectures;
    std::shared_ptr<Lecturer> courseInstructor;
    std::string courseCode;
    std::string description;
    std::vector<std::string> learningObjectives;
    std::vector<std::string> prerequisites;

public:
    AudioCourse(const std::string& title,
               unsigned long long coverID,
               const std::shared_ptr<Lecturer>& instructor,
               const std::string& courseCode,
               const std::string& description);

    const std::shared_ptr<Lecturer>& getInstructor() const { return courseInstructor; }
    const std::string& getCourseCode() const { return courseCode; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::string>& getLearningObjectives() const { return learningObjectives; }
    const std::vector<std::string>& getPrerequisites() const { return prerequisites; }
    std::vector<std::shared_ptr<AudioLecture>> getLectures() const { return lectures; }
    std::string getAuthor() const override;

    bool addLecture(const std::shared_ptr<AudioLecture>& lecture);
    bool removeLecture(const std::shared_ptr<AudioLecture>& lecture);
    bool hasLecture(const std::shared_ptr<AudioLecture>& lecture) const;

    bool addLearningObjective(const std::string& objective);
    bool removeLearningObjective(const std::string& objective);
    bool addPrerequisite(const std::string& prerequisite);
    bool removePrerequisite(const std::string& prerequisite);

    unsigned long long getTotalDuration() const;
};

#endif // AUDIO_COURSE_H
