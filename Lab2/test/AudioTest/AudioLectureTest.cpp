#include "../../src/Audio/AudioCourse/AudioLecture/AudioLecture.h"
#include "../../src/User/RegisteredUser/Lecturer/Lecturer.h"
#include "UnitTest++.h"
#include <memory>

SUITE(AudioLectureTest) {
    TEST(TestConstructorAndGetters) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Introduction to C++", 3600, 1, lecturer, "OOP Basics", "CS101");
        lecture->registerWithLecturer();

                CHECK_EQUAL("Introduction to C++", lecture->getName());
                CHECK_EQUAL(3600, lecture->getDuration());
                CHECK_EQUAL(1, lecture->getCoverID());
                CHECK_EQUAL("JohnDoe", lecture->getAuthor());
                CHECK_EQUAL("OOP Basics", lecture->getTopic());
                CHECK_EQUAL("CS101", lecture->getCourseCode());
                CHECK_EQUAL(0, lecture->getSlideCount());
    }

    TEST(TestAddSlide) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

                CHECK(lecture->addSlide("Slide 1"));
                CHECK_EQUAL(1, lecture->getSlideCount());
                CHECK(lecture->addSlide("Slide 2"));
                CHECK_EQUAL(2, lecture->getSlideCount());
    }

    TEST(TestGetCurrentSlide) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

                CHECK(lecture->getCurrentSlide().empty());

        lecture->addSlide("First slide");
                CHECK_EQUAL("First slide", lecture->getCurrentSlide());

        lecture->addSlide("Second slide");
                CHECK_EQUAL("First slide", lecture->getCurrentSlide());
    }

    TEST(TestSetCurrentSlide) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

        lecture->addSlide("Slide 1");
        lecture->addSlide("Slide 2");
        lecture->addSlide("Slide 3");

                CHECK(lecture->setCurrentSlide(1));
                CHECK_EQUAL("Slide 2", lecture->getCurrentSlide());

                CHECK(!lecture->setCurrentSlide(3));
                CHECK_EQUAL("Slide 2", lecture->getCurrentSlide());
    }

    TEST(TestRemoveSlide) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

        lecture->addSlide("Slide 1");
        lecture->addSlide("Slide 2");
        lecture->addSlide("Slide 3");

                CHECK(lecture->removeSlide(1));
                CHECK_EQUAL(2, lecture->getSlideCount());

        auto slides = lecture->getSlides();
                CHECK_EQUAL("Slide 1", slides[0]);
                CHECK_EQUAL("Slide 3", slides[1]);

                CHECK(!lecture->removeSlide(5));
    }

    TEST(TestRemoveCurrentSlide) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

        lecture->addSlide("Slide 1");
        lecture->addSlide("Slide 2");
        lecture->setCurrentSlide(1);

                CHECK(lecture->removeSlide(1));
                CHECK_EQUAL("Slide 1", lecture->getCurrentSlide());

                CHECK(lecture->removeSlide(0));
                CHECK(lecture->getCurrentSlide().empty());
    }

    TEST(TestGetSlides) {
        auto lecturer = std::make_shared<Lecturer>("lecturer1", "JohnDoe", "john@example.com", "password123", "MIT", "Computer Science");
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, lecturer, "Topic 1", "CS101");
        lecture->registerWithLecturer();

        lecture->addSlide("Slide 1");
        lecture->addSlide("Slide 2");

        auto slides = lecture->getSlides();
                CHECK_EQUAL(2, slides.size());
                CHECK_EQUAL("Slide 1", slides[0]);
                CHECK_EQUAL("Slide 2", slides[1]);
    }

    TEST(TestNullLecturer) {
        auto lecture = std::make_shared<AudioLecture>("Lecture 1", 1800, 2, nullptr, "Topic 1", "CS101");

                CHECK_EQUAL("Unknown Lecturer", lecture->getAuthor());
                CHECK(lecture->getLecturer() == nullptr);
    }
}


