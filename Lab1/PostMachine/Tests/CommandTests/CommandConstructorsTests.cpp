#include "UnitTest++.h"
#include "../../Source/Command/Command.h"

TEST(CommandConstructorsAndToString) {
    Command setMark(CommandType::SET_MARK, 5);
            CHECK(setMark.getType() == CommandType::SET_MARK);
            CHECK_EQUAL(5, setMark.getNextLine());
            CHECK_EQUAL(-1, setMark.getNextIfZero());
            CHECK_EQUAL(-1, setMark.getNextIfOne());
            CHECK_EQUAL("V 5", setMark.toString());

    Command condition(CommandType::CONDITION, 2, 3);
            CHECK(condition.getType() == CommandType::CONDITION);
            CHECK_EQUAL(-1, condition.getNextLine());
            CHECK_EQUAL(2, condition.getNextIfZero());
            CHECK_EQUAL(3, condition.getNextIfOne());
            CHECK_EQUAL("? 2; 3", condition.toString());

    Command stop(CommandType::STOP);
            CHECK_EQUAL("!", stop.toString());
}