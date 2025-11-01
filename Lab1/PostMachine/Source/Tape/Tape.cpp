#include "Tape.h"
#include <string>

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

