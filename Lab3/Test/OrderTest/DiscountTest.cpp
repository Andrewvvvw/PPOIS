#include "../../Source/Order/Discount/Discount.h"
#include "../../Source/Exceptions/Exceptions.h"
#include <UnitTest++.h>

SUITE(DiscountTest) {
    TEST(TestDiscountCreation) {
        Discount discount1("SUMMER20", 20.0, true, 50.0);
                CHECK_EQUAL("SUMMER20", discount1.getCode());
                CHECK_EQUAL(20.0, discount1.getAmount());
                CHECK_EQUAL(true, discount1.getIsPercentage());
                CHECK_EQUAL(50.0, discount1.getMaxDiscountAmount());

        Discount discount2("FIXED10", 10.0, false);
                CHECK_EQUAL("FIXED10", discount2.getCode());
                CHECK_EQUAL(10.0, discount2.getAmount());
                CHECK_EQUAL(false, discount2.getIsPercentage());
                CHECK_EQUAL(0.0, discount2.getMaxDiscountAmount());

                CHECK_THROW(Discount("INVALID", -5.0), ExceptionIncorrectDiscountAmount);
    }

    TEST(TestPercentageDiscount) {
        Discount discount("SALE10", 10.0);
                CHECK_EQUAL(90.0, discount.applyDiscount(100.0));
                CHECK_EQUAL(45.0, discount.applyDiscount(50.0));

        Discount maxDiscount("MAX99", 99.0);
                CHECK_EQUAL(1.0, maxDiscount.applyDiscount(100.0));
    }


    TEST(TestFixedDiscount) {
        Discount discount("FIXED20", 20.0, false);
                CHECK_EQUAL(80.0, discount.applyDiscount(100.0));

                CHECK_EQUAL(0.0, discount.applyDiscount(15.0));
    }

    TEST(TestMaxDiscountAmount) {
        Discount discount("MAX50", 20.0, true, 10.0);

                CHECK_EQUAL(90.0, discount.applyDiscount(100.0));

                CHECK_EQUAL(20.0, discount.applyDiscount(25.0));

        discount.setMaxDiscountAmount(5.0);
                CHECK_EQUAL(95.0, discount.applyDiscount(100.0));
    }

    TEST(TestValidity) {
                CHECK(Discount("VALID1", 10.0).isValid());
                CHECK(Discount("VALID2", 10.0, false).isValid());
                CHECK_THROW(Discount("VALID3", 100.0).isValid(), ExceptionIncorrectDiscountAmount);

                CHECK_THROW(Discount("INVALID1", 0.0), ExceptionIncorrectDiscountAmount);
                CHECK_THROW(Discount("INVALID2", -5.0), ExceptionIncorrectDiscountAmount);
                CHECK_THROW(Discount("INVALID3", 150.0), ExceptionIncorrectDiscountAmount);
    }

    TEST(TestEdgeCases) {
        Discount discount("SALE10", 10.0);
                CHECK_EQUAL(0.0, discount.applyDiscount(0.0));
        CHECK_EQUAL(-90.0, discount.applyDiscount(-100.0));
        Discount maxDiscount("FIXED2000", 2000.0, false);
                CHECK_EQUAL(0.0, maxDiscount.applyDiscount(1000.0));
                CHECK_EQUAL(0.0, maxDiscount.applyDiscount(2000.0));
    }

    TEST(TestApplyInvalidDiscount) {
                CHECK_THROW(Discount("INVALID", 0.0), ExceptionIncorrectDiscountAmount);

        Discount d("VALID", 10.0);
                CHECK_EQUAL(90.0, d.applyDiscount(100.0));
    }

    TEST(TestGetDescription) {
        Discount percentDiscount("SALE10", 10.0, true, 50.0);
                CHECK_EQUAL("10% off (max 50.000000)", percentDiscount.getDescription());

        Discount fixedDiscount("FIXED20", 20.0, false);
                CHECK_EQUAL("$20.000000 off", fixedDiscount.getDescription());

        Discount simplePercent("SIMPLE10", 10.0, true);
                CHECK_EQUAL("10% off", simplePercent.getDescription());
    }

    TEST(TestInvalidMaxDiscountAmount) {
        Discount discount("NEGMAX", 10.0, true, -10.0);
                CHECK(!discount.isValid());

        Discount zeroMax("ZEROMAX", 10.0, true, 0.0);
                CHECK(zeroMax.isValid());
    }

    TEST(TestSetMaxDiscountAmount) {
        Discount discount("CHANGEMAX", 20.0, true, 50.0);

        discount.setMaxDiscountAmount(30.0);
                CHECK_EQUAL(30.0, discount.getMaxDiscountAmount());
                CHECK(discount.isValid());

        discount.setMaxDiscountAmount(0.0);
                CHECK_EQUAL(0.0, discount.getMaxDiscountAmount());
                CHECK(discount.isValid());
    }

    TEST(TestPercentageDiscountWithMaxAmount) {
        Discount discount("MAX50", 20.0, true, 10.0);

                CHECK_EQUAL(90.0, discount.applyDiscount(100.0));

                CHECK_EQUAL(40.0, discount.applyDiscount(50.0));

                CHECK_EQUAL(40.0, discount.applyDiscount(50.0));
    }

    TEST(TestFixedDiscountEdgeCases) {
        Discount exactDiscount("EXACT100", 100.0, false);
                CHECK_EQUAL(0.0, exactDiscount.applyDiscount(100.0));

                CHECK_EQUAL(0.0, exactDiscount.applyDiscount(50.0));

        Discount smallDiscount("SMALL", 0.01, false);
                CHECK_CLOSE(0.99, smallDiscount.applyDiscount(1.0), 0.0001);
    }

    TEST(TestInvalidDiscountApplication) {
        Discount discount("NEGATIVE", 10.0, true);
                CHECK_EQUAL(-90.0, discount.applyDiscount(-100.0));

                CHECK_EQUAL(0.0, discount.applyDiscount(0.0));
    }
}