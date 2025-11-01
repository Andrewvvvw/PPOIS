#include "../../Source/Program/Program.h"
#include "UnitTest++.h"

TEST(ProgramAddGetRemove) {
    Program program;
    Command command(CommandType::SET_MARK, 2);

    program.addCommand(1, command);
    const Command* pointer = program.getCommand(1);
            CHECK(pointer != nullptr);
            CHECK(CommandType::SET_MARK == pointer->getType());

            CHECK(program.hasCommand(1));

    program.removeCommand(1);
            CHECK(program.getCommand(1) == nullptr);
            CHECK(!program.hasCommand(1));
}

TEST(ProgramGetNextLine) {
    Program program;
    program.addCommand(1, Command(CommandType::SET_MARK, 2));
    program.addCommand(3, Command(CommandType::MOVE_RIGHT, 4));

            CHECK_EQUAL(3, program.getNextLineAfter(1));
            CHECK_EQUAL(-1, program.getNextLineAfter(3));
}
TEST(ProgramAddGetRemove2) {
    Program program;
    Command command(CommandType::SET_MARK, 2);
    program.addCommand(1, command);

    const Command* pointer = program.getCommand(1);
            CHECK(pointer != nullptr);
            CHECK(CommandType::SET_MARK == pointer->getType());

    program.removeCommand(1);
            CHECK(program.getCommand(1) == nullptr);
}

TEST(ProgramNextLine) {
    Program program;
    program.addCommand(1, Command(CommandType::SET_MARK));
    program.addCommand(3, Command(CommandType::STOP));
            CHECK_EQUAL(3, program.getNextLineAfter(1));
            CHECK_EQUAL(-1, program.getNextLineAfter(3));
}
