#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

#include <string>

class Table {
    int tableId;
    int capacity;
    bool isOccupied;
    std::string location;

public:
    Table(int id, int capacity, const std::string& location);

    bool canAccommodate(int people) const;
    void occupy();
    void vacate();
    bool isAvailable() const;
    bool isSuitableForGroup(int people) const;
};

#endif //LAB3_TABLE_H
