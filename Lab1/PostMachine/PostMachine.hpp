#ifndef POST_MACHINE_H
#define POST_MACHINE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <limits>

enum class CommandType {
    SET_MARK,      // V - place a mark
    ERASE_MARK,    // X - erase a mark
    MOVE_LEFT,
    MOVE_RIGHT,
    CONDITION,     // ? - conditional jump
    STOP
};

/**
 * @brief Command class - represents a single instruction
 * Format: i. K j
 * where i - line number, K - action, j - next line
 */
class Command {
private:
    CommandType type;
    int nextLine;        // -1 if unspecified
    int nextIfZero;     // for ? - jump if 0
    int nextIfOne;      // for ? - jump if 1

    [[nodiscard]] std::string toStringSimple(const std::string& symbol) const;
    [[nodiscard]] std::string toStringCondition() const;
    [[nodiscard]] static std::string toStringStop() ;
public:
    Command(CommandType t, int next = -1);
    Command(CommandType t, int ifZero, int ifOne);

    [[nodiscard]] CommandType getType() const { return type; }
    [[nodiscard]] int getNextLine() const { return nextLine; }
    [[nodiscard]] int getNextIfZero() const { return nextIfZero; }
    [[nodiscard]] int getNextIfOne() const { return nextIfOne; }

    [[nodiscard]] std::string toString() const;

    bool operator==(const Command& other) const;
    bool operator!=(const Command& other) const;
};

/**
 * @brief Class represents the Post machine tape
 */
class Tape {
private:
    std::map <int, int> cells;
    int carriagePosition;

public:
    Tape();

    void setMark();
    void eraseMark();
    [[nodiscard]] int readCell() const;

    void moveLeft();
    void moveRight();

    [[nodiscard]] int getCarriagePosition() const { return carriagePosition; }
    void setCarriagePosition(int pos) { carriagePosition = pos; }

    void loadFromStream(std::istream& inStream);
    void print(std::ostream& outStream, int range = 20) const;

    void setCell(int position, int value);
    [[nodiscard]] int readCellAt(int position) const;

    bool operator==(const Tape& other) const;
    bool operator!=(const Tape& other) const;
};

/**
 * @brief Class represents a program for the Post machine
 */
class Program {
private:
    std::map<int, Command> commands;
    int startLine;

    void parseCommandLine(const std::string& line);
    void parseCommand(int lineNum, const std::string& commandString, std::istringstream& inStream);
    void parseSingleNext(int lineNum, CommandType type, std::istringstream& inStream);
    void parseConditional(int lineNum, std::istringstream& inStream);
public:
    Program();

    void addCommand(int lineNum, const Command& command);
    void removeCommand(int lineNumber);
    [[nodiscard]] const Command* getCommand(int lineNumber) const;
    [[nodiscard]] bool hasCommand(int lineNumber) const;

    [[nodiscard]] int getNextLineAfter(int lineNumber) const;

    void loadFromStream(std::istream& inStream);
    void print(std::ostream& outStream) const;

    [[nodiscard]] int getStartLine() const { return startLine; }
    void setStartLine(int line) { startLine = line; }

    bool operator==(const Program& other) const;
    bool operator!=(const Program& other) const;

    friend class ProgramTest;
};

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

    void executeCommand(const Command& commad);
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
    [[nodiscard]] const Tape& getTape() const { return tape; }
    Program& getProgram() { return program; }
    [[nodiscard]] const Program& getProgram() const { return program; }

    [[nodiscard]] bool isRunningCheck() const { return isRunning; }
    [[nodiscard]] int getCurrentLine() const { return currentLine; }
    [[nodiscard]] int getStepsExecuted() const { return stepsExecuted; }

    void printState(std::ostream& outStream) const;

    bool operator==(const PostMachine& other) const;
    bool operator!=(const PostMachine& other) const;
};

#endif // POST_MACHINE_H
