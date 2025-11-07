#ifndef LECTURER_H
#define LECTURER_H

#include "../RegisteredUser.h"
#include "../../../Audio/AudioCourse/AudioLecture/AudioLecture.h"
#include <vector>
#include <memory>

class AudioLecture;

class Lecturer : public RegisteredUser {
private:
    std::vector <std::shared_ptr <AudioLecture> > lectures;
    std::string institution;
    std::string department;

public:
    Lecturer(const std::string& id,
             const std::string& username,
             const std::string& email,
             const std::string& password,
             const std::string& institution,
             const std::string& department);

    const std::string& getInstitution() const { return institution; }
    const std::string& getDepartment() const { return department; }
    const std::vector<std::shared_ptr<AudioLecture>>& getLectures() const { return lectures; }

    bool addLecture(const std::shared_ptr<AudioLecture>& lecture);
    bool removeLecture(const std::shared_ptr<AudioLecture>& lecture);
    bool hasLecture(const std::shared_ptr<AudioLecture>& lecture) const;
};

#endif // LECTURER_H
