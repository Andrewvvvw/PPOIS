#ifndef AUDIO_COURSE_H
#define AUDIO_COURSE_H

#include "../Audio.h"
#include <vector>
#include <memory>
#include <string>

class Lecturer;
class AudioLecture;

class AudioCourse : public Audio {
private:
    std::vector <std::shared_ptr<AudioLecture> > lectures;
    std::string courseCode;
    std::string description;
    std::vector<std::string> learningObjectives;
    std::vector<std::string> prerequisites;

public:
    AudioCourse(const std::string& title,
               unsigned long long coverID,
               const std::string& courseCode,
               const std::string& description);

    const std::string& getCourseCode() const;
    const std::string& getDescription() const;
    const std::vector<std::string>& getLearningObjectives() const;
    const std::vector<std::string>& getPrerequisites() const;
    std::vector <std::shared_ptr <AudioLecture> > getLectures() const;
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
