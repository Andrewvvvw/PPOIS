#include "../../Source/PostMachine/PostMachine.h"
#include "UnitTest++.h"

TEST(PostMachineLoadFromStream2) {
    std::istringstream input(
            "[TAPE]\n"
            "0\n"
            "0101\n"
            "[PROGRAM]\n"
            "1. V 2\n"
            "2. -> 3\n"
            "3. X 4\n"
            "4. !\n"
    );

    PostMachine machine;
    machine.loadFromStream(input);

            CHECK_EQUAL(1, machine.getCurrentLine());
            CHECK(machine.isRunningCheck());
            CHECK_EQUAL(0, machine.getTape().getCarriagePosition());
            CHECK_EQUAL(0, machine.getTape().readCellAt(0));
            CHECK_EQUAL(1, machine.getTape().readCellAt(1));
            CHECK_EQUAL(0, machine.getTape().readCellAt(2));
            CHECK_EQUAL(1, machine.getTape().readCellAt(3));

    const Command* command1 = machine.getProgram().getCommand(1);
            CHECK(command1 != nullptr);
            CHECK(command1->getType() == CommandType::SET_MARK);
            CHECK_EQUAL(2, command1->getNextLine());

    const Command* command2 = machine.getProgram().getCommand(2);
            CHECK(command2 != nullptr);
            CHECK(command2->getType() == CommandType::MOVE_RIGHT);
            CHECK_EQUAL(3, command2->getNextLine());

    const Command* command4 = machine.getProgram().getCommand(4);
            CHECK(command4 != nullptr);
            CHECK(command4->getType() == CommandType::STOP);

            CHECK_EQUAL(0, machine.getStepsExecuted());
}

TEST(LoadFromStream_WithComplexProgram) {
    PostMachine machine;
    std::string program = "[TAPE]\n5\n000111000\n[PROGRAM]\n1. -> 2\n2. <- 3\n3. V 4\n4. X 5\n5. ? 6; 7\n6. !\n7. !\n";
    std::istringstream input(program);

    machine.loadFromStream(input);

            CHECK_EQUAL(1, machine.getCurrentLine());
            CHECK_EQUAL(true, machine.isRunningCheck());
}