#include "UnitTest++.h"
#include "../../../src/User/RegisteredUser/Lecturer/Lecturer.h"
#include "../../../src/Exceptions/Exceptions.h"

using namespace std;

SUITE(LecturerTest) {
    TEST(TestConstructor) {
        Lecturer lecturer("lecturer1", "john_doe", "john@university.edu", "password123", "MIT", "Computer Science");

                CHECK_EQUAL("lecturer1", lecturer.getId());
                CHECK_EQUAL("john_doe", lecturer.getUsername());
                CHECK_EQUAL("john@university.edu", lecturer.getEmail());
                CHECK_EQUAL("MIT", lecturer.getInstitution());
                CHECK_EQUAL("Computer Science", lecturer.getDepartment());
                CHECK(lecturer.getLectures().empty());
    }

    TEST(TestAddLecture) {
        auto lecturer = make_shared<Lecturer>("lecturer1", "john_doe", "john@university.edu", "password123", "MIT", "CS");
        auto lecture1 = make_shared<AudioLecture>("Intro to C++", 60, 1, lecturer, "Introduction", "CS101");
        auto lecture2 = make_shared<AudioLecture>("OOP Principles", 45, 2, lecturer, "OOP", "CS102");

                CHECK(lecturer->addLecture(lecture1));
                CHECK(lecturer->hasLecture(lecture1));
                CHECK_EQUAL(1, lecturer->getLectures().size());

                CHECK(lecturer->addLecture(lecture2));
                CHECK(lecturer->hasLecture(lecture2));
                CHECK_EQUAL(2, lecturer->getLectures().size());

                CHECK(!lecturer->addLecture(lecture1));
                CHECK_EQUAL(2, lecturer->getLectures().size());

                CHECK(!lecturer->addLecture(nullptr));
    }

    TEST(TestRemoveLecture) {
        auto lecturer = make_shared<Lecturer>("lecturer1", "john_doe", "john@university.edu", "password123", "MIT", "CS");
        auto lecture1 = make_shared<AudioLecture>("Intro to C++", 60, 1, lecturer, "Introduction", "CS101");
        auto lecture2 = make_shared<AudioLecture>("OOP Principles", 45, 2, lecturer, "OOP", "CS102");

        lecturer->addLecture(lecture1);
        lecturer->addLecture(lecture2);

                CHECK(lecturer->removeLecture(lecture1));
                CHECK(!lecturer->hasLecture(lecture1));
                CHECK(lecturer->hasLecture(lecture2));
                CHECK_EQUAL(1, lecturer->getLectures().size());

                CHECK(!lecturer->removeLecture(lecture1));
                CHECK(!lecturer->removeLecture(nullptr));

                CHECK(lecturer->removeLecture(lecture2));
                CHECK(lecturer->getLectures().empty());
    }

    TEST(TestHasLecture) {
        auto lecturer = make_shared<Lecturer>("lecturer1", "john_doe", "john@university.edu", "password123", "MIT", "CS");
        auto lecture1 = make_shared<AudioLecture>("Intro to C++", 60, 1, lecturer, "Introduction", "CS101");
        auto lecture2 = make_shared<AudioLecture>("OOP Principles", 45, 2, lecturer, "OOP", "CS102");

        lecturer->addLecture(lecture1);

                CHECK(lecturer->hasLecture(lecture1));
                CHECK(!lecturer->hasLecture(lecture2));
                CHECK(!lecturer->hasLecture(nullptr));
    }

    TEST(TestGetLectures) {
        auto lecturer = make_shared<Lecturer>("lecturer1", "john_doe", "john@university.edu", "password123", "MIT", "CS");
        auto lecture1 = make_shared<AudioLecture>("Intro to C++", 60, 1, lecturer, "Introduction", "CS101");
        auto lecture2 = make_shared<AudioLecture>("OOP Principles", 45, 2, lecturer, "OOP", "CS102");

        lecturer->addLecture(lecture1);
        lecturer->addLecture(lecture2);

        const auto& lectures = lecturer->getLectures();
                CHECK_EQUAL(2, lectures.size());
                CHECK(lectures[0] == lecture1 || lectures[1] == lecture1);
                CHECK(lectures[0] == lecture2 || lectures[1] == lecture2);
    }

    TEST(TestGetInstitutionAndDepartment) {
        Lecturer lecturer("lecturer1", "john_doe", "john@university.edu", "password123", "Stanford", "AI");
                CHECK_EQUAL("Stanford", lecturer.getInstitution());
                CHECK_EQUAL("AI", lecturer.getDepartment());
    }
}
