#include "UnitTest++.h"
#include "Source/Employee/Waiter/Waiter.h"

SUITE(employeeTest) {
    TEST(ConstructorAndGetters) {
        Waiter emp("John Doe", 25.0, 2);

        CHECK_EQUAL("John Doe", emp.getName());
        CHECK_EQUAL("Waiter", emp.getRole());
        CHECK_EQUAL(25.0, emp.getHourlyRate());
        CHECK_EQUAL(2, emp.getYearsOfExperience());
        CHECK(emp.getIsActive());
    }

    TEST(Setters) {
        Waiter emp("Jane Smith", 30.0, 3);

        emp.setName("Jane Johnson");
        CHECK_EQUAL("Jane Johnson", emp.getName());

        emp.setHourlyRate(35.0);
        CHECK_EQUAL(35.0, emp.getHourlyRate());

        emp.setYearsOfExperience(5);
        CHECK_EQUAL(5, emp.getYearsOfExperience());

        emp.setIsActive(false);
        CHECK(!emp.getIsActive());

        emp.setIsActive(true);
        CHECK(emp.getIsActive());
    }

    TEST(AddExperience) {
        Waiter emp("Bob Brown", 20.0, 1);

        emp.addExperience();
        CHECK_EQUAL(2, emp.getYearsOfExperience());

        emp.addExperience(3);
        CHECK_EQUAL(5, emp.getYearsOfExperience());

        emp.addExperience(0);
        CHECK_EQUAL(5, emp.getYearsOfExperience());

        emp.addExperience(-2);
        CHECK_EQUAL(5, emp.getYearsOfExperience());
    }

    TEST(EdgeCases) {
        Waiter minEmp("", 0.0, 0);
        CHECK_EQUAL("", minEmp.getName());
        CHECK_EQUAL(0.0, minEmp.getHourlyRate());
        CHECK_EQUAL(0, minEmp.getYearsOfExperience());

        Waiter maxEmp("A very long name that exceeds any reasonable limit",
                     1000.0,
                     50);
        CHECK(maxEmp.getName().length() > 0);

        CHECK_EQUAL(1000.0, maxEmp.getHourlyRate());

        CHECK_EQUAL(50, maxEmp.getYearsOfExperience());

        maxEmp.setHourlyRate(-100.0);
        CHECK_EQUAL(0.0, maxEmp.getHourlyRate());

        maxEmp.setYearsOfExperience(-10);
        CHECK_EQUAL(0, maxEmp.getYearsOfExperience());
    }

    TEST(Polymorphism) {
        Waiter waiter("Alice", 15.0, 2);
        Employee* emp = &waiter;

        CHECK_EQUAL("Alice", emp->getName());
        CHECK_EQUAL("Waiter", emp->getRole());
        CHECK_EQUAL(15.0, emp->getHourlyRate());
        CHECK_EQUAL(2, emp->getYearsOfExperience());

        emp->addExperience(3);
        CHECK_EQUAL(5, emp->getYearsOfExperience());
    }
}
