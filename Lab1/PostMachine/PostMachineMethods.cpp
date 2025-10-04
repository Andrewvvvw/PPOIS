#include "PostMachine.hpp"
#include <sstream>
#include <stdexcept>

constexpr int MAX_STEPS = 100000;

Command::Command(CommandType t, int next)
        : type(t), nextLine(next), nextIfZero(-1), nextIfOne(-1) {}

Command::Command(CommandType t, int ifZero, int ifOne)
        : type(t), nextLine(-1), nextIfZero(ifZero), nextIfOne(ifOne) {}

std::string Command::toString() const {
    switch (type) {
        case CommandType::SET_MARK:   return toStringSimple("V");
        case CommandType::ERASE_MARK: return toStringSimple("X");
        case CommandType::MOVE_LEFT:  return toStringSimple("<-");
        case CommandType::MOVE_RIGHT: return toStringSimple("->");
        case CommandType::CONDITION:  return toStringCondition();
        case CommandType::STOP:       return toStringStop();
        default: return "Unknown";
    }
}

std::string Command::toStringSimple(const std::string& symbol) const {
    std::ostringstream outStream;
    outStream << symbol << " " << (nextLine == -1 ? "?" : std::to_string(nextLine));
    return outStream.str();
}

std::string Command::toStringCondition() const {
    std::ostringstream outStream;
    outStream << "? "
        << (nextIfZero == -1 ? "?" : std::to_string(nextIfZero))
        << "; "
        << (nextIfOne == -1 ? "?" : std::to_string(nextIfOne));
    return outStream.str();
}

std::string Command::toStringStop() {
    return "!";
}


Tape::Tape() : carriagePosition(0) {}

void Tape::setMark() {
    if (readCell() == 1) {
        throw std::runtime_error("Attempted to set a mark on an already marked cell at position " +
                                 std::to_string(carriagePosition));
    }
    cells[carriagePosition] = 1;
}

void Tape::eraseMark() {
    if (readCell() == 0) {
        throw std::runtime_error("Attempted to erase a non-existent mark at position " +
                                 std::to_string(carriagePosition));
    }
    cells.erase(carriagePosition);
}

int Tape::readCell() const {
    auto iterator = cells.find(carriagePosition);
    return (iterator != cells.end()) ? iterator->second : 0;
}

void Tape::moveLeft() { carriagePosition--; }
void Tape::moveRight() { carriagePosition++; }

void Tape::setCell(int position, int value) {
    if (value != 0 && value != 1) {
        throw std::invalid_argument("Cell value must be 0 or 1");
    }
    if (value == 1) cells[position] = 1;
    else cells.erase(position);
}

void Tape::loadFromStream(std::istream& inStream) {
    cells.clear();
    int carriagePos;
    std::string tapeString;
    if (!(inStream >> carriagePos)) {
        throw std::runtime_error("Failed to read carriage position");
    }
    inStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::getline(inStream, tapeString)) {
        throw std::runtime_error("Failed to read tape content");
    }
    for (size_t i = 0; i < tapeString.length(); ++i) {
        if (tapeString[i] == '1')
            cells[(int)i] = 1;
        else if (tapeString[i] != '0')
            throw std::runtime_error("Invalid symbol on tape: " + std::string(1, tapeString[i]));
    }
    carriagePosition = carriagePos;
}

void Tape::print(std::ostream& outStream, int range) const {
    outStream << "Tape: ";
    for (int pos = carriagePosition - range; pos <= carriagePosition + range; ++pos) {
        auto iterator = cells.find(pos);
        outStream << (iterator != cells.end() ? iterator->second : 0);
    }
    outStream << "\nCarriage position: " << carriagePosition << "\n";
}

int Tape::readCellAt(int position) const {
    auto iterator = cells.find(position);
    return (iterator != cells.end() ? iterator->second : 0);
}


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



PostMachine::PostMachine() : currentLine(1), isRunning(false), logEnabled(false), stepsExecuted(0) {}

