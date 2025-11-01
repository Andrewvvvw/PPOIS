#include "UnitTest++.h"
#include "../../Source/Tape/Tape.h"

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
