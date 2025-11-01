#ifndef LAB1_COMMAND_H
#define LAB1_COMMAND_H

#include <string>

enum class CommandType {
    SET_MARK,
    ERASE_MARK,
    MOVE_LEFT,
    MOVE_RIGHT,
    CONDITION,
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
    int nextLine;
    int nextIfZero;
    int nextIfOne;

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

};

#endif //LAB1_COMMAND_H
