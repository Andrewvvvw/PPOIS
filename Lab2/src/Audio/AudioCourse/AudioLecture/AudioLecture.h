#ifndef AUDIO_LECTURE_H
#define AUDIO_LECTURE_H

#include "../../Audio.h"
#include "../../../User/RegisteredUser/Lecturer/Lecturer.h"
#include <vector>
#include <memory>
#include <string>

class Lecturer;

class AudioLecture : public Audio {
private:
    std::shared_ptr<Lecturer> lecturer;
    std::vector<std::string> slides;
    unsigned int currentSlide;
    std::string topic;
    std::string courseCode;

public:
    AudioLecture(const std::string& title,
                 unsigned long long duration,
                 unsigned long long coverID,
                 const std::shared_ptr<Lecturer>& lecturer,
                 const std::string& topic,
                 const std::string& courseCode);

    const std::shared_ptr<Lecturer>& getLecturer() const { return lecturer; }
    const std::string& getTopic() const { return topic; }
    const std::string& getCourseCode() const { return courseCode; }
    std::string getAuthor() const override;

    bool addSlide(const std::string& slideContent);
    bool removeSlide(unsigned int slideIndex);
    bool setCurrentSlide(unsigned int slide);
    std::string getCurrentSlide() const;
    unsigned int getSlideCount() const { return slides.size(); }
    std::vector<std::string> getSlides() const { return slides; }
};

#endif // AUDIO_LECTURE_H