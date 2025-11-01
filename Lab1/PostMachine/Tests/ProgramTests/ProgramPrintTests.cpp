#include "../../Source/Program/Program.h"
#include "UnitTest++.h"
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
