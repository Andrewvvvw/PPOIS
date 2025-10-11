#include "PostMachine.hpp"
#include "UnitTest++.h"
#include <sstream>

SUITE(ProgramParsingTests) {

    TEST (EmptyLineOrComment) {
        std::istringstream input("\n# comment\n");
        Program program;
        CHECK_THROW(program.loadFromStream(input), std::runtime_error);
    }

    TEST (StopCommand) {
        std::istringstream input("1. !\n");
        Program program;
        program.loadFromStream(input);

        const Command *command = program.getCommand(1);
        CHECK(command != nullptr);
        CHECK(command->getType() == CommandType::STOP);
        CHECK_EQUAL(-1, command->getNextLine());
    }

    TEST (SetMarkCommandWithNext) {
        std::istringstream input("1. V 5\n");
        Program program;
        program.loadFromStream(input);

        const Command *command = program.getCommand(1);
        CHECK(command != nullptr);
        CHECK(command->getType() == CommandType::SET_MARK);
        CHECK_EQUAL(5, command->getNextLine());
    }

    TEST (SetMarkCommandWithoutNext) {
        std::istringstream input("1. V\n2. !\n");
        Program program;
        program.loadFromStream(input);

        const Command *command = program.getCommand(1);
        CHECK(command->getType() == CommandType::SET_MARK);
        CHECK_EQUAL(-1, command->getNextLine());
    }

    TEST (EraseMarkCommand) {
        std::istringstream input("1. X 3\n2. !\n");
        Program program;
        program.loadFromStream(input);

        const Command *command = program.getCommand(1);
        CHECK(command->getType() == CommandType::ERASE_MARK);
        CHECK_EQUAL(3, command->getNextLine());
    }

    TEST (MoveLeftRightCommands) {
        std::istringstream input(
                "1. <- 2\n"
                "2. -> 3\n"
                "3. ← 4\n"
                "4. → 5\n"
        );
        Program program;
        program.loadFromStream(input);

        CHECK(CommandType::MOVE_LEFT == program.getCommand(1)->getType());
        CHECK_EQUAL(2, program.getCommand(1)->getNextLine());
        CHECK(CommandType::MOVE_RIGHT == program.getCommand(2)->getType());
        CHECK_EQUAL(3, program.getCommand(2)->getNextLine());
        CHECK(CommandType::MOVE_LEFT == program.getCommand(3)->getType());
        CHECK_EQUAL(4, program.getCommand(3)->getNextLine());
        CHECK(CommandType::MOVE_RIGHT == program.getCommand(4)->getType());
        CHECK_EQUAL(5, program.getCommand(4)->getNextLine());
    }

    TEST (ConditionalCommand) {
        std::istringstream input("1. ? 2 ; 3\n");
        Program program;
        program.loadFromStream(input);

        const Command *command = program.getCommand(1);
        CHECK(command->getType() == CommandType::CONDITION);
        CHECK_EQUAL(2, command->getNextIfZero());
        CHECK_EQUAL(3, command->getNextIfOne());
    }

    TEST (ConditionalCommandMissingArgs) {
        std::istringstream input("1. ? 2\n");
        Program program;
        CHECK_THROW(program.loadFromStream(input), std::runtime_error);

        std::istringstream input2("1. ? ; 3\n");
        CHECK_THROW(program.loadFromStream(input2), std::runtime_error);

        std::istringstream input3("1. ? 2 ;\n");
        CHECK_THROW(program.loadFromStream(input3), std::runtime_error);
    }

    TEST (UnknownCommand) {
        std::istringstream input("1. Z\n");
        Program program;
        CHECK_THROW(program.loadFromStream(input), std::runtime_error);
    }
}

TEST(ProgramLoadFromStream_ValidProgram) {
    std::istringstream input(
            "1. V 2\n"
            "2. X 3\n"
            "3. !\n"
    );

    Program program;
    program.loadFromStream(input);

    CHECK(program.hasCommand(1));
    CHECK(program.hasCommand(2));
    CHECK(program.hasCommand(3));
    CHECK(CommandType::SET_MARK == program.getCommand(1)->getType());
    CHECK(CommandType::ERASE_MARK == program.getCommand(2)->getType());
    CHECK(CommandType::STOP == program.getCommand(3)->getType());
}

TEST(ProgramLoadFromStream_InValidProgram) {
    std::istringstream input(
            "1. Y 2\n"
            "2. Y 3\n"
            "3. !\n"
    );
    Program program;
    CHECK_THROW(program.loadFromStream(input), std::runtime_error);

}

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

