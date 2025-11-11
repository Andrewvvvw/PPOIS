#ifndef LAB3_HOST_H
#define LAB3_HOST_H

#include "../Employee.h"
#include <vector>

class Host : public Employee {
private:
    int maxTables;
    std::vector<int> assignedTables;

public:
    Host(const std::string& name, double hourlyRate, int maxTables);

    std::string getRole() const override;

    void assignTable(int tableNumber);
    void freeTable(int tableNumber);
    bool isTableAssigned(int tableNumber) const;
    int getAssignedTablesCount() const;
};

#endif //LAB3_HOST_H
