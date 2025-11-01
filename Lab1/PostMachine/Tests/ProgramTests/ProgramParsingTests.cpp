#include "../../Source/Program/Program.h"
#include "UnitTest++.h"

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