#ifndef LAB1_TAPE_H
#define LAB1_TAPE_H

#include <map>
#include <iostream>

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

};

#endif //LAB1_TAPE_H
