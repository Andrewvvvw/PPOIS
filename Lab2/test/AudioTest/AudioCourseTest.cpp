#include "../../src/Audio/AudioCourse/AudioCourse.h"
#include "../../src/Audio/AudioCourse/AudioLecture/AudioLecture.h"
#include "../../src/User/RegisteredUser/Lecturer/Lecturer.h"
#include "UnitTest++.h"
#include <memory>

using namespace std;

class TestFixture {
public:
    shared_ptr<Lecturer> lecturer;
    shared_ptr<AudioLecture> lecture1;
    shared_ptr<AudioLecture> lecture2;
    shared_ptr<AudioCourse> course;

    TestFixture() {
        lecturer = make_shared<Lecturer>("lecturer1", "johndoe", "john@example.com", "password", "MIT", "CS");
        lecture1 = make_shared<AudioLecture>("Intro to C++", 3600, 1, lecturer, "Basics", "CS101");
        lecture2 = make_shared<AudioLecture>("Advanced C++", 5400, 2, lecturer, "Advanced", "CS101");
        course = make_shared<AudioCourse>("C++ Programming", 3, "CS101", "Learn C++ programming");
    }
};

SUITE(AudioCourseTest) {
    TEST_FIXTURE(TestFixture, ConstructorAndGetters) {
        CHECK_EQUAL("C++ Programming", course->getName());
        CHECK_EQUAL(3, course->getCoverID());
        CHECK_EQUAL("CS101", course->getCourseCode());
        CHECK_EQUAL("Learn C++ programming", course->getDescription());
        CHECK_EQUAL(0, course->getLectures().size());
        CHECK_EQUAL(0, course->getLearningObjectives().size());
        CHECK_EQUAL(0, course->getPrerequisites().size());
    }

    TEST_FIXTURE(TestFixture, AddLecture) {
        CHECK(course->addLecture(lecture1));
        CHECK_EQUAL(1, course->getLectures().size());
        CHECK(course->hasLecture(lecture1));

        CHECK(!course->addLecture(lecture1));
        CHECK_EQUAL(1, course->getLectures().size());

        auto invalidLecture = make_shared<AudioLecture>("Other Course", 3600, 4, lecturer, "Other", "CS102");
        CHECK(!course->addLecture(invalidLecture));
        CHECK_EQUAL(1, course->getLectures().size());

        CHECK(!course->addLecture(nullptr));
        CHECK_EQUAL(1, course->getLectures().size());
    }

    TEST_FIXTURE(TestFixture, RemoveLecture) {
        course->addLecture(lecture1);
        CHECK(course->removeLecture(lecture1));
        CHECK_EQUAL(0, course->getLectures().size());

        CHECK(!course->removeLecture(lecture1));
        CHECK(!course->removeLecture(nullptr));
    }

    TEST_FIXTURE(TestFixture, LearningObjectives) {
        CHECK(course->addLearningObjective("Learn C++ basics"));
        CHECK_EQUAL(1, course->getLearningObjectives().size());
        CHECK_EQUAL("Learn C++ basics", course->getLearningObjectives()[0]);

        CHECK(!course->addLearningObjective(""));
        CHECK_EQUAL(1, course->getLearningObjectives().size());

        CHECK(!course->addLearningObjective("Learn C++ basics"));
        CHECK_EQUAL(1, course->getLearningObjectives().size());

        CHECK(course->addLearningObjective("Master advanced C++"));
        CHECK_EQUAL(2, course->getLearningObjectives().size());

        CHECK(course->removeLearningObjective("Learn C++ basics"));
        CHECK_EQUAL(1, course->getLearningObjectives().size());
        CHECK_EQUAL("Master advanced C++", course->getLearningObjectives()[0]);

        CHECK(!course->removeLearningObjective("Non-existent objective"));
        CHECK_EQUAL(1, course->getLearningObjectives().size());
    }

    TEST_FIXTURE(TestFixture, Prerequisites) {
        CHECK(course->addPrerequisite("Basic programming knowledge"));
        CHECK_EQUAL(1, course->getPrerequisites().size());
        CHECK_EQUAL("Basic programming knowledge", course->getPrerequisites()[0]);

        CHECK(!course->addPrerequisite(""));
        CHECK_EQUAL(1, course->getPrerequisites().size());

        CHECK(!course->addPrerequisite("Basic programming knowledge"));
        CHECK_EQUAL(1, course->getPrerequisites().size());

        CHECK(course->addPrerequisite("C++ basics"));
        CHECK_EQUAL(2, course->getPrerequisites().size());

        CHECK(course->removePrerequisite("Basic programming knowledge"));
        CHECK_EQUAL(1, course->getPrerequisites().size());
        CHECK_EQUAL("C++ basics", course->getPrerequisites()[0]);

        CHECK(!course->removePrerequisite("Non-existent prerequisite"));
        CHECK_EQUAL(1, course->getPrerequisites().size());
    }

    TEST_FIXTURE(TestFixture, TotalDuration) {
        CHECK_EQUAL(0, course->getTotalDuration());

        course->addLecture(lecture1);
        CHECK_EQUAL(3600, course->getTotalDuration());

        course->addLecture(lecture2);
        CHECK_EQUAL(9000, course->getTotalDuration());

        course->removeLecture(lecture1);
        CHECK_EQUAL(5400, course->getTotalDuration());

        auto nullLecture = shared_ptr<AudioLecture>(nullptr);
        course->addLecture(nullLecture);
        CHECK_EQUAL(5400, course->getTotalDuration());
    }

    TEST_FIXTURE(TestFixture, GetLectures) {
        course->addLecture(lecture1);
        auto lectures = course->getLectures();
        CHECK_EQUAL(1, lectures.size());
        CHECK_EQUAL("Intro to C++", lectures[0]->getName());
    }
}
