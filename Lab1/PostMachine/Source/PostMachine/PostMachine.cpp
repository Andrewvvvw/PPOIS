#include "PostMachine.h"
#include <sstream>
#include <stdexcept>

constexpr int MAX_STEPS = 100000;

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