void PostMachine::loadFromStream(std::istream& inStream) {
    std::string line;
    while (std::getline(inStream, line))
        if (line.find("[TAPE]") != std::string::npos) { tape.loadFromStream(inStream); break; }
    while (std::getline(inStream, line))
        if (line.find("[PROGRAM]") != std::string::npos) { program.loadFromStream(inStream); break; }

    currentLine = program.getStartLine();
    isRunning = true;
    stepsExecuted = 0;
}

int PostMachine::computeDefaultNextLine(int afterLine) const {
    return program.getNextLineAfter(afterLine);
}

void PostMachine::executeSetMark(const Command& command) {
    tape.setMark();
    int next = command.getNextLine();
    if (next == -1) next = computeDefaultNextLine(currentLine);
    currentLine = (next == -1) ? (isRunning = false, currentLine) : next;
}

void PostMachine::executeEraseMark(const Command& command) {
    tape.eraseMark();
    int next = command.getNextLine();
    currentLine = (next == -1) ? (isRunning = false, currentLine) : next;
}

void PostMachine::executeMoveLeft(const Command& command) {
    tape.moveLeft();
    int next = command.getNextLine();
    currentLine = (next == -1) ? (isRunning = false, currentLine) : next;
}

void PostMachine::executeMoveRight(const Command& command) {
    tape.moveRight();
    int next = command.getNextLine();
    currentLine = (next == -1) ? (isRunning = false, currentLine) : next;
}

void PostMachine::executeCondition(const Command& command) {
    int dest = (tape.readCell() == 0) ? command.getNextIfZero() : command.getNextIfOne();
    if (dest == -1) dest = computeDefaultNextLine(currentLine);
    currentLine = (dest == -1) ? (isRunning = false, currentLine) : dest;
}

void PostMachine::executeStop(const Command&) {
    isRunning = false;
}

void PostMachine::executeCommand(const Command& command) {
    switch (command.getType()) {
        case CommandType::SET_MARK:    executeSetMark(command); break;
        case CommandType::ERASE_MARK:  executeEraseMark(command); break;
        case CommandType::MOVE_LEFT:   executeMoveLeft(command); break;
        case CommandType::MOVE_RIGHT:  executeMoveRight(command); break;
        case CommandType::CONDITION:   executeCondition(command); break;
        case CommandType::STOP:        executeStop(command); break;
    }
}

bool PostMachine::step() {
    if (!isRunning) return false;
    const Command* command = program.getCommand(currentLine);
    if (command == nullptr) throw std::runtime_error("Command " + std::to_string(currentLine) + " not found");

    if (logEnabled) {
        std::cout << "\n=== Step " << (stepsExecuted + 1) << " ===\n";
        std::cout << "Executing command " << currentLine << ". " << command->toString() << "\n";
    }

    try {
        executeCommand(*command);
        stepsExecuted++;
        if (logEnabled) printState(std::cout);
        return isRunning;
    } catch (const std::exception& e) {
        isRunning = false;
        std::cerr << "Execution error at line " << currentLine << ": " << e.what() << "\n";
        return false;
    }
}

void PostMachine::run() {
    while (isRunning && stepsExecuted < MAX_STEPS) if (!step()) break;
    if (stepsExecuted >= MAX_STEPS) std::cerr << "Warning: maximum steps reached (" << MAX_STEPS << "), possible infinite loop\n";
}

void PostMachine::reset() {
    currentLine = program.getStartLine();
    isRunning = true;
    stepsExecuted = 0;
}

PostMachine& PostMachine::operator++() { step(); return *this; }
PostMachine PostMachine::operator++(int) { PostMachine temporaryMachine = *this; step(); return temporaryMachine; }

void PostMachine::printState(std::ostream& outStream) const {
    outStream << "Current line: " << currentLine << "\n";
    outStream << "Steps executed: " << stepsExecuted << "\n";
    tape.print(outStream);
}
