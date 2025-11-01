#include "../../Source/PostMachine/PostMachine.h"
#include "UnitTest++.h"

TEST(PostMachinePreIncrement) {
    PostMachine machine;

    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    ++machine;
            CHECK_EQUAL(1, machine.getTape().readCell());
            CHECK_EQUAL(2, machine.getCurrentLine());
            CHECK(machine.isRunningCheck());

    ++machine;
            CHECK(!machine.isRunningCheck());
}

TEST(PostMachinePostIncrement) {
    PostMachine machine;

    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    PostMachine oldMachine = machine++;

            CHECK_EQUAL(0, oldMachine.getTape().readCell());
            CHECK_EQUAL(1, oldMachine.getCurrentLine());

            CHECK_EQUAL(1, machine.getTape().readCell());
            CHECK_EQUAL(2, machine.getCurrentLine());

    machine++;
            CHECK(!machine.isRunningCheck());
}
