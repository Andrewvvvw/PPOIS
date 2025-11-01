#include "UnitTest++.h"
#include "../../Source/Command/Command.h"

TEST(CommandToString) {
    Command setMark(CommandType::SET_MARK, 5);
            CHECK_EQUAL("V 5", setMark.toString());

    Command setMarkNoNext(CommandType::SET_MARK);
            CHECK_EQUAL("V ?", setMarkNoNext.toString());

    Command eraseMark(CommandType::ERASE_MARK, 10);
            CHECK_EQUAL("X 10", eraseMark.toString());

    Command eraseMarkNoNext(CommandType::ERASE_MARK);
            CHECK_EQUAL("X ?", eraseMarkNoNext.toString());

    Command moveLeft(CommandType::MOVE_LEFT, 3);
            CHECK_EQUAL("<- 3", moveLeft.toString());

    Command moveLeftNoNext(CommandType::MOVE_LEFT);
            CHECK_EQUAL("<- ?", moveLeftNoNext.toString());

    Command moveRight(CommandType::MOVE_RIGHT, 7);
            CHECK_EQUAL("-> 7", moveRight.toString());

    Command moveRightNoNext(CommandType::MOVE_RIGHT);
            CHECK_EQUAL("-> ?", moveRightNoNext.toString());

    Command condition(CommandType::CONDITION, 2, 5);
            CHECK_EQUAL("? 2; 5", condition.toString());

    Command condNoNext(CommandType::CONDITION);
            CHECK_EQUAL("? ?; ?", condNoNext.toString());

    Command stop(CommandType::STOP);
            CHECK_EQUAL("!", stop.toString());
}

TEST(CommandToString2) {
    Command command1(CommandType::SET_MARK, 5);
            CHECK_EQUAL("V 5", command1.toString());

    Command command2(CommandType::ERASE_MARK);
            CHECK_EQUAL("X ?", command2.toString());

    Command command3(CommandType::MOVE_LEFT, 3);
            CHECK_EQUAL("<- 3", command3.toString());

    Command command4(CommandType::MOVE_RIGHT);
            CHECK_EQUAL("-> ?", command4.toString());

    Command command5(CommandType::CONDITION, 1, 2);
            CHECK_EQUAL("? 1; 2", command5.toString());

    Command command6(CommandType::STOP);
            CHECK_EQUAL("!", command6.toString());
}