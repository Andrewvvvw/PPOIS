#include "UnitTest++.h"
#include "Source/Employee/Manager/Manager.h"

SUITE(ManagerTest) {
    TEST(ConstructorAndGetters) {
        Manager manager("John Doe", "Restaurant Manager", 25.0, "Operations", 2);

        CHECK_EQUAL("John Doe", manager.getName());
        CHECK_EQUAL("Manager", manager.getRole());
        CHECK_EQUAL(25.0, manager.getHourlyRate());
        CHECK_EQUAL("Operations", manager.getDepartment());
        CHECK_EQUAL(2, manager.getAccessLevel());
        CHECK_EQUAL(0, manager.getTeamSize());
        CHECK_EQUAL(0.0, manager.getBonus());
        CHECK(!manager.getIsCertified());
        CHECK(manager.getIsActive());
    }

    TEST(SettersAndGetters) {
        Manager manager("Jane Smith", "Shift Manager", 22.0, "Kitchen", 1);

        manager.setDepartment("Service");
        CHECK_EQUAL("Service", manager.getDepartment());

        manager.setTeamSize(5);
        CHECK_EQUAL(5, manager.getTeamSize());

        manager.setTeamSize(-3);
        CHECK_EQUAL(0, manager.getTeamSize());

        manager.setBonus(1000.0);
        CHECK_EQUAL(1000.0, manager.getBonus());

        manager.setBonus(-500.0);
        CHECK_EQUAL(0.0, manager.getBonus());

        manager.setAccessLevel(3);
        CHECK_EQUAL(3, manager.getAccessLevel());

        manager.setAccessLevel(-1);
        CHECK_EQUAL(1, manager.getAccessLevel());

        manager.setIsCertified(true);
        CHECK(manager.getIsCertified());
    }

    TEST(AssignTask) {
        Manager manager("Bob Johnson", "Floor Manager", 20.0, "Service", 2);

        manager.assignTask("prepare monthly report", "Alice");

        manager.assignTask("", "");
        manager.assignTask("", "Alice");
        manager.assignTask("", "");
    }

    TEST(ApproveExpense) {
        Manager manager("Alice Brown", "senior Manager", 30.0, "Finance", 3);

        CHECK(manager.approveExpense(500.0));
        CHECK(manager.approveExpense(3000.0));

        CHECK(!manager.approveExpense(3500.0));

        CHECK(!manager.approveExpense(-100.0));

        manager.setAccessLevel(1);
        CHECK(manager.approveExpense(1000.0));
        CHECK(!manager.approveExpense(1001.0));
    }

    TEST(EvaluateTeam) {
        Manager manager("Charlie Wilson", "Team Lead", 18.0, "HR", 2);

        CHECK_EQUAL(0.0, manager.evaluateTeam());

        manager.setTeamSize(1);
        CHECK_CLOSE(50.0, manager.evaluateTeam(), 0.001);

        manager.setTeamSize(2);
        CHECK_CLOSE(66.6667, manager.evaluateTeam(), 0.001);

        manager.setTeamSize(3);
        CHECK_CLOSE(75.0, manager.evaluateTeam(), 0.001);

        manager.setTeamSize(10);
        CHECK_CLOSE(90.9091, manager.evaluateTeam(), 0.001);
    }

    TEST(BonusEligibility) {
        Manager manager("David Lee", "Assistant Manager", 20.0, "Operations", 2);

        CHECK(!manager.getBonusEligibility());

        manager.setTeamSize(5);
        CHECK(!manager.getBonusEligibility());

        manager.setIsCertified(true);
        manager.setAccessLevel(1);
        CHECK(!manager.getBonusEligibility());

        manager.setAccessLevel(3);
        manager.setTeamSize(2);
        CHECK(!manager.getBonusEligibility());

        manager.setTeamSize(4);
        CHECK(manager.getBonusEligibility());
    }

    TEST(EdgeCases) {
        Manager minManager("Min", "Trainee", 0.0, "", 1);
        CHECK_EQUAL(1, minManager.getAccessLevel());
        CHECK_EQUAL(0.0, minManager.getHourlyRate());

        Manager maxManager("Max", "Director", 1000.0, std::string(100, 'A'), 10);
        maxManager.setTeamSize(1000);
        maxManager.setBonus(1e6);

        CHECK_EQUAL(1000, maxManager.getTeamSize());
        CHECK_EQUAL(1e6, maxManager.getBonus());
        CHECK_CLOSE(99.9001, maxManager.evaluateTeam(), 0.0001);
    }
}
