#ifndef LAB3_WAITER_H
#define LAB3_WAITER_H

#include "../Employee.h"
#include <vector>
#include <string>

class Order;

class Waiter : public Employee {
private:
    int tablesServed;
    double totalTips;
    int currentTable;
    std::vector <Order*> activeOrders;

public:
    Waiter(const std::string& name, double hourlyRate, int yearsOfExperience);

    void assignTable(int tableNumber);
    void addOrder(Order* order);
    void completeOrder(Order* order);
    void receiveTip(double amount);

    std::string getRole() const override;
    int getCurrentTable() const;
    int getTablesServed() const;
    size_t getActiveOrdersCount() const;
    double getTotalTips() const;
};

#endif //LAB3_WAITER_H
