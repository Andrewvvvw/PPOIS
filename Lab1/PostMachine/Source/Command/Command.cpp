#include "Command.h"
#include <sstream>

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
