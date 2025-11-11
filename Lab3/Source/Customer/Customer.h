#ifndef LAB3_CUSTOMER_H
#define LAB3_CUSTOMER_H

#include <string>

class Customer {
protected:
    std::string name;
    int id;
    double totalSpent;

public:
    Customer(const std::string& name, int id, double totalSpent = 0.0);
    virtual ~Customer() = default;

    std::string getName() const;
    int getId() const;
    double getTotalSpent() const;
    void setTotalSpent(double amount);
};
#endif //LAB3_CUSTOMER_H
