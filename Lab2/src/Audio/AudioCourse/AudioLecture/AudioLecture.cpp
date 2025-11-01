#include "AudioLecture.h"
#include <algorithm>

AudioLecture::AudioLecture(const std::string& title,
                           unsigned long long duration,
                           unsigned long long coverID,
                           const std::shared_ptr<Lecturer>& lecturer,
                           const std::string& topic,
                           const std::string& courseCode)
        : Audio(duration, title, coverID),
          lecturer(lecturer),
          topic(topic),
          courseCode(courseCode),
          currentSlide(0) {
    if (lecturer) {
        lecturer->addLecture(std::shared_ptr<AudioLecture>(this));
    }
}

std::string AudioLecture::getAuthor() const {
    return lecturer ? lecturer->getUsername() : "Unknown Lecturer";
}

bool AudioLecture::addSlide(const std::string& slideContent) {
    try {
        slides.push_back(slideContent);
        return true;
    } catch (...) {
        return false;
    }
}

bool AudioLecture::removeSlide(unsigned int slideIndex) {
    if (slideIndex >= slides.size()) {
        return false;
    }

    slides.erase(slides.begin() + slideIndex);

    if (currentSlide >= slides.size() && !slides.empty()) {
        currentSlide = slides.size() - 1;
    } else if (slides.empty()) {
        currentSlide = 0;
    }

    return true;
}

bool AudioLecture::setCurrentSlide(unsigned int slide) {
    if (slide < slides.size()) {
        currentSlide = slide;
        return true;
    }
    return false;
}

std::string AudioLecture::getCurrentSlide() const {
    if (slides.empty()) {
        return "";
    }
    return slides[currentSlide];
}
