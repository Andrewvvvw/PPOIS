#include "UnitTest++.h"
#include "../../Source/Tape/Tape.h"

TEST(TapeSetEraseRead) {
    Tape tape;
            CHECK_EQUAL(0, tape.readCell());
    tape.setMark();
            CHECK_EQUAL(1, tape.readCell());
            CHECK_THROW(tape.setMark(), std::runtime_error);

    tape.eraseMark();
            CHECK_EQUAL(0, tape.readCell());
            CHECK_THROW(tape.eraseMark(), std::runtime_error);

    tape.moveRight();
            CHECK_EQUAL(0, tape.readCell());
    tape.moveLeft();
            CHECK_EQUAL(0, tape.readCell());

    tape.setCell(10, 1);
            CHECK_EQUAL(1, tape.readCellAt(10));
    tape.setCell(10, 0);
            CHECK_EQUAL(0, tape.readCellAt(10));
            CHECK_THROW(tape.setCell(5, 2), std::invalid_argument);
}

TEST(TapeSetEraseRead2) {
    Tape tape;

            CHECK_EQUAL(0, tape.readCell());

    tape.setMark();
            CHECK_EQUAL(1, tape.readCell());

            CHECK_THROW(tape.setMark(), std::runtime_error);

    tape.eraseMark();
            CHECK_EQUAL(0, tape.readCell());

            CHECK_THROW(tape.eraseMark(), std::runtime_error);
}

TEST(TapeMoveAndCellAccess) {
    Tape tape;
    tape.setCell(5, 1);
            CHECK_EQUAL(1, tape.readCellAt(5));
    tape.setCarriagePosition(5);
            CHECK_EQUAL(1, tape.readCell());

    tape.moveLeft();
            CHECK_EQUAL(0, tape.readCell());
    tape.moveRight();
            CHECK_EQUAL(1, tape.readCell());
}