TEST(ProgramLoadFromStream_Valid) {
    Program program;
    std::istringstream input(
            "1. V 2\n"
            "2. -> 3\n"
            "3. !\n"
    );
    program.loadFromStream(input);

    CHECK_EQUAL(1, program.getStartLine());
    CHECK(CommandType::SET_MARK == program.getCommand(1)->getType());
    CHECK(CommandType::MOVE_RIGHT == program.getCommand(2)->getType());
    CHECK(CommandType::STOP == program.getCommand(3)->getType());
}

TEST(ProgramLoadFromStream_Invalid) {
    Program program;
    std::istringstream input_empty("");
    CHECK_THROW(program.loadFromStream(input_empty), std::runtime_error);

    std::istringstream input_unknown("1. Z\n");
    CHECK_THROW(program.loadFromStream(input_unknown), std::runtime_error);

    std::istringstream input_cond_missing("1. ? ; 2\n");
    CHECK_THROW(program.loadFromStream(input_cond_missing), std::runtime_error);
}

TEST(PostMachineStepSetMark) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    CHECK(machine.step());
    CHECK_EQUAL(1, machine.getTape().readCell());
    CHECK_EQUAL(2, machine.getCurrentLine());

    CHECK(!machine.step());
    CHECK(!machine.isRunningCheck());
}

TEST(PostMachineStepEraseMark) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getTape().setMark();
    machine.getProgram().addCommand(1, Command(CommandType::ERASE_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    CHECK(machine.step());
    CHECK_EQUAL(0, machine.getTape().readCell());
    CHECK_EQUAL(2, machine.getCurrentLine());
}

TEST(PostMachineStepMoveRightLeft) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::MOVE_RIGHT, 2));
    machine.getProgram().addCommand(2, Command(CommandType::MOVE_LEFT, 3));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    CHECK(machine.step());
    CHECK_EQUAL(1, machine.getTape().getCarriagePosition());
    CHECK(machine.step());
    CHECK_EQUAL(0, machine.getTape().getCarriagePosition());
}

TEST(PostMachineStepCondition) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::CONDITION, 2, 3));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    CHECK(machine.step());
    CHECK_EQUAL(2, machine.getCurrentLine());

    machine.reset();
    machine.getTape().setMark();
    CHECK(machine.step());
    CHECK_EQUAL(3, machine.getCurrentLine());
}

TEST(PostMachineRunMultipleSteps) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::MOVE_RIGHT, 3));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);
    machine.reset();

    machine.run();

    CHECK_EQUAL(1, machine.getTape().readCellAt(0));
    CHECK_EQUAL(1, machine.getTape().getCarriagePosition());
    CHECK_EQUAL(3, machine.getCurrentLine());
    CHECK(!machine.isRunningCheck());
}

TEST(PostMachineReset) {
    PostMachine machine;
    machine.getProgram().addCommand(1, Command(CommandType::STOP));
    machine.reset();
    CHECK(machine.isRunningCheck());
    CHECK_EQUAL(1, machine.getCurrentLine());
    CHECK_EQUAL(0, machine.getStepsExecuted());
}

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

TEST(TapePrint) {
    Tape tape;

    tape.setCell(0, 1);
    tape.setCell(2, 1);
    tape.setCarriagePosition(1);

    std::ostringstream outStream;
    tape.print(outStream, 2);

    std::string expectedOutput = "Tape: 01010\nCarriage position: 1\n";

    CHECK_EQUAL(expectedOutput, outStream.str());
}

TEST(TapePrintEmpty) {
    Tape tape;
    tape.setCarriagePosition(0);

    std::ostringstream outStream;
    tape.print(outStream, 1);

    std::string expectedOutput = "Tape: 000\nCarriage position: 0\n";

    CHECK_EQUAL(expectedOutput, outStream.str());
}

TEST(ProgramPrint) {
    Program program;

    program.addCommand(1, Command(CommandType::SET_MARK, 2));
    program.addCommand(2, Command(CommandType::MOVE_RIGHT, 3));
    program.addCommand(3, Command(CommandType::STOP));

    std::ostringstream outStream;
    program.print(outStream);

    std::string expected =
    "Program:\n"
    "1. V 2\n"
    "2. -> 3\n"
    "3. !\n";

    CHECK_EQUAL(expected, outStream.str());
}

