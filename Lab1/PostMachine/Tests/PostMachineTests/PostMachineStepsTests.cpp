#include "../../Source/PostMachine/PostMachine.h"
#include "UnitTest++.h"

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

std::string createSimpleProgram() {
    return "[TAPE]\n0\n0\n[PROGRAM]\n1. V 2\n2. !\n";
}

std::string createProgramWithCondition() {
    return "[TAPE]\n0\n0\n[PROGRAM]\n1. ? 2; 3\n2. V 4\n3. X 4\n4. !\n";
}


TEST(Step_ReturnsFalseWhenNotRunning) {
    PostMachine machine;
    std::istringstream input(createSimpleProgram());
    machine.loadFromStream(input);

    machine.step();
    machine.step();
    bool result = machine.step();
            CHECK_EQUAL(false, result);
}

TEST(Step_ThrowsWhenCommandNotFound) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. V 99\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_THROW(machine.step(), std::runtime_error);
}

TEST(Run_StopsOnMaxSteps) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. V 2\n2. X 1\n");
    machine.loadFromStream(input);

    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::ostringstream capturedCerr;
    std::cerr.rdbuf(capturedCerr.rdbuf());

    machine.run();

    std::cerr.rdbuf(oldCerr);

            CHECK_EQUAL(100000, machine.getStepsExecuted());
            CHECK(capturedCerr.str().find("maximum steps") != std::string::npos);
}
TEST(ExecuteSetMark_WithoutNextLineAndNoDefault_StopsMachine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. V\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(false, machine.isRunningCheck());
}
TEST(ExecuteMoveRight_WithoutNextLine_StopsMachine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. ->\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(false, machine.isRunningCheck());
}

TEST(ExecuteMoveLeft_WithoutNextLine_StopsMachine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. <-\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(false, machine.isRunningCheck());
}

TEST(ExecuteCondition_WithZero_JumpsToFirstBranch) {
    PostMachine machine;
    std::istringstream input(createProgramWithCondition());
    machine.loadFromStream(input);

    machine.step();

            CHECK_EQUAL(2, machine.getCurrentLine());
}

TEST(ExecuteCondition_WithOne_JumpsToSecondBranch) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n1\n[PROGRAM]\n1. ? 2; 3\n2. V 4\n3. X 4\n4. !\n");
    machine.loadFromStream(input);

    machine.step();

            CHECK_EQUAL(3, machine.getCurrentLine());
}

TEST(ExecuteCondition_WithoutNextLine_UsesDefaultNext) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. ? -1; -1\n2. !\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(2, machine.getCurrentLine());
}

TEST(ExecuteCondition_WithoutNextLineAndNoDefault_StopsMachine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. ? -1; -1\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(false, machine.isRunningCheck());
}

TEST(ExecuteStop_StopsMachine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. !\n");
    machine.loadFromStream(input);

    machine.step();

            CHECK_EQUAL(false, machine.isRunningCheck());
}

TEST(ComputeDefaultNextLine_ReturnsNextCommandLine) {
    PostMachine machine;
    std::istringstream input("[TAPE]\n0\n0\n[PROGRAM]\n1. V\n5. !\n");
    machine.loadFromStream(input);

    machine.step();
            CHECK_EQUAL(5, machine.getCurrentLine());
}

TEST(Step_WithLogging_PrintsExecutionDetails) {
    PostMachine machine;
    machine.enableLog(true);
    std::istringstream input(createSimpleProgram());
    machine.loadFromStream(input);

    std::streambuf* oldCout = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    machine.step();

    std::cout.rdbuf(oldCout);

    std::string output = capturedOutput.str();
            CHECK(output.find("Current line:") != std::string::npos);
            CHECK(output.find("Steps executed:") != std::string::npos);
            CHECK(output.find("Tape:") != std::string::npos);
}

TEST(IsRunningCheck_ReturnsTrueWhenRunning) {
    PostMachine machine;
    std::istringstream input(createSimpleProgram());
    machine.loadFromStream(input);

            CHECK_EQUAL(true, machine.isRunningCheck());
}

TEST(IsRunningCheck_ReturnsFalseWhenStopped) {
    PostMachine machine;
            CHECK_EQUAL(false, machine.isRunningCheck());
}

TEST(GetCurrentLine_ReturnsCorrectLine) {
    PostMachine machine;
    std::istringstream input(createSimpleProgram());
    machine.loadFromStream(input);

            CHECK_EQUAL(1, machine.getCurrentLine());
    machine.step();
            CHECK_EQUAL(2, machine.getCurrentLine());
}

TEST(GetStepsExecuted_ReturnsCorrectCount) {
    PostMachine machine;
    std::istringstream input(createSimpleProgram());
    machine.loadFromStream(input);

            CHECK_EQUAL(0, machine.getStepsExecuted());
    machine.step();
            CHECK_EQUAL(1, machine.getStepsExecuted());
    machine.step();
            CHECK_EQUAL(2, machine.getStepsExecuted());
}