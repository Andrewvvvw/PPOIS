#ifndef POST_MACHINE_H
#define POST_MACHINE_H

#include <map>
#include <string>
#include <iostream>
#include <limits>
#include "../Tape/Tape.h"
#include "../Program/Program.h"

/**
 * @brief PostMachine class
 */
class PostMachine {
private:
    Tape tape;
    Program program;
    int currentLine;
    bool isRunning;
    bool logEnabled;
    int stepsExecuted;

    void executeCommand(const Command& command);
    [[nodiscard]] int computeDefaultNextLine(int afterLine) const;

    void executeEraseMark(const Command& command);
    void executeSetMark(const Command& command);
    void executeStop(const Command&);
    void executeCondition(const Command& command);
    void executeMoveRight(const Command& command);
    void executeMoveLeft(const Command& command);

public:
    ~PostMachine()=default;
    PostMachine();

    void loadFromStream(std::istream& in);
    bool step();
    void run();
    void reset();

    void enableLog(bool enable) { logEnabled = enable; }

    PostMachine& operator++();
    PostMachine operator++(int);

    Tape& getTape() { return tape; }
    Program& getProgram() { return program; }

    [[nodiscard]] bool isRunningCheck() const { return isRunning; }
    [[nodiscard]] int getCurrentLine() const { return currentLine; }
    [[nodiscard]] int getStepsExecuted() const { return stepsExecuted; }

    void printState(std::ostream& outStream) const;

};

#endif // POST_MACHINE_H