TEST(LoadFromStream) {
    std::string data =
            "# Example program\n"
            "1. V 2\n"
            "2. X 3\n"
            "3. -> 4\n"
            "4. <-\n"
            "5. ? 2 ; 3\n"
            "6. !\n";

    std::istringstream input(data);
    Program program;
    program.loadFromStream(input);

    CHECK_EQUAL(6, program.getNextLineAfter(5));
    const Command* command1 = program.getCommand(1);
    CHECK(command1 != nullptr);
    CHECK(CommandType::SET_MARK == command1->getType());

    const Command* command6 = program.getCommand(6);
    CHECK(command6 != nullptr);
    CHECK(CommandType::STOP == command6->getType());
}

TEST(LoadFromStream_EmptyProgram_Throws) {
    std::istringstream input("");
    Program program;
    CHECK_THROW(program.loadFromStream(input), std::runtime_error);
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

TEST(ProgramLoadFromStream) {
    std::istringstream input(
            "1. V 2\n"
            "2. X 3\n"
            "3. -> 4\n"
            "4. !\n"
    );
    Program program;
    program.loadFromStream(input);

    CHECK(program.hasCommand(1));
    CHECK(program.hasCommand(4));
    CHECK_EQUAL(1, program.getStartLine());
}

TEST(PostMachineStepSetMark2) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, -1));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.step();

    CHECK_EQUAL(1, machine.getTape().readCell());
    CHECK_EQUAL(2, machine.getCurrentLine());
}

TEST(PostMachineStepEraseMark2) {
    PostMachine machine;
    machine.getTape().setCell(0,1);
    machine.getProgram().addCommand(1, Command(CommandType::ERASE_MARK, -1));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.step();

    CHECK_EQUAL(0, machine.getTape().readCell());
}

TEST(PostMachineStepMoveRightLeft2) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::MOVE_RIGHT, 2));
    machine.getProgram().addCommand(2, Command(CommandType::MOVE_LEFT, 3));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.step();
    CHECK_EQUAL(1, machine.getTape().getCarriagePosition());

    machine.step();
    CHECK_EQUAL(0, machine.getTape().getCarriagePosition());
}

TEST(PostMachineStepCondition2) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::CONDITION, 2, 3));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.step();
    CHECK_EQUAL(2, machine.getCurrentLine());

    machine.getTape().setMark();
    machine.reset();
    machine.step();
    CHECK_EQUAL(3, machine.getCurrentLine());
}

TEST(PostMachineRunMultipleSteps2) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::MOVE_RIGHT, 3));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.run();

    CHECK_EQUAL(1, machine.getTape().readCellAt(0));
    CHECK_EQUAL(1, machine.getTape().getCarriagePosition());
    CHECK_EQUAL(3, machine.getCurrentLine());
    CHECK(!machine.isRunningCheck());
}

TEST(PostMachineStepSetMark3) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);

    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    bool running = machine.step();

    CHECK(running);
    CHECK_EQUAL(1, machine.getTape().readCellAt(0));
    CHECK_EQUAL(2, machine.getCurrentLine());
    CHECK_EQUAL(1, machine.getStepsExecuted());
}

TEST(PostMachineStepMoveRightLeft3) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);

    machine.getProgram().addCommand(1, Command(CommandType::MOVE_RIGHT, 2));
    machine.getProgram().addCommand(2, Command(CommandType::MOVE_LEFT, 3));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();

    machine.step();
    CHECK_EQUAL(1, machine.getTape().getCarriagePosition());
    CHECK_EQUAL(2, machine.getCurrentLine());

    machine.step();
    CHECK_EQUAL(0, machine.getTape().getCarriagePosition());
    CHECK_EQUAL(3, machine.getCurrentLine());

    machine.step();
    CHECK(!machine.isRunningCheck());
}

TEST(PostMachineStepCondition3) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);

    machine.getProgram().addCommand(1, Command(CommandType::CONDITION, 2, 3));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().addCommand(3, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.reset();
    machine.step();
    CHECK_EQUAL(2, machine.getCurrentLine());

    machine.reset();
    machine.getTape().setMark();
    machine.step();
    CHECK_EQUAL(3, machine.getCurrentLine());
}

TEST(PostMachineStepMissingCommand) {
    PostMachine machine;
    machine.getProgram().setStartLine(1);
    machine.reset();

    CHECK_THROW(machine.step(), std::runtime_error);
}

TEST(PostMachineStepLogging) {
    PostMachine machine;
    machine.getTape().setCarriagePosition(0);
    machine.getProgram().addCommand(1, Command(CommandType::SET_MARK, 2));
    machine.getProgram().addCommand(2, Command(CommandType::STOP));
    machine.getProgram().setStartLine(1);

    machine.enableLog(true);
    machine.reset();

    std::cout << "Step logging testing:\n";
    CHECK(machine.step());
    std::cout << "\n";
}

int main()
{
    return UnitTest::RunAllTests();
}