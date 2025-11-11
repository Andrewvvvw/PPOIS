#include "UnitTest++.h"
#include "../../Source/Marketing/Promotion/Promotion.h"
#include <chrono>

using namespace std::chrono_literals;

TEST(Promotion_Constructor) {
    auto now = std::chrono::system_clock::now();
    auto start = now + 1h;
    auto end = now + 24h;

    Promotion promo(1, "Summer Sale", "Summer discount", start, end, "SUMMER20", 20.0, 50.0);

            CHECK_EQUAL(1, promo.getId());
            CHECK_EQUAL("Summer Sale", promo.getName());
            CHECK_EQUAL("SUMMER20", promo.getDiscountCode());
}

TEST(Promotion_IsActive) {
    auto now = std::chrono::system_clock::now();
    auto start = now - 1h;
    auto end = now + 1h;

    Promotion activePromo(1, "Active", "Active promo", start, end, "ACTIVE", 10.0);
            CHECK(activePromo.isActive());

    Promotion futurePromo(2, "Future", "Future promo", now + 1h, now + 2h, "FUTURE", 10.0);
            CHECK(!futurePromo.isActive());

    Promotion pastPromo(3, "Past", "Past promo", now - 2h, now - 1h, "PAST", 10.0);
            CHECK(!pastPromo.isActive());
}

TEST(Promotion_CreateDiscount) {
    auto now = std::chrono::system_clock::now();
    Promotion promo(1, "Test", "Test discount", now, now + 24h, "TEST10", 10.0, 25.0);

    auto discount = promo.createDiscount();
            CHECK_EQUAL("TEST10", discount.getCode());
            CHECK_EQUAL(10.0, discount.getAmount());
            CHECK(discount.getIsPercentage());
            CHECK_EQUAL(25.0, discount.getMaxDiscountAmount());
            CHECK(discount.isValid());
}

TEST(Promotion_IsExpired) {
    auto now = std::chrono::system_clock::now();
    Promotion activePromo(1, "Active", "Active promo", now - 1h, now + 1h, "ACTIVE", 10.0);
            CHECK(!activePromo.isExpired());

    Promotion expiredPromo(2, "Expired", "Expired promo", now - 2h, now - 1h, "EXPIRED", 10.0);
            CHECK(expiredPromo.isExpired());
}

TEST(Promotion_Validate) {
    auto now = std::chrono::system_clock::now();
    Promotion validPromo(1, "Valid", "Valid promo", now, now + 24h, "VALID", 20.0);
            CHECK(validPromo.validate());

    Promotion emptyName(2, "", "No name", now, now + 24h, "NONAME", 10.0);
            CHECK(!emptyName.validate());

    Promotion emptyCode(3, "No Code", "No code", now, now + 24h, "", 10.0);
            CHECK(!emptyCode.validate());

    Promotion invalidPerc1(4, "Invalid %", "0%", now, now + 24h, "ZERO", 0.0);
    Promotion invalidPerc2(5, "Invalid %", ">100%", now, now + 24h, "OVER100", 101.0);
            CHECK(!invalidPerc1.validate());
            CHECK(!invalidPerc2.validate());

    Promotion invalidDates(6, "Invalid dates", "End before start", now, now - 1h, "DATES", 10.0);
            CHECK(!invalidDates.validate());
}

TEST(Promotion_ExtendPromotion) {
    auto now = std::chrono::system_clock::now();
    auto end = now + 24h;
    Promotion promo(1, "Extend", "Extend test", now, end, "EXTEND", 15.0);

    auto originalEnd = end;
    promo.extendPromotion(7);
    auto newEnd = originalEnd + std::chrono::hours(24 * 7);
            CHECK(promo.isExpired() == (std::chrono::system_clock::now() > newEnd));
}