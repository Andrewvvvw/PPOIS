#ifndef LAB1_PROGRAM_H
#define LAB1_PROGRAM_H

#include <map>
#include <string>
#include <iostream>
#include "../Command/Command.h"

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

};

#endif //LAB1_PROGRAM_H
