#include "../../../Source/Customer/DiningSession/Reservation/Reservation.h"
#include "../../../Source/Customer/RegularCustomer/RegularCustomer.h"
#include "UnitTest++.h"
#include <chrono>

using namespace std::chrono;

SUITE(ReservationTest) {
        TEST(TestConstructor) {
            RegularCustomer customer("John Doe", 1, 100.0);
            auto now = system_clock::now();
            Reservation reservation(1, &customer, 101, now, 60);

            CHECK_EQUAL(1, reservation.isForCustomer(1));
            CHECK(reservation.isForTable(101));
        }

        TEST(TestIsActive) {
            RegularCustomer customer("Jane Smith", 2, 150.0);
            auto now = system_clock::now();
            auto futureTime = now + hours(1);

            Reservation pastReservation(2, &customer, 102, now - hours(2), 60);
            Reservation currentReservation(3, &customer, 103, now - minutes(30), 60);
            Reservation futureReservation(4, &customer, 104, now + hours(1), 60);

            CHECK(!pastReservation.isActive(now));
            CHECK(currentReservation.isActive(now));
            CHECK(!futureReservation.isActive(now));
        }

        TEST(TestIsForTable) {
            RegularCustomer customer("Bob Johnson", 3, 200.0);
            auto now = system_clock::now();
            Reservation reservation(5, &customer, 105, now, 60);

            CHECK(reservation.isForTable(105));
            CHECK(!reservation.isForTable(999));
        }

        TEST(TestIsForCustomer) {
            RegularCustomer customer1("Alice Brown", 4, 250.0);
            RegularCustomer customer2("Charlie Davis", 5, 300.0);
            auto now = system_clock::now();
            Reservation reservation(6, &customer1, 106, now, 60);

            CHECK(reservation.isForCustomer(4));
            CHECK(!reservation.isForCustomer(5));
        }

    TEST(TestExtendDuration) {
        RegularCustomer customer("Eve Wilson", 6, 350.0);
        auto now = system_clock::now();
        Reservation reservation(7, &customer, 107, now, 60);

                CHECK(reservation.isActive(now + minutes(59)));
                CHECK(!reservation.isActive(now + minutes(61)));

        reservation.extendDuration(30);
                CHECK(reservation.isActive(now + minutes(61)));
                CHECK(reservation.isActive(now + minutes(89)));
                CHECK(!reservation.isActive(now + minutes(91)));

        reservation.extendDuration(-10);
                CHECK(reservation.isActive(now + minutes(89)));

        reservation.extendDuration(0);
                CHECK(reservation.isActive(now + minutes(89)));
    }

        TEST(TestConflictsWith) {
            RegularCustomer customer1("Frank Miller", 7, 400.0);
            RegularCustomer customer2("Grace Lee", 8, 450.0);
            auto now = system_clock::now();

            Reservation res1(8, &customer1, 108, now, 60);
            Reservation res2(9, &customer2, 108, now + minutes(30), 60);

            Reservation res3(10, &customer1, 108, now + hours(2), 30);

            Reservation res4(11, &customer2, 109, now, 60);

            CHECK(res1.conflictsWith(res2));
            CHECK(res2.conflictsWith(res1));
            CHECK(!res1.conflictsWith(res3));
            CHECK(!res1.conflictsWith(res4));
            CHECK(!res3.conflictsWith(res4));
        }

        TEST(TestEdgeCases) {
            Reservation nullCustomerReservation(12, nullptr, 110, system_clock::now(), 60);
            CHECK(!nullCustomerReservation.isForCustomer(1));

            RegularCustomer customer("Henry Ford", 9, 500.0);
            auto now = system_clock::now();
            Reservation zeroDurationReservation(13, &customer, 111, now, 0);

            CHECK(!zeroDurationReservation.isActive(now));
            CHECK(!zeroDurationReservation.isActive(now + hours(1)));

            Reservation longReservation(14, &customer, 112, now, 24 * 60);
            CHECK(longReservation.isActive(now + hours(12)));
            CHECK(longReservation.isActive(now + hours(23)));
            CHECK(!longReservation.isActive(now + hours(25)));
        }

        TEST(TestBoundaryConditions) {
            RegularCustomer customer("Ivy Young", 10, 550.0);
            auto now = system_clock::now();

            Reservation res(15, &customer, 113, now, 60);

            CHECK(res.isActive(now));

            CHECK(res.isActive(now + minutes(60)));

            CHECK(res.isActive(now + minutes(59)));

            CHECK(!res.isActive(now + minutes(61)));
        }
}