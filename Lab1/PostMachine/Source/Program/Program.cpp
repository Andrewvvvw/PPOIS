#include "Program.h"
#include <sstream>

Program::Program() : startLine(1) {}

void Program::addCommand(int lineNumber, const Command& command) {
    commands.insert_or_assign(lineNumber, command);
}

void Program::removeCommand(int lineNumber) { commands.erase(lineNumber); }

const Command* Program::getCommand(int lineNumber) const {
    auto iterator = commands.find(lineNumber);
    return (iterator != commands.end()) ? &(iterator->second) : nullptr;
}

bool Program::hasCommand(int lineNumber) const {
    return commands.find(lineNumber) != commands.end();
}

int Program::getNextLineAfter(int lineNumber) const {
    auto iterator = commands.upper_bound(lineNumber);
    return (iterator == commands.end()) ? -1 : iterator->first;
}

void Program::parseCommandLine(const std::string& line) {
    if (line.empty() || line[0] == '#') return;

    std::istringstream inStream(line);
    int lineNumber;
    char dot;
    if (!(inStream >> lineNumber >> dot) || dot != '.') return;

    std::string commandString;
    if (!(inStream >> commandString))
        throw std::runtime_error("Missing command on line " + std::to_string(lineNumber));

    parseCommand(lineNumber, commandString, inStream);
}

void Program::parseCommand(int lineNumber, const std::string& commandString, std::istringstream& inStream) {
    if (commandString == "V") parseSingleNext(lineNumber, CommandType::SET_MARK, inStream);
    else if (commandString == "X") parseSingleNext(lineNumber, CommandType::ERASE_MARK, inStream);
    else if (commandString == "<-" || commandString == "←") parseSingleNext(lineNumber, CommandType::MOVE_LEFT, inStream);
    else if (commandString == "->" || commandString == "→") parseSingleNext(lineNumber, CommandType::MOVE_RIGHT, inStream);
    else if (commandString == "?") parseConditional(lineNumber, inStream);
    else if (commandString == "!") addCommand(lineNumber, Command(CommandType::STOP, -1));
    else throw std::runtime_error("Unknown command: " + commandString);
}

void Program::parseSingleNext(int lineNumber, CommandType type, std::istringstream& inStream) {
    int next = -1;
    inStream >> next;
    addCommand(lineNumber, Command(type, next));
}

void Program::parseConditional(int lineNumber, std::istringstream& inStream) {
    int ifZero = -1, ifOne = -1;
    if (!(inStream >> ifZero))
        throw std::runtime_error("Missing first argument for conditional command on line " + std::to_string(lineNumber));

    char separator = 0;
    if (!(inStream >> separator) || separator != ';')
        throw std::runtime_error("Expected ';' in conditional command on line " + std::to_string(lineNumber));

    if (!(inStream >> ifOne))
        throw std::runtime_error("Missing second argument for conditional command on line " + std::to_string(lineNumber));

    addCommand(lineNumber, Command(CommandType::CONDITION, ifZero, ifOne));
}

void Program::loadFromStream(std::istream& inStream) {
    commands.clear();
    std::string line;

    while (std::getline(inStream, line)) parseCommandLine(line);

    if (commands.empty())
        throw std::runtime_error("Program contains no commands");

    startLine = commands.begin()->first;
}

void Program::print(std::ostream& outStream) const {
    outStream << "Program:\n";
    for (const auto& pair : commands)
        outStream << pair.first << ". " << pair.second.toString() << "\n";
}
