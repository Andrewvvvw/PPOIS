#include "PostMachine.hpp"
#include "UnitTest++.h"
#include <sstream>

class ProgramTest {
public:
    static void testParseCommandLine() {
        Program p;

        // корректная строка
        std::string line = "1. V 2";
        //CHECK_NO_THROW(p.parseCommandLine(line));
        const Command* cmd = p.getCommand(1);
        CHECK(cmd != nullptr);
        CHECK(CommandType::SET_MARK == cmd->getType());
        CHECK_EQUAL(2, cmd->getNextLine());

        // комментарий
        //CHECK_NO_THROW(p.parseCommandLine("# this is a comment"));
        CHECK_EQUAL(1, p.getStartLine()); // ничего не изменилось

        // пустая строка
        //CHECK_NO_THROW(p.parseCommandLine(""));
        CHECK_EQUAL(1, p.getStartLine());

        // некорректная строка
        std::string badLine = "2. ?"; // нет аргументов
        CHECK_THROW(p.parseCommandLine(badLine), std::runtime_error);
    }
};

TEST(ProgramParseCommandLine) {
        ProgramTest::testParseCommandLine();
}
