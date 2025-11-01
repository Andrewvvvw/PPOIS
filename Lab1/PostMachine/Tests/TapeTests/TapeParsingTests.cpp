#include "UnitTest++.h"
#include "../../Source/Tape/Tape.h"

TEST(Tape_LoadFromStream_EmptyTape) {
        std::istringstream input("0\n000\n");
        Tape tape;
        tape.loadFromStream(input);
        CHECK_EQUAL(0, tape.getCarriagePosition());
        CHECK_EQUAL(0, tape.readCellAt(-1));
        CHECK_EQUAL(0, tape.readCellAt(0));
        CHECK_EQUAL(0, tape.readCellAt(1));
}

TEST(Tape_LoadFromStream_Simple) {
        std::istringstream input("0\n101\n");
        Tape tape;
        tape.loadFromStream(input);
        CHECK_EQUAL(0, tape.getCarriagePosition());

        CHECK_EQUAL(1, tape.readCellAt(0));
        CHECK_EQUAL(0, tape.readCellAt(1));
        CHECK_EQUAL(1, tape.readCellAt(2));
}

TEST(Tape_LoadFromStream_CustomCarriage) {
        std::istringstream input("5\n010\n");
        Tape tape;
        tape.loadFromStream(input);
        CHECK_EQUAL(5, tape.getCarriagePosition());

        CHECK_EQUAL(0, tape.readCellAt(0));
        CHECK_EQUAL(1, tape.readCellAt(1));
        CHECK_EQUAL(0, tape.readCellAt(2));
}

TEST(Tape_LoadFromStream_InvalidCarriage) {
        std::istringstream input("X\n010\n");
        Tape tape;
        CHECK_THROW(tape.loadFromStream(input), std::runtime_error);
}

TEST(Tape_LoadFromStream_MissingTapeLine) {
        std::istringstream input("0\n");
        Tape tape;
        CHECK_THROW(tape.loadFromStream(input), std::runtime_error);
}

TEST(Tape_LoadFromStream_InvalidCharacter) {
        std::istringstream input("0\n01X1\n");
        Tape tape;
        CHECK_THROW(tape.loadFromStream(input), std::runtime_error);
}

TEST(TapeLoadFromStream) {
    std::istringstream input("2\n0101");
    Tape tape;
    tape.loadFromStream(input);
            CHECK_EQUAL(2, tape.getCarriagePosition());
            CHECK_EQUAL(0, tape.readCellAt(0));
            CHECK_EQUAL(1, tape.readCellAt(1));
            CHECK_EQUAL(0, tape.readCellAt(2));
            CHECK_EQUAL(1, tape.readCellAt(3));

    std::istringstream badInput("0\n01a0");
            CHECK_THROW(Tape().loadFromStream(badInput), std::runtime_error);
}
