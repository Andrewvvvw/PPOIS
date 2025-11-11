#include "../../Source/Order/LoyaltyProgram/LoyaltyProgram.h"
#include <UnitTest++.h>

SUITE(LoyaltyProgramTest) {
    TEST(TestInitialState) {
        LoyaltyProgram program;

        CHECK_EQUAL(0.0, program.getAvailablePoints(1));
        CHECK_EQUAL("Regular", program.getTierName(1));
        CHECK_EQUAL(0.0, program.calculateDiscount(1));
    }

    TEST(TestAddPoints) {
        LoyaltyProgram program;

        program.addPoints(1, 100.0);
        CHECK_CLOSE(10.0, program.getAvailablePoints(1), 0.001);

        program.addPoints(1, 50.0);
        CHECK_CLOSE(15.0, program.getAvailablePoints(1), 0.001);

        program.addPoints(2, 200.0);
        CHECK_CLOSE(20.0, program.getAvailablePoints(2), 0.001);

        program.addPoints(1, -50.0);
        CHECK_CLOSE(15.0, program.getAvailablePoints(1), 0.001);
    }

    TEST(TestRedeemPoints) {
        LoyaltyProgram program;
        program.addPoints(1, 1000.0);

        CHECK(program.redeemPoints(1, 50.0));
        CHECK_CLOSE(50.0, program.getAvailablePoints(1), 0.001);

        CHECK(!program.redeemPoints(1, 60.0));
        CHECK_CLOSE(50.0, program.getAvailablePoints(1), 0.001);

        CHECK(!program.redeemPoints(1, -10.0));
        CHECK_CLOSE(50.0, program.getAvailablePoints(1), 0.001);

        CHECK(program.redeemPoints(1, 50.0));
        CHECK_EQUAL(0.0, program.getAvailablePoints(1));
    }

    TEST(TestTierCalculation) {
        LoyaltyProgram program;

        program.addPoints(1, 500.0);
        CHECK_EQUAL("Regular", program.getTierName(1));
        CHECK_EQUAL(0.0, program.calculateDiscount(1));

        program.addPoints(1, 600.0);
        CHECK_EQUAL("Silver", program.getTierName(1));
        CHECK_EQUAL(0.05, program.calculateDiscount(1));

        program.addPoints(1, 4000.0);
        CHECK_EQUAL("Gold", program.getTierName(1));
        CHECK_EQUAL(0.1, program.calculateDiscount(1));
    }

    TEST(TestUpdateCustomerSpending) {
        LoyaltyProgram program;

        program.updateCustomerSpending(1, 1000.0);
        CHECK_CLOSE(100.0, program.getAvailablePoints(1), 0.001);
        CHECK_EQUAL("Silver", program.getTierName(1));

        program.updateCustomerSpending(1, 4000.0);
        CHECK_CLOSE(500.0, program.getAvailablePoints(1), 0.001);
        CHECK_EQUAL("Gold", program.getTierName(1));
    }

    TEST(TestMultipleCustomers) {
        LoyaltyProgram program;

        program.addPoints(1, 1000.0);
        program.addPoints(2, 5000.0);
        program.addPoints(3, 500.0);

        CHECK_EQUAL("Silver", program.getTierName(1));
        CHECK_EQUAL("Gold", program.getTierName(2));
        CHECK_EQUAL("Regular", program.getTierName(3));

        CHECK_EQUAL(0.05, program.calculateDiscount(1));
        CHECK_EQUAL(0.1, program.calculateDiscount(2));
        CHECK_EQUAL(0.0, program.calculateDiscount(3));
    }

    TEST(TestEdgeCases) {
        LoyaltyProgram program;

        program.addPoints(1, 0.0);
        CHECK_EQUAL(0.0, program.getAvailablePoints(1));

        program.addPoints(1, -100.0);
        CHECK_EQUAL(0.0, program.getAvailablePoints(1));

        CHECK_EQUAL(0.0, program.calculateDiscount(999));
        CHECK_EQUAL("Regular", program.getTierName(999));

        program.addPoints(2, 1000.0);
        CHECK_EQUAL("Silver", program.getTierName(2));

        program.addPoints(3, 5000.0);
        CHECK_EQUAL("Gold", program.getTierName(3));
    }

    TEST(TestRedeemPointsEdgeCases) {
        LoyaltyProgram program;

        CHECK(!program.redeemPoints(999, 10.0));

        program.addPoints(1, 100.0);
        CHECK(!program.redeemPoints(1, 0.0));
        CHECK(!program.redeemPoints(1, -10.0));

        CHECK(program.redeemPoints(1, 10.0));
        CHECK_EQUAL(0.0, program.getAvailablePoints(1));
    }
}
