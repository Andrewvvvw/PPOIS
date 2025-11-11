#include "../../../Source/Customer/DiningSession/DiningSession.h"
#include "../../../Source/Customer/RegularCustomer/RegularCustomer.h"
#include <UnitTest++.h>
#include <thread>

SUITE(DiningSessionTest) {
    TEST(TestConstructor) {
        Table table(1, 4, "Window");
        RegularCustomer customer("John Doe", 1, 100.0);

        DiningSession session(1, &table, &customer);

                CHECK_EQUAL(1, session.calculateSessionDuration() >= 0);
                CHECK(session.isActive());
    }

    TEST(TestAddCustomer) {
        Table table(2, 4, "Window");
        RegularCustomer customer1("John Doe", 1, 100.0);
        RegularCustomer customer2("Jane Smith", 2, 150.0);
        RegularCustomer customer3("Bob Johnson", 3, 200.0);

        DiningSession session(1, &table, &customer1);

        session.addCustomer(&customer2);
        session.addCustomer(&customer2);
        session.addCustomer(&customer3);

        session.endSession();
        session.addCustomer(&customer1);
    }

    TEST(TestRemoveCustomer) {
        Table table(3, 4, "Center");
        RegularCustomer customer1("John Doe", 1, 100.0);
        RegularCustomer customer2("Jane Smith", 2, 150.0);

        DiningSession session(1, &table, &customer1);
        session.addCustomer(&customer2);

        session.removeCustomer(1);
        session.removeCustomer(999);
        session.endSession();
        session.removeCustomer(2);
    }

    TEST(TestEndSession) {
        Table table(4, 4, "Terrace");
        RegularCustomer customer("John Doe", 1, 100.0);

        DiningSession session(1, &table, &customer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        session.endSession();
                CHECK(!session.isActive());
        double duration1 = session.calculateSessionDuration();
                CHECK(duration1 > 0);

        session.endSession();
        double duration2 = session.calculateSessionDuration();
                CHECK_CLOSE(duration1, duration2, 0.001);
    }

    TEST(TestCalculateSessionDuration) {
        Table table(5, 4, "Bar");
        RegularCustomer customer("John Doe", 1, 100.0);

        {
            DiningSession session(1, &table, &customer);
            double duration1 = session.calculateSessionDuration();
                    CHECK(duration1 >= 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            double duration2 = session.calculateSessionDuration();
                    CHECK(duration2 > duration1);
        }

        {
            DiningSession session(2, &table, &customer);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            session.endSession();
            double duration = session.calculateSessionDuration();
                    CHECK(duration > 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    CHECK_CLOSE(duration, session.calculateSessionDuration(), 0.001);
        }
    }

    TEST(TestIsActive) {
        Table table(6, 4, "VIP");
        RegularCustomer customer("John Doe", 1, 100.0);

        {
            DiningSession session(1, &table, &customer);
                    CHECK(session.isActive());
        }

        {
            DiningSession session(2, &table, &customer);
            session.endSession();
                    CHECK(!session.isActive());
        }
    }

    TEST(TestMultipleOperations) {
        Table table(7, 4, "Outdoor");
        RegularCustomer customer1("John Doe", 1, 100.0);
        RegularCustomer customer2("Jane Smith", 2, 150.0);
        RegularCustomer customer3("Bob Johnson", 3, 200.0);

        DiningSession session(1, &table, &customer1);
        session.addCustomer(&customer2);
        session.addCustomer(&customer3);
        session.removeCustomer(2);
        session.addCustomer(&customer2);
        session.endSession();

                CHECK(!session.isActive());
        double duration = session.calculateSessionDuration();
                CHECK(duration > 0);

        session.addCustomer(&customer3);
        session.removeCustomer(1);
                CHECK_CLOSE(duration, session.calculateSessionDuration(), 0.001);
    }

    TEST(TestEdgeCases) {
        RegularCustomer customer("John Doe", 1, 100.0);
        DiningSession session(1, nullptr, &customer);
                CHECK(session.isActive());

        Table table(8, 4, "Private");
        DiningSession session2(2, &table, nullptr);
                CHECK(session2.isActive());

        DiningSession session3(3, &table, &customer);
        session3.removeCustomer(1);
                CHECK(session3.isActive());
    }
